#include "win32_program.h"
#include <errno.h>

void WriteDebugToFileForWindows(const char* string) {
    FILE* file = nullptr;
    errno_t err = freopen_s(&file, DEBUG_FILENAME, "a", stdout);
    if (err != 0) {
        std::cerr << "Failed to redirect output to file, error code: " << err << std::endl;
        std::cerr << "DEBUG_FILENAME: " << DEBUG_FILENAME << std::endl;
        perror("Error Details");
        // Handle the error, e.g., create directories, change path, etc.
    } else {
        fprintf(stdout, "%s", string);  
        fclose(file);
    }
    freopen_s(&file, "CON", "w", stdout); //
}

void LogMessage(char WriteToFile, int logLevel, const char* Message, ...) {
    static const int MessageLength = 32000;

    char OutMessage[MessageLength] = {};
    memset(OutMessage, 0, sizeof(OutMessage));
    
    char OutMessage2[MessageLength] = {};
    memset(OutMessage2, 0, sizeof(OutMessage2));
    
    const char* LOG_LEVEL_STRINGS[7] = {
        "  [LOG]:",
        "[FATAL]:", 
        "[ERROR]:", 
        " [WARN]:", 
        " [INFO]:", 
        "[DEBUG]:", 
        "[TRACE]:"
    };

    const int LOG_LEVEL[7] = {0, 64, 4, 6, 2, 1, 8};
    bool Error = logLevel < 2; // Assuming LOG_LEVEL_WARN corresponds to index 2
    
    va_list VAPtr;
    va_start(VAPtr, Message);
    vsnprintf(OutMessage, MessageLength, Message, VAPtr);
    va_end(VAPtr);
    
    // Platform Specific Output (Placeholder functions)
    SetConsoleTextAttribute(GetStdHandle((Error ? STD_ERROR_HANDLE : STD_OUTPUT_HANDLE)), LOG_LEVEL[logLevel]);;
    fprintf((Error ? stderr : stdout), "%s", LOG_LEVEL_STRINGS[logLevel]);
    SetConsoleTextAttribute(GetStdHandle((Error ? STD_ERROR_HANDLE : STD_OUTPUT_HANDLE)),  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    fprintf((Error ? stderr : stdout), " %s\n", OutMessage); 
    sprintf(OutMessage2, "%s %s\n", LOG_LEVEL_STRINGS[logLevel], OutMessage);
    OutputDebugStringA(OutMessage2);
    // Platform Specific Output (Placeholder functions)
    if (WriteToFile == true) {
        WriteDebugToFileForWindows(OutMessage2); 
    }
}


