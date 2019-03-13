#ifndef _REPORT_H
#define _REPORT_
#include <stdio.h>

#define ReportErrorMacro(error) \
    ReportError(#error, 0);

#define ReportLocationMacro(l, f) \
    ReportError(f, l);

#define RASSERT(exp, error) \
    if (!(exp)) \
    { \
        ReportLocationMacro(__LINE__,__FILE__); \
        ReportErrorMacro(Assert on expression #exp failed.\n);\
        ReportErrorMacro(Error detail: #error.\n\n); \
    }

#define Report(log) \
    { \
        ReportLocationMacro(__LINE__,__FILE__); \
        ReportErrorMacro(#log\n\n); \
    }

#define Terminate(log) \
    { \
        ReportLocationMacro(__LINE__,__FILE__); \
        ReportErrorMacro(#log\n\n); \
        exit(0); \
    }

#define ReportFormat1(fmt, a) \
    { \
        char _report_macro_buffer[1024]; \
        snprintf(_report_macro_buffer, sizeof(_report_macro_buffer), fmt "\n\n", a); \
        ReportLocationMacro(__LINE__,__FILE__); \
        ReportError(_report_macro_buffer, 0); \
    }


void ReportError(char* error, int line);
void loginfo(const char* fmt, ...);

#endif // _REPORT_H
