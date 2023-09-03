// kbhit.h
#ifndef KBHIT_H
#define KBHIT_H
#include<ncurses.h>

#include <sys/ioctl.h>
#include <termios.h>
bool kbhit()
{
    termios term;
    tcgetattr(0, &term);

    termios term2 = term;
    term2.c_lflag &= ~static_cast<tcflag_t>(ICANON);
    tcsetattr(0, TCSANOW, &term2);

    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);

    tcsetattr(0, TCSANOW, &term);

    return byteswaiting > 0;
}

#endif // KBHIT_H