#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/aruco.hpp>


class camera_module{
    private:
        cv::VideoCapture inputVideo;
        cv::Mat image;
        cv::Ptr<cv::aruco::Dictionary> dictionary;
        std::vector<int> marker_ids;
        std::vector<std::vector<cv::Point2f>> marker_corners;
        cv::Point2f left_finger_coordinate;
        cv::Point2f right_finger_coordinate;
        bool testing;
        void get_marker_corners_val(int marker_num, int corner, cv::Point2f& coordinate_point);
    public:
        camera_module();
        void generate_markers(int size);
        void display_detected_markers();
        void read_marker_corners();
        void read_marker_ids();
        int get_marker_corners_size();
        int get_marker_ids_size();
        int get_left_finger_x();
        int get_left_finger_y();
        int get_right_finger_x();
        int get_right_finger_y();
};