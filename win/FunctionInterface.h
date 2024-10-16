#pragma once

#ifdef DLL_EXPORT
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __declspec(dllimport)
#endif

extern "C" {
    EXPORT double Execute(double arg);
    EXPORT const char* GetFunctionName();
}