/*
#include "camera_module.h"
#include "mouse_module.h"
*/

#include "virtual_mouse.h"

int main(int, char**)
{
    /*
    mouse_module mouse;
    camera_module camera;

    while(1){
        //camera.display_detected_markers();
        camera.read_marker_corners();
        camera.read_marker_ids();
    }
    */

    /*
    virtual_mouse vm;
    while(1){
        vm.move_cursor();
    }
    */

    camera_module cm;
    std::cout << "calibrating" << std::endl;
    cm.calibrate_camera();
    

    return 0;
}

