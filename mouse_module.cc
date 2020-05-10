#include <X11/extensions/XTest.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include <iostream>
#include "mouse_module.h"

//g++ -std=c++11  main.cpp mouse_click.cpp mouse_move.cpp -lX11 -lXtst

#define RIGHT_CLICK 1

mouse_module::mouse_module(){
    mouse_module::right_click = RIGHT_CLICK;
}

void mouse_module::click(int button, bool down) {
    Display *display = XOpenDisplay(NULL);
    XTestFakeButtonEvent(display, button, down, CurrentTime);
    XFlush(display);
    XCloseDisplay(display);
}

void mouse_module::release_click(int button, bool up){
    Display *display = XOpenDisplay(NULL);
    XTestFakeButtonEvent(display, button, !up, CurrentTime);
    XFlush(display);
    XCloseDisplay(display);
}

void mouse_module::move_to(int x_coord, int y_coord){
    XEvent event;
    Display* dpy = XOpenDisplay (NULL);
    /* Get the current pointer position */
    XQueryPointer (dpy, RootWindow (dpy, 0), &event.xbutton.root,
    &event.xbutton.window, &event.xbutton.x_root,
    &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y,
    &event.xbutton.state);
    
    
    /* Fake the pointer movement to new relative position */
    /*
    XTestFakeMotionEvent (dpy, 0, event.xbutton.x + 100,
    event.xbutton.y + 50, CurrentTime);
    XSync(dpy, 0);
    sleep(3);
    */
    
    /* Fake the pointer movement to new absolate position */
    XTestFakeMotionEvent(dpy, 0, x_coord, y_coord, CurrentTime);
    //XTestFakeMotionEvent(dpy, 0, x_coord, y_coord, 0);
    //sleep(3);
    XFlush(dpy);
    XCloseDisplay(dpy);
}