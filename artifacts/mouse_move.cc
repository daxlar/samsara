#include <X11/extensions/XTest.h>
#include <unistd.h>
#include <iostream>


void mouse_move(){
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
    XTestFakeMotionEvent (dpy, 0, 250, 250, CurrentTime);
    //sleep(3);
    XFlush(dpy);
    XCloseDisplay(dpy);
}
