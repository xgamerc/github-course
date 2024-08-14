#include "../platform/win32_program.h"
#include <stdio.h>
int main() {
  printf("Hello World!\n");
  // static_assert(123 / 2 != 0, "Error");
    #ifdef IMPORT
      #ifndef LLA
          LogMessage( // 
            true,  // 
            0,  // 
            " Test: %05.2f%%\nExported Function 1: %d\nExported Function 2: %d", 25.52, ExportedFunction(1), ExportedFunction2(1) // 
          ); // 
      #endif // 
    #else  // 
        LogMessage(true, 1, "Test: %05.2f%%", 25.52);
    #endif
}