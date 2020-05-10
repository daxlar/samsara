#include "camera_module.h"
#include <iostream>

// NOTE: Only works with 2 ?
#define EXTERNAL_CAMERA_MAGIC_NUM 2
// NOTE: UPPER LEFT CORNER OF TAG IS FIRST POINT@F OF VECTOR
#define MARKER_UPPER_LEFT 0
// NOTE: LEFT FINGER IS ID:0
#define LEFT_FINGER 0
// NOTE: RIGHT FINGER is ID:1
#define RIGHT_FINGER 1
#define TESTING 1 


camera_module::camera_module(){
    inputVideo.open(EXTERNAL_CAMERA_MAGIC_NUM);
    if(!inputVideo.isOpened()){
        std::cout << "Error opening video stream or file" << std::endl;
    }
    dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);
}

void camera_module::generate_markers(int size){
    cv::Mat markerImage;
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);
    cv::aruco::drawMarker(dictionary, 0, size, markerImage, 1);
    cv::imwrite("first marker.png", markerImage);
    cv::aruco::drawMarker(dictionary, 1, size, markerImage, 1);
    cv::imwrite("second marker.png", markerImage);
}

void camera_module::display_detected_markers(){
    camera_module::inputVideo.read(camera_module::image);
    cv::aruco::detectMarkers(camera_module::image, dictionary, camera_module::marker_corners, camera_module::marker_ids);
    cv::aruco::drawDetectedMarkers(camera_module::image, camera_module::marker_corners, camera_module::marker_ids);
    cv::imshow("out", camera_module::image);
    cv::waitKey(30);
}

void camera_module::read_marker_corners(){
    camera_module::inputVideo.read(camera_module::image);
    cv::aruco::detectMarkers(camera_module::image, camera_module::dictionary, camera_module::marker_corners, camera_module::marker_ids);
    if(TESTING){
        int counter = 0;
        for(auto v : camera_module::marker_corners){
            std::cout << "at: " << counter << std::endl;
            for(auto p: v){
                std::cout << p << std::endl;
            }
            counter++;
        }
    }
}

void camera_module::read_marker_ids(){
    camera_module::inputVideo.read(camera_module::image);
    cv::aruco::detectMarkers(camera_module::image, camera_module::dictionary, camera_module::marker_corners, camera_module::marker_ids);
    if(TESTING){
        for(auto id : marker_ids){
            std::cout << id << std::endl;
        }
    }
}

int camera_module::get_marker_corners_size(){
    return camera_module::marker_corners.size();
}

int camera_module::get_marker_ids_size(){
    return camera_module::marker_ids.size();
}

/*
NOTE: Doesn't suffer from marker inversion like the python version does
*/
void camera_module::get_marker_corners_val(int marker_num, int corner, cv::Point2f& coordinate_point){
    try{
        // camera_module::marker_ids.at(marker_num) solves index at 0
        // i.e. when only the right marker with ID:1 is available, indexing at zero will erroneously read right marker as left marker coordinates
        // to solve the issue, index with marker ID in marker_ids list, because zero marker inversion guarantees that if ID:0 exists, it will be at index 0
        coordinate_point = camera_module::marker_corners.at(camera_module::marker_ids.at(marker_num)).at(corner);
    }catch(const std::out_of_range& e){
        std::cout << "invalid indexes" << std::endl;
    }
}

int camera_module::get_left_finger_x(){
    camera_module::get_marker_corners_val(LEFT_FINGER, MARKER_UPPER_LEFT, camera_module::left_finger_coordinate);
    return camera_module::left_finger_coordinate.x;
}

int camera_module::get_left_finger_y(){
    camera_module::get_marker_corners_val(LEFT_FINGER, MARKER_UPPER_LEFT, camera_module::left_finger_coordinate);
    return camera_module::left_finger_coordinate.y;
}

int camera_module::get_right_finger_x(){
    camera_module::get_marker_corners_val(RIGHT_FINGER, MARKER_UPPER_LEFT, camera_module::right_finger_coordinate);
    return camera_module::right_finger_coordinate.x;
}

int camera_module::get_right_finger_y(){
    camera_module::get_marker_corners_val(RIGHT_FINGER, MARKER_UPPER_LEFT, camera_module::right_finger_coordinate);
    return camera_module::right_finger_coordinate.y;
}