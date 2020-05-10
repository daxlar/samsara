#include <X11/extensions/XTest.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include <iostream>

//g++ -std=c++11  main.cpp mouse_click.cpp mouse_move.cpp -lX11 -lXtst

#define RIGHT_CLICK 1

void click(int button, bool down) {
    Display *display = XOpenDisplay(NULL);
    XTestFakeButtonEvent(display, button, down, CurrentTime);
    XFlush(display);
    XCloseDisplay(display);
}

void release_click(int button, bool up){
    Display *display = XOpenDisplay(NULL);
    XTestFakeButtonEvent(display, button, !up, CurrentTime);
    XFlush(display);
    XCloseDisplay(display);
}



