#include "mouse_module.h"
#include "camera_module.h"


class virtual_mouse{
    private:
        mouse_module mm;
        camera_module cm;
    public:
        virtual_mouse();
        void inversion_correction();
        void move_cursor();
        void set_cursor_sensitivity(int senstitivty);
};