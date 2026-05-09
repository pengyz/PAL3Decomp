#pragma once

#ifdef GBENGINE_EXPORTS
#define GBAPI __declspec(dllexport)
#else
#define GBAPI __declspec(dllimport)
#endif
