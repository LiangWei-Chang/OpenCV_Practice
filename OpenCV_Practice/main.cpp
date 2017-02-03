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

using namespace cv;

int main(){
    Mat image = imread("/Users/PinYo/Documents/workspace/OpenCV_Practice/OpenCV_Practice/123.png");
    namedWindow("Image");
    if(image.empty())
        std::cout << "123";
    else
        imshow("Image", image);
    waitKey();
    return 0;
}
