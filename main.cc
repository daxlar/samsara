/*
#include "camera_module.h"
#include "mouse_module.h"
*/

#include "virtual_mouse.h"

int main(int argc, char* argv[])
{
    camera_module camera;
    while(1){
        camera.detect_marker_corners_ids();
        camera.detect_pose();
    }

    return 0;
}

