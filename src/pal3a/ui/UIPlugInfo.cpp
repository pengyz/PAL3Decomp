#include "UIPlugInfo.h"

tagRECT ArtistPlugIn::GetMaxRect(tagRECT * __$ReturnUdt, char * name)
{
    /* stub */
    tagRECT _ret = {0}; return _ret;
}

void ArtistPlugIn::SetLibFolder(char * folder)
{
    /* stub */
}

_PlugInfo * ArtistPlugIn::GetInfo(char * name)
{
    /* stub */
    return NULL;
}

_PlugInfo * ArtistPlugIn::GetInfo(int index)
{
    /* stub */
    return NULL;
}

char * ArtistPlugIn::GetLib(char * _texName)
{
    /* stub */
    return NULL;
}

UIPosMaker * ArtistPlugIn::GetPosMaker()
{
    /* stub */
    return NULL;
}

void ArtistPlugIn::GetPlugFileInfo(char * filename)
{
    /* stub */
}

tagRECT ArtistPlugIn::GetRect(tagRECT * __$ReturnUdt)
{
    /* stub */
    tagRECT _ret = {0}; return _ret;
}

ArtistPlugIn::~ArtistPlugIn()
{
    /* stub */
}

ArtistPlugIn::ArtistPlugIn(char * filename)
{
    /* stub */
}

ArtistPlugIn::ArtistPlugIn()
{
    /* stub */
}

bool UIPosMaker::LoadPosFile()
{
    /* stub */
    return FALSE;
}

bool UIPosMaker::GetPos(int nIndex, int * nx, int * ny)
{
    /* stub */
    return FALSE;
}

bool UIPosMaker::GetPos(uint nameCrc, int * nx, int * ny)
{
    /* stub */
    return FALSE;
}

UIPosMaker::UIPosMaker()
{
    /* stub */
}

UIPosMaker::~UIPosMaker()
{
    /* stub */
}

bool _PlugInfo::_CalculateUV()
{
    /* stub */
    return FALSE;
}

