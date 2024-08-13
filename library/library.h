#pragma once
#ifdef EXPORT
    #ifdef __cplusplus 
        #define LIB __declspec(dllexport)
    #else 
        #ifdef _MSC_VER_
            #define LIB __declspec(dllexport)
        #else 
            #define LIB __attribute__((visibility("default")))
        #endif
    #endif
#elif defined(IMPORT)
    #ifdef __cplusplus
        #define LIB __declspec(dllimport)
    #else 
        #ifdef _MSC_VER_
        #define LIB __declspec(dllimport)
        #else
        #define LIB
        #endif
    #endif
#endif


#ifndef LLA
#ifdef STATIC
    #define LIB
#endif
  #ifdef __cplusplus
  extern "C" { 
  #endif
    LIB void ExportedFunction(int);
    LIB void ExportedFunction2(int);
  #ifdef __cplusplus
  }
  #endif
#endif

