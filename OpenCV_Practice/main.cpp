//
//  main.cpp
//  OpenCV_Practice
//
//  Created by 張良瑋 on 2017/2/3.
//  Copyright © 2017年 張良瑋. All rights reserved.
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int slider_value, max_slider_value;
Mat frame, frame_front, frame_front_gray;
Mat canny_dst, detected_edges;

int edgeThresh = 1;
int Ratio = 3;
int kernel_size = 3;

void on_trackbar(int, void*){
    
    double alpha = (double)slider_value / 100.0;
    double beta = 1.0 - alpha;
    
    /// Create a matrix of the same type and size as src (for dst)
    canny_dst.create(frame_front.size(), frame_front.type());
    
    /// Convert the image to grayscale
    cvtColor(frame_front, frame_front_gray, CV_BGR2GRAY);
    
    // Reduce noise with a kernel 3x3
    blur(frame_front_gray, detected_edges, Size(3, 3));
    
    // Canny detector
    Canny(detected_edges, detected_edges, slider_value, slider_value*Ratio, kernel_size);
    
    canny_dst = Scalar::all(0);
    frame_front.copyTo(canny_dst, detected_edges);
    
    Mat blended;
    
    addWeighted(canny_dst, alpha, frame_front, beta, 0.0, blended);
    
    // Copy blended front_frame to the video frame
    blended.copyTo(frame(Rect(0, 0, blended.cols, blended.rows)));
    imshow("Video Window", frame);
}

int main(){
    VideoCapture front_cam(0);
    VideoCapture video("/Users/PinYo/Desktop/Senior_Preject/OpenCV_Project/OpenCV_Practice/OpenCV_Practice/TenThousandSad.mp4");
    
    if(!front_cam.isOpened()){
        cout << "Front camera loading error\n";
        return -1;
    }
    if(!video.isOpened()){
        cout << "Video loading error\n";
        return -1;
    }
    
    slider_value = 0;
    max_slider_value = 100;
    
    namedWindow("Video Window", CV_WINDOW_KEEPRATIO);
    createTrackbar("Ratio: ", "Video Window", &slider_value, max_slider_value, on_trackbar);
    
    for(;;){
        video >> frame;
        front_cam >> frame_front;
        // resize the frame to fit the monitor
        resize(frame, frame, Size(frame.cols*0.9, frame.rows*0.9));
        resize(frame_front, frame_front, Size(frame_front.cols*0.2, frame_front.rows*0.2));
        
        on_trackbar(slider_value, 0);

        if(waitKey(1) < 0) break;
    }
    return 0;
}
