class mouse_module{
    public:
        int right_click;
        mouse_module();
        void click(int button, bool down);
        void release_click(int button, bool up);
        void move_to(int x_coord, int y_coord);
};