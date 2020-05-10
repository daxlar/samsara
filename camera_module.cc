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
#define MARKER_TESTING 0
#define POSE_TESTING 1

// NOTE: calibration camera matrix is always 3x3
#define CAMERA_MATRIX_ROWS 3
#define CAMERA_MATRIX_COLS 3
// NOTE: calibration distortion matrix is always 1xX  
#define DISTORTION_MATRIX_COLS 1


camera_module::camera_module(){
    inputVideo.open(EXTERNAL_CAMERA_MAGIC_NUM);
    if(!inputVideo.isOpened()){
        std::cout << "Error opening video stream or file" << std::endl;
    }
    dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);
    read_camera_calibration_values();
    std::cout << "distortion: " << camera_module::distortion_matrix << std::endl;
    std::cout << "camera: " << camera_module::camera_matrix << std::endl;
}

void camera_module::generate_markers(int size){
    cv::Mat markerImage;
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);
    cv::aruco::drawMarker(dictionary, 0, size, markerImage, 1);
    cv::imwrite("first marker.png", markerImage);
    cv::aruco::drawMarker(dictionary, 1, size, markerImage, 1);
    cv::imwrite("second marker.png", markerImage);
}

void camera_module::read_camera_calibration_values(){
    cv::String calibration_file_path = "../camera_calibration/out_camera_data.xml";
    cv::FileStorage fs;
    fs.open(calibration_file_path, cv::FileStorage::READ);
    if(!fs.isOpened()){
        std::cout << "file: " << calibration_file_path << " doesn't exist, build and execute camera_calibration.cc as specified" << std::endl;
    }
    /*
    cv::FileNode cm_data = fs["camera_matrix"]["data"];
    cv::FileNodeIterator it = cm_data.begin(), it_end = cm_data.end(); 
    std::vector<float> cm_data_store = {};
    for (it; it != it_end; ++it){
        float to_add = *it;
        cm_data_store.push_back(to_add);
    }
    cv::Mat camera_matrix_temp = cv::Mat(CAMERA_MATRIX_ROWS, CAMERA_MATRIX_COLS, CV_32F, cm_data_store.data());
    camera_module::camera_matrix = camera_matrix_temp;

    cv::FileNode dm_data = fs["distortion_coefficients"]["data"];
    it = dm_data.begin(); it_end = dm_data.end();
    std::vector<float> dm_data_store = {};
    for(it; it != it_end; ++it){
        float to_add = *it;
        dm_data_store.push_back(to_add);
    }
    cv::Mat distortion_matrix_temp = cv::Mat(dm_data_store.size(), DISTORTION_MATRIX_COLS, CV_32F, dm_data_store.data());
    camera_module::distortion_matrix = distortion_matrix_temp;
    */
    
    fs["camera_matrix"] >> camera_module::camera_matrix;
    fs["distortion_coefficients"] >> camera_module::distortion_matrix;
    
    fs.release();
}

void camera_module::detect_marker_corners_ids(){
    camera_module::inputVideo.read(camera_module::image);
    cv::aruco::detectMarkers(camera_module::image, dictionary, camera_module::marker_corners, camera_module::marker_ids);
     if(MARKER_TESTING){
        int counter = 0;
        for(auto v : camera_module::marker_corners){
            std::cout << "at: " << counter << std::endl;
            for(auto p: v){
                std::cout << p << std::endl;
            }
            counter++;
        }
    }
    if(MARKER_TESTING){
        for(auto id : camera_module::marker_ids){
            std::cout << id << std::endl;
        }
    }
}

void camera_module::detect_pose(){
    cv::aruco::estimatePoseSingleMarkers(camera_module::marker_corners, 0.05, 
                                         camera_module::camera_matrix, camera_module::distortion_matrix, 
                                         camera_module::rotation_vector, camera_module::translation_vector);
    if(POSE_TESTING){
        for(auto v: camera_module::rotation_vector){
            std::cout << v << std::endl;
        }
        for(auto v: camera_module::translation_vector){
            std::cout << v << std::endl;
        }
    }   
}

void camera_module::display_detected_markers(){
    cv::aruco::drawDetectedMarkers(camera_module::image, camera_module::marker_corners, camera_module::marker_ids);
    cv::imshow("out", camera_module::image);
    cv::waitKey(30);
}

void camera_module::display_pose_extraction(){
    cv::Mat imageCopy;
    camera_module::image.copyTo(imageCopy);
    cv::aruco::drawDetectedMarkers(imageCopy, camera_module::marker_corners, camera_module::marker_ids);
    camera_module::detect_pose();
    if(POSE_TESTING){
        for(auto v: camera_module::rotation_vector){
            std::cout << v << std::endl;
        }
        for(auto v: camera_module::translation_vector){
            std::cout << v << std::endl;
        }
    }   
    for(int i=0; i < get_marker_ids_size(); i++){
        cv::aruco::drawAxis(imageCopy, 
                            camera_module::camera_matrix, camera_module::distortion_matrix, 
                            camera_module::rotation_vector[i], camera_module::translation_vector[i], 
                            0.1);
    }
    cv::imshow("out", imageCopy);
    cv::waitKey(30);

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

