#include "clock.h"

#if defined(_WIN32) /* Implementação de sleep/gettime para windows. */

    #include <windows.h>

    void Clock_Sleep(unsigned mili)
    {
        Sleep(mili);
    }

    unsigned long long Clock_GetTime(unsigned long long* last)
    {
        HANDLE currentThread = GetCurrentThread();
        DWORD_PTR previousMask = SetThreadAffinityMask(currentThread, 1);
        static LARGE_INTEGER frequency;
        static int initialized = 0;
        if (!initialized)
        {
            QueryPerformanceFrequency(&frequency);
            initialized = 1;
        }
        LARGE_INTEGER time;
        QueryPerformanceCounter(&time);
        SetThreadAffinityMask(currentThread, previousMask);
        unsigned long long tnow = 1000000ULL * time.QuadPart / frequency.QuadPart;
        if (last)
            return (tnow - *last) / 1000ULL;
        return tnow;
    }

#else /* Implementação de sleep/gettime para linux. */

    #include <unistd.h>
    #include <sys/time.h>

    void Clock_Sleep(unsigned mili)
    {
        usleep(mili * 1000);
    }

    unsigned long long Clock_GetTime(unsigned long long* last)
    {
        unsigned long long tnow;
        struct timeval time;
        gettimeofday(&time, NULL);
        tnow = (unsigned long long)(time.tv_sec) * 1000000ULL + time.tv_usec / 1000ULL;

        if (last)
            return (tnow - *last) / 1000ULL;

        return tnow;
    }

#endif
