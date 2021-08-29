/*
 * @Description: 
 * @Version: 
 * @Author: William
 * @Date: 2021-05-12 22:52:11
 * @LastEditors: William
 * @LastEditTime: 2021-05-12 23:21:31
 */
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
int main()
{
    Mat img=imread("test.jpg");
    imshow("image",img);
    waitKey();
    return 0;
}