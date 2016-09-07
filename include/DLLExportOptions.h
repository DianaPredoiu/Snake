#pragma once

#ifdef _MSC_VER
#ifdef DLL_EXP
#define DLL_SNAKE __declspec(dllexport)
#else
#define DLL_SNAKE __declspec(dllimport)

#endif // My
#endif // _MS
