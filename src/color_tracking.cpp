#include "opencv2/opencv.hpp"
#include "external/Labeling.h"
#include "include/color_tracking.hpp"

using namespace cv;

void CV::trackRed()
{
    int w = 640;
    int h = 480;
    Mat im, hsv, mask;
    LabelingBS labeling;
    RegionInfoBS* ri;
    short* mask2 = new short[w * h];
    VideoCapture cap(0);
    if (!cap.isOpened())
        return;

    while (1) {
        cap >> im;
        cvtColor(im, hsv, CV_BGR2HSV);
        inRange(hsv, Scalar(150, 70, 70), Scalar(360, 255, 255), mask);
        rectangle(mask, Point(0, 0), Point(1, 1), Scalar(255), -1);
        labeling.Exec((uchar*)mask.data, mask2, w, h, true, 30);
        ri = labeling.GetResultRegionInfo(0);
        int x1, y1, x2, y2;
        ri->GetMin(x1, y1);
        ri->GetMax(x2, y2);
        rectangle(im, Point(x1, y1), Point(x2, y2), Scalar(255, 0, 0), 3);
        flip(im, im, 1);
        imshow("Camera", im);
        //imshow("Mask", mask);
        waitKey(1);
        auto x = (x1 + x2) / 2.0;
        auto y = (y1 + y2) / 2.0;
        //std::cout << x << " " << y << std::endl;
        SharedData::setPos(x, y);
        SharedData::setArea((x2 - x1) * (y2 - y1));
        //if (waitKey(1000) >= 0) {  // 任意のキー入力があれば終了
        //    break;
        //}
    }
}
