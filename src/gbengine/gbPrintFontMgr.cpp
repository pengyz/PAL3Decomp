/**
 * gbengine.dll - gbPrintFontMgr
 * Font manager - additional implementation
 */

#include "gbengine/gbPrintFont.h"

// Get font by type (default, small, large)
gbPrintFont* gbPrintFontMgr::GetFont(gbFontType type) {
    int index = (int)type;
    if (index < 0 || index >= 4) {
        index = 0; // default font
    }
    return fonts[index];
}
