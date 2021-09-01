/*
 * @Description: 
 * @Version: 
 * @Author: William
 * @Date: 2021-05-12 22:52:11
 * @LastEditors: William
 * @LastEditTime: 2021-09-01 20:28:36
 */
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#define Method 1;

using namespace cv;
using namespace std;

int canny_sobel(InputArray src, OutputArray &dst);
int soble_filt(InputArray src, OutputArray &dst);
void inspectTable(vector<unsigned int> &_Phase);

int main()
{
    Mat img = imread("test.png");
    imshow("image",img);
    Mat BlurredImg;
    Mat EdgeImg;
    Mat dx,dy;
    Mat PhaseImg;
    //calculate the angle after canny operation.

    canny_sobel(img,EdgeImg);
    //imshow("Edge", EdgeImg);

    waitKey(0);
    return 0;

}

int canny_sobel(InputArray src, OutputArray &dst)
{
    Mat BlurredImg;
    Mat EdgeImg;
    Mat dx,dy;
    vector<unsigned int> Phase(360,0);
    //Mat PhaseImage;
    cv::blur(src,BlurredImg,Size(3,3));
    //BlurredImg = GrayImage;
    imshow("Blurred", BlurredImg);
    waitKey(0);
    //PhaseImage.create(BlurredImg.size(), CV_32F);
    cv::Canny(BlurredImg, EdgeImg, 5, 150, 3, false);
    
    imshow("Edge",EdgeImg);
    
    dx.create(BlurredImg.size(), CV_32F);
    dy.create(BlurredImg.size(), CV_32F);
    Mat dx_abs, dy_abs;   

    Sobel(BlurredImg, dx, CV_32F, 1, 0, 3);
    Sobel(BlurredImg, dy, CV_32F, 0, 1, 3);

    for (int i = 0; i < EdgeImg.cols - 1; i++)
    {
        for (int j = 0; j < EdgeImg.rows - 1; j++)
        {
            if ( EdgeImg.at<unsigned char>(j, i) >= 200)
            {
                float gx = dx.at<float>(j, i);
                float gy = dy.at<float>(j, i);
                const float theta = fastAtan2(gy, gx + 0.00001);    
                //PhaseImage.at<float>(j,i) = theta;
                 
                const float thetaScale = 360.0 / 360;
                const int tableIndex = cvRound(theta / thetaScale) % 360;

                Phase[tableIndex]++;
            }
        }
    }

    inspectTable(Phase);

    return 1;
}


int soble_filt(InputArray src, OutputArray &dst)
{
    Mat BlurredImg;
    Mat EdgeImg;
    Mat dx,dy;
    vector<unsigned int> Phase(360,0);
    Mat PhaseImage;
    cv::blur(src,BlurredImg,Size(3,3));
    //BlurredImg = GrayImage;
    imshow("Blurred", BlurredImg);
    waitKey(0);
    //PhaseImage.create(BlurredImg.size(), CV_32F);
    
    dx.create(BlurredImg.size(), CV_32F);
    dy.create(BlurredImg.size(), CV_32F);
    Mat dx_abs, dy_abs;   

    Sobel(BlurredImg, dx, CV_32F, 1, 0, 3);
    Sobel(BlurredImg, dy, CV_32F, 0, 1, 3);

    convertScaleAbs(dx,dx_abs);
    convertScaleAbs(dy,dy_abs);

    addWeighted(dx_abs,0.5,dy_abs,0.5,0,EdgeImg); 
    imshow("Edge",EdgeImg);
/*     PhaseImage.create(BlurredImg.size(), CV_32F);
    phase(dx,dy,PhaseImage,true);
    
    convertScaleAbs(PhaseImage,PhaseImage);
    imshow("Phase", PhaseImage);

    waitKey(0); */
    for (int i = 0; i < EdgeImg.cols - 1; i++)
    {
        for (int j = 0; j < EdgeImg.rows - 1; j++)
        {
            if ( EdgeImg.at<unsigned char>(j, i) >= 100)
            {
                float gx = dx.at<float>(j, i);
                float gy = dy.at<float>(j, i);
                const float theta = fastAtan2(gy, gx + 0.00001);    
                //PhaseImage.at<float>(j,i) = theta;
                 
                const float thetaScale = 360.0 / 360;
                const int tableIndex = cvRound(theta / thetaScale) % 360;

                Phase[tableIndex]++;
            }
        }
    }

    inspectTable(Phase);


    return 1;
}

void inspectTable(vector<unsigned int> &_Phase)
{
    int entryNum = 0;
    for (int i = 0; i < _Phase.size(); i++) 
    {
        cout << "Angle: " << i << " :" <<_Phase[i]<< endl;
        entryNum +=_Phase[i];
    }  
    cout << "total edge points number is " << entryNum << "." <<endl;
}
