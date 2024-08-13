#pragma once
#include <stdio.h>
#include <Windows.h>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <iostream>
#ifdef IMPORT
    #include <library\library.h>
#elif defined(LLA)
    /* Write Custom Function pointers using typedef and load using loadlibraryA and GetProcAddress*/
#endif

// Window's specific Logging function
static const char* DEBUG_FILENAME = "../default_log.txt";
void WriteDebugToFileForWindows(const char* string);
void LogMessage(char WriteToFile, int logLevel, const char* Message, ...);