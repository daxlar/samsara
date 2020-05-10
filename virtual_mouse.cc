#include "virtual_mouse.h"


virtual_mouse::virtual_mouse():mm(),cm(){
}

void virtual_mouse::move_cursor(){
    cm.read_marker_corners();
    cm.read_marker_ids();
    mm.move_to(cm.get_left_finger_x(), cm.get_left_finger_y());
}

void virtual_mouse::set_cursor_sensitivity(int sensitivtiy){
    
}
