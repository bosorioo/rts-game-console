#include "report.h"
#include <stdarg.h>

void ReportError(char* error, int line)
{
    static FILE* ErrorFile = 0;

    if (!ErrorFile && !(ErrorFile = fopen("errors.txt", "w")))
        return;

    if (!error)
    {
        fclose(ErrorFile);
        ErrorFile = 0;
        return;
    }

    if (line)
        fprintf(ErrorFile, "File %s\nLine %d\n", error, line);
    else
        fprintf(ErrorFile, "%s", error);
}

void loginfo(const char* fmt, ...)
{
    static FILE* logFile = 0;
    char buffer[1024];

    if (!logFile && !(logFile = fopen("log.txt", "w")))
        return;

    va_list arg;
    va_start(arg, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, arg);
    va_end(arg);

    fprintf(logFile, "%s\n", buffer);
    fflush(logFile);
}
