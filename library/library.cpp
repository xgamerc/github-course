#include <stdio.h>
#include "library.h"

#ifdef EXPORT
#ifdef __cplusplus 
extern "C" { 
#endif

LIB void ExportedFunction(int a) {
    printf("\nNumber is: %i\n", a);
}

LIB void ExportedFunction2(int a) {
    printf("\nNumber is: %i\n", a + 1);
}

#ifdef __cplusplus
}
#endif
#endif