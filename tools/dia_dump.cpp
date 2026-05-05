// Minimal DIA SDK PDB dumper - exports symbols to JSON
// Compile: cl /EHsc /I"<VS>/DIA SDK/include" tools/dia_dump.cpp /link /LIBPATH:"<VS>/DIA SDK/lib/amd64" diaguids.lib ole32.lib oleaut32.lib
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dia2.h>
#include <atlbase.h>

// Simple JSON output helpers with nesting support
FILE* out;
int first_stack[64];
int first_sp = 0;

void json_start_obj() { fprintf(out, "{"); }
void json_end_obj() { fprintf(out, "}"); }
void json_start_array(const char* key) {
    fprintf(out, "\"%s\":[", key);
    first_stack[first_sp++] = 1;
}
void json_end_array() {
    fprintf(out, "]");
    if (first_sp > 0) first_sp--;
}
void json_comma() {
    int idx = first_sp > 0 ? first_sp - 1 : 0;
    if (!first_stack[idx]) fprintf(out, ",");
    first_stack[idx] = 0;
}

void json_str(const char* key, const wchar_t* val) {
    if (!val) val = L"";
    fprintf(out, "\"%s\":\"", key);
    for (const wchar_t* p = val; *p; p++) {
        if (*p == '"') fprintf(out, "\\\"");
        else if (*p == '\\') fprintf(out, "\\\\");
        else if (*p < 128) fputc((char)*p, out);
        else fprintf(out, "\\u%04x", (unsigned)*p);
    }
    fprintf(out, "\"");
}

void json_int(const char* key, long long val) { fprintf(out, "\"%s\":%lld", key, val); }
void json_hex(const char* key, unsigned long val) { fprintf(out, "\"%s\":\"0x%08lX\"", key, val); }

// Resolve DIA type symbol to a C type name string
// Writes result into buf (max bufLen chars)
void resolve_type_name_r(IDiaSymbol* pType, wchar_t* buf, int bufLen, int depth) {
    buf[0] = 0;
    if (!pType || depth > 8) { wcscpy_s(buf, bufLen, L"void"); return; }

    DWORD symTag = 0;
    pType->get_symTag(&symTag);

    if (symTag == SymTagBaseType) {
        DWORD baseType = 0;
        ULONGLONG len = 0;
        pType->get_baseType(&baseType);
        pType->get_length(&len);
        // btVoid=1, btChar=2, btWChar=3, btInt=6, btUInt=7, btFloat=8, btBool=10, btLong=13, btULong=14, btHresult=31
        switch (baseType) {
            case 0: wcscpy_s(buf, bufLen, L"void"); break; // btNoType
            case 1: wcscpy_s(buf, bufLen, L"void"); break;
            case 2: wcscpy_s(buf, bufLen, L"char"); break;
            case 3: wcscpy_s(buf, bufLen, L"wchar_t"); break;
            case 6: // btInt
                if (len == 1) wcscpy_s(buf, bufLen, L"char");
                else if (len == 2) wcscpy_s(buf, bufLen, L"short");
                else if (len == 4) wcscpy_s(buf, bufLen, L"int");
                else if (len == 8) wcscpy_s(buf, bufLen, L"__int64");
                else swprintf_s(buf, bufLen, L"int%llu", len*8);
                break;
            case 7: // btUInt
                if (len == 1) wcscpy_s(buf, bufLen, L"unsigned char");
                else if (len == 2) wcscpy_s(buf, bufLen, L"unsigned short");
                else if (len == 4) wcscpy_s(buf, bufLen, L"unsigned int");
                else if (len == 8) wcscpy_s(buf, bufLen, L"unsigned __int64");
                else swprintf_s(buf, bufLen, L"uint%llu", len*8);
                break;
            case 8: // btFloat
                if (len == 4) wcscpy_s(buf, bufLen, L"float");
                else wcscpy_s(buf, bufLen, L"double");
                break;
            case 10: wcscpy_s(buf, bufLen, L"bool"); break; // btBool
            case 13: // btLong
                if (len == 4) wcscpy_s(buf, bufLen, L"long");
                else wcscpy_s(buf, bufLen, L"long long");
                break;
            case 14: // btULong
                if (len == 4) wcscpy_s(buf, bufLen, L"unsigned long");
                else wcscpy_s(buf, bufLen, L"unsigned long long");
                break;
            case 31: wcscpy_s(buf, bufLen, L"HRESULT"); break;
            default: swprintf_s(buf, bufLen, L"base_%lu_%llu", baseType, len); break;
        }
    } else if (symTag == SymTagPointerType) {
        IDiaSymbol* pPointee = NULL;
        pType->get_type(&pPointee);
        wchar_t inner[256];
        resolve_type_name(pPointee, inner, 256);
        if (pPointee) pPointee->Release();
        swprintf_s(buf, bufLen, L"%s*", inner);
    } else if (symTag == SymTagArrayType) {
        IDiaSymbol* pElem = NULL;
        pType->get_type(&pElem);
        wchar_t inner[256];
        resolve_type_name(pElem, inner, 256);
        if (pElem) pElem->Release();
        DWORD count = 0;
        pType->get_count(&count);
        swprintf_s(buf, bufLen, L"%s[%lu]", inner, count);
    } else if (symTag == SymTagUDT || symTag == SymTagEnum || symTag == SymTagTypedef) {
        BSTR name = NULL;
        pType->get_name(&name);
        if (name && wcslen(name) > 0) {
            wcscpy_s(buf, bufLen, name);
            SysFreeString(name);
        } else {
            wcscpy_s(buf, bufLen, L"unknown_udt");
            if (name) SysFreeString(name);
        }
    } else if (symTag == SymTagFunctionType) {
        wcscpy_s(buf, bufLen, L"void(*)()");
    } else {
        BSTR name = NULL;
        pType->get_name(&name);
        if (name && wcslen(name) > 0) {
            wcscpy_s(buf, bufLen, name);
            SysFreeString(name);
        } else {
            swprintf_s(buf, bufLen, L"unknown_%lu", symTag);
            if (name) SysFreeString(name);
        }
    }
}

void json_type(const char* key, IDiaSymbol* pType) {
    wchar_t typeName[512];
    resolve_type_name(pType, typeName, 512);
    json_str(key, typeName);
}

typedef HRESULT(WINAPI* DllGetClassObjectFunc)(REFCLSID, REFIID, LPVOID*);

IDiaDataSource* CreateDiaSource(const wchar_t* dllPath) {
    HMODULE hDll = LoadLibraryW(dllPath);
    if (!hDll) { fprintf(stderr, "Cannot load: %ls\n", dllPath); return NULL; }

    DllGetClassObjectFunc pDllGetClassObject =
        (DllGetClassObjectFunc)GetProcAddress(hDll, "DllGetClassObject");
    if (!pDllGetClassObject) { fprintf(stderr, "No DllGetClassObject\n"); return NULL; }

    IClassFactory* pFactory = NULL;
    HRESULT hr = pDllGetClassObject(__uuidof(DiaSource), IID_IClassFactory, (void**)&pFactory);
    if (FAILED(hr)) { fprintf(stderr, "GetClassObject failed: 0x%08X\n", hr); return NULL; }

    IDiaDataSource* pSource = NULL;
    hr = pFactory->CreateInstance(NULL, __uuidof(IDiaDataSource), (void**)&pSource);
    pFactory->Release();
    if (FAILED(hr)) { fprintf(stderr, "CreateInstance failed: 0x%08X\n", hr); return NULL; }

    return pSource;
}

int wmain(int argc, wchar_t* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: dia_dump.exe <pdb_file> <output.json>\n");
        return 1;
    }

    const wchar_t* pdbPath = argv[1];
    const wchar_t* outPath = argv[2];

    CoInitialize(NULL);

    // Find msdia140.dll
    const wchar_t* diaDll = L"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\DIA SDK\\bin\\amd64\\msdia140.dll";

    IDiaDataSource* pSource = CreateDiaSource(diaDll);
    if (!pSource) { fprintf(stderr, "Failed to create DIA source\n"); return 1; }

    HRESULT hr = pSource->loadDataFromPdb(pdbPath);
    if (FAILED(hr)) { fprintf(stderr, "loadDataFromPdb failed: 0x%08X\n", hr); return 1; }
    fprintf(stderr, "PDB loaded successfully\n");

    IDiaSession* pSession = NULL;
    hr = pSource->openSession(&pSession);
    if (FAILED(hr)) { fprintf(stderr, "openSession failed: 0x%08X\n", hr); return 1; }

    IDiaSymbol* pGlobal = NULL;
    pSession->get_globalScope(&pGlobal);

    out = _wfopen(outPath, L"w");
    if (!out) { fprintf(stderr, "Cannot open output file\n"); return 1; }

    fprintf(out, "{\"image_base\":\"0x00400000\",");

    // === Compilands (source modules) ===
    json_start_array("compilands");

    IDiaEnumSymbols* pCompilands = NULL;
    pGlobal->findChildren(SymTagCompiland, NULL, 0, &pCompilands);
    if (pCompilands) {
        IDiaSymbol* pComp = NULL;
        ULONG celt = 0;
        int comp_count = 0;

        while (SUCCEEDED(pCompilands->Next(1, &pComp, &celt)) && celt == 1) {
            json_comma();
            json_start_obj();

            BSTR compName = NULL;
            pComp->get_name(&compName);
            json_str("name", compName ? compName : L"");
            if (compName) SysFreeString(compName);

            // Source files for this compiland
            fprintf(out, ",");
            json_start_array("source_files");
            IDiaEnumSourceFiles* pSrcFiles = NULL;
            pSession->findFile(pComp, NULL, 0, &pSrcFiles);
            if (pSrcFiles) {
                IDiaSourceFile* pSrc = NULL;
                while (SUCCEEDED(pSrcFiles->Next(1, &pSrc, &celt)) && celt == 1) {
                    BSTR srcName = NULL;
                    pSrc->get_fileName(&srcName);
                    if (srcName) {
                        json_comma();
                        fprintf(out, "\"");
                        for (const wchar_t* p = srcName; *p; p++) {
                            if (*p == '\\') fprintf(out, "\\\\");
                            else if (*p == '"') fprintf(out, "\\\"");
                            else if (*p < 128) fputc((char)*p, out);
                        }
                        fprintf(out, "\"");
                        SysFreeString(srcName);
                    }
                    pSrc->Release();
                }
                pSrcFiles->Release();
            }
            json_end_array();

            // Functions in this compiland
            fprintf(out, ",");
            json_start_array("functions");
            IDiaEnumSymbols* pFuncs = NULL;
            pComp->findChildren(SymTagFunction, NULL, 0, &pFuncs);
            if (pFuncs) {
                IDiaSymbol* pFunc = NULL;
                while (SUCCEEDED(pFuncs->Next(1, &pFunc, &celt)) && celt == 1) {
                    json_comma();
                    json_start_obj();

                    BSTR funcName = NULL;
                    pFunc->get_name(&funcName);
                    json_str("name", funcName ? funcName : L"");
                    if (funcName) SysFreeString(funcName);

                    DWORD rva = 0;
                    pFunc->get_relativeVirtualAddress(&rva);
                    fprintf(out, ","); json_hex("address", 0x00400000 + rva);

                    ULONGLONG len = 0;
                    pFunc->get_length(&len);
                    fprintf(out, ","); json_int("size", (long long)len);

                    // Class parent
                    IDiaSymbol* pParent = NULL;
                    pFunc->get_classParent(&pParent);
                    if (pParent) {
                        BSTR parentName = NULL;
                        pParent->get_name(&parentName);
                        fprintf(out, ","); json_str("class", parentName ? parentName : L"");
                        if (parentName) SysFreeString(parentName);
                        pParent->Release();
                    }

                    // Return type and parameters via function type
                    IDiaSymbol* pFuncType = NULL;
                    pFunc->get_type(&pFuncType);
                    if (pFuncType) {
                        IDiaSymbol* pRetType = NULL;
                        pFuncType->get_type(&pRetType);
                        fprintf(out, ","); json_type("return_type", pRetType);
                        if (pRetType) pRetType->Release();

                        // Parameters
                        fprintf(out, ",");
                        json_start_array("parameters");
                        IDiaEnumSymbols* pParams = NULL;
                        pFuncType->findChildren(SymTagFunctionArgType, NULL, 0, &pParams);
                        if (pParams) {
                            IDiaSymbol* pParam = NULL;
                            while (SUCCEEDED(pParams->Next(1, &pParam, &celt)) && celt == 1) {
                                json_comma();
                                json_start_obj();
                                IDiaSymbol* pParamType = NULL;
                                pParam->get_type(&pParamType);
                                json_type("type", pParamType);
                                if (pParamType) pParamType->Release();
                                json_end_obj();
                                pParam->Release();
                            }
                            pParams->Release();
                        }
                        json_end_array();

                        pFuncType->Release();
                    }

                    json_end_obj();
                    pFunc->Release();
                }
                pFuncs->Release();
            }
            json_end_array();

            json_end_obj();
            pComp->Release();
            comp_count++;
            if (comp_count % 20 == 0) fprintf(stderr, "  Compilands: %d\n", comp_count);
        }
        pCompilands->Release();
        fprintf(stderr, "Total compilands: %d\n", comp_count);
    }
    json_end_array();

    // === UDTs (structs/classes) ===
    fprintf(out, ",");
    json_start_array("types");
    IDiaEnumSymbols* pUDTs = NULL;
    pGlobal->findChildren(SymTagUDT, NULL, 0, &pUDTs);
    if (pUDTs) {
        IDiaSymbol* pUDT = NULL;
        ULONG celt = 0;
        int type_count = 0;
        while (SUCCEEDED(pUDTs->Next(1, &pUDT, &celt)) && celt == 1 && type_count < 10000) {
            json_comma();
            json_start_obj();

            BSTR udtName = NULL;
            pUDT->get_name(&udtName);
            json_str("name", udtName ? udtName : L"");
            if (udtName) SysFreeString(udtName);

            DWORD udtKind = 0;
            pUDT->get_udtKind(&udtKind);
            const char* kindStr = udtKind == 0 ? "struct" : udtKind == 1 ? "class" : "union";
            fprintf(out, ",\"kind\":\"%s\"", kindStr);

            ULONGLONG udtLen = 0;
            pUDT->get_length(&udtLen);
            fprintf(out, ","); json_int("size", (long long)udtLen);

            // Members
            fprintf(out, ",");
            json_start_array("members");
            IDiaEnumSymbols* pMembers = NULL;
            pUDT->findChildren(SymTagData, NULL, 0, &pMembers);
            if (pMembers) {
                IDiaSymbol* pMem = NULL;
                while (SUCCEEDED(pMembers->Next(1, &pMem, &celt)) && celt == 1) {
                    json_comma();
                    json_start_obj();

                    BSTR memName = NULL;
                    pMem->get_name(&memName);
                    json_str("name", memName ? memName : L"");
                    if (memName) SysFreeString(memName);

                    LONG offset = 0;
                    pMem->get_offset(&offset);
                    fprintf(out, ","); json_int("offset", offset);

                    IDiaSymbol* pMemType = NULL;
                    pMem->get_type(&pMemType);
                    if (pMemType) {
                        fprintf(out, ","); json_type("type", pMemType);
                        ULONGLONG mLen = 0;
                        pMemType->get_length(&mLen);
                        fprintf(out, ","); json_int("size", (long long)mLen);
                        pMemType->Release();
                    }

                    json_end_obj();
                    pMem->Release();
                }
                pMembers->Release();
            }
            json_end_array();

            json_end_obj();
            pUDT->Release();
            type_count++;
        }
        pUDTs->Release();
        fprintf(stderr, "Total types: %d\n", type_count);
    }
    json_end_array();

    // === Global data ===
    fprintf(out, ",");
    json_start_array("globals");
    IDiaEnumSymbols* pData = NULL;
    pGlobal->findChildren(SymTagData, NULL, 0, &pData);
    if (pData) {
        IDiaSymbol* pDatum = NULL;
        ULONG celt = 0;
        int glob_count = 0;
        while (SUCCEEDED(pData->Next(1, &pDatum, &celt)) && celt == 1 && glob_count < 50000) {
            DWORD locType = 0;
            pDatum->get_locationType(&locType);
            // Only static globals (locationType == LocIsStatic)
            if (locType == 1) {
                BSTR gName = NULL;
                pDatum->get_name(&gName);
                if (gName && wcslen(gName) > 0) {
                    json_comma();
                    json_start_obj();
                    json_str("name", gName);

                    DWORD rva = 0;
                    pDatum->get_relativeVirtualAddress(&rva);
                    fprintf(out, ","); json_hex("address", 0x00400000 + rva);

                    IDiaSymbol* pGType = NULL;
                    pDatum->get_type(&pGType);
                    if (pGType) {
                        fprintf(out, ","); json_type("type", pGType);
                        ULONGLONG gLen = 0;
                        pGType->get_length(&gLen);
                        fprintf(out, ","); json_int("size", (long long)gLen);
                        pGType->Release();
                    }

                    json_end_obj();
                    glob_count++;
                }
                if (gName) SysFreeString(gName);
            }
            pDatum->Release();
        }
        pData->Release();
        fprintf(stderr, "Total globals: %d\n", glob_count);
    }
    json_end_array();

    fprintf(out, "}");
    fclose(out);

    pGlobal->Release();
    pSession->Release();
    pSource->Release();
    CoUninitialize();

    fprintf(stderr, "Done! Output: %ls\n", outPath);
    return 0;
}
