#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/aruco.hpp>


class camera_module{
    private:
        cv::VideoCapture inputVideo;
        cv::Mat image;
        cv::Mat camera_matrix;
        cv::Mat distortion_matrix;
        cv::Ptr<cv::aruco::Dictionary> dictionary;
        std::vector<int> marker_ids;
        std::vector<std::vector<cv::Point2f>> marker_corners;
        std::vector<cv::Vec3d> translation_vector;
        std::vector<cv::Vec3d> rotation_vector;
        cv::Point2f left_finger_coordinate;
        cv::Point2f right_finger_coordinate;
        bool testing;
        void get_marker_corners_val(int marker_num, int corner, cv::Point2f& coordinate_point);
        void read_camera_calibration_values();
    public:
        camera_module();
        void generate_markers(int size);
        void detect_marker_corners_ids();
        void detect_pose();
        void display_detected_markers();
        void display_pose_extraction();
        int get_marker_corners_size();
        int get_marker_ids_size();
        int get_left_finger_x();
        int get_left_finger_y();
        int get_right_finger_x();
        int get_right_finger_y();
};