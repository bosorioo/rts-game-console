#include "terminal_size.h"

#if defined(_WIN32)

#include <windows.h>

char GetTerminalSize(int* width, int* height)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    if (width)
        *width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    if (height)
        *height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return 1;
}

#elif defined(__linux__)

#include <sys/ioctl.h>
#include <unistd.h>

char GetTerminalSize(int* width, int* height)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    if (width)
        *width = w.ws_col;

    if (height)
        *height = w.ws_row;

    return 1;
}

#else

char GetTerminalSize(int* width, int* height)
{
    return 0;
}

#endif // _TERMINAL_SIZE_H
