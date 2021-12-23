#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "RSWrapper.h"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;
void mask_depth(Mat &image, Mat &th, int throld = 1000)
{
    int nr = image.rows; // number of rows
    int nc = image.cols; // number of columns
    for (int i = 0; i < nr; i++)
    {

        for (int j = 0; j < nc; j++)
        {
            if (image.at<ushort>(i, j) > throld)
                th.at<ushort>(i, j) = 0;
        }
    }
}
vector<vector<Point>> find_obstacle(Mat &depth, int thresh = 20, int max_thresh = 255, int area = 500)
{
    Mat dep;
    depth.copyTo(dep);
    mask_depth(depth, dep, 1000);
    dep.convertTo(dep, CV_8UC1, 1.0 / 16);
    //imshow("color", color);
    imshow("depth", dep);
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); //核的大小可适当调整
    Mat out;
    //进行开操作
    morphologyEx(dep, out, MORPH_OPEN, element);
    //dilate(dhc, out, element);

    //显示效果图
    imshow("opencv", out);
    Mat src_copy = dep.clone();
    Mat threshold_output;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    RNG rng(12345);
    /// 对图像进行二值化
    threshold(dep, threshold_output, thresh, 255, CV_THRESH_BINARY);
    //mask_depth(src, threshold_output);
    /// 寻找轮廓
    findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    /// 对每个轮廓计算其凸包
    vector<vector<Point>> hull(contours.size());
    vector<vector<Point>> result;
    for (int i = 0; i < contours.size(); i++)
    {
        convexHull(Mat(contours[i]), hull[i], false);
    }

    /// 绘出轮廓及其凸包
    Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
    for (int i = 0; i < contours.size(); i++)
    {
        if (contourArea(contours[i]) < area) //面积小于area的凸包，可忽略
            continue;
        result.push_back(hull[i]);
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point());
        drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point());
    }
    imshow("contours", drawing);
    return result;
}
int main(int argc, char *argv[])
{
    Mat dhc;
    Mat dep;
    int idxImageRes = 1, idxFrameRate = 30;
    RSWrapper depthCam(idxImageRes, idxImageRes, idxFrameRate, idxFrameRate);
    if (!depthCam.init())
    {
        std::cerr << "Init. RealSense Failure!" << std::endl;
        return -1;
    }

    while (true)
    {
        //Get RGB-D Images
        cv::Mat color, depth;
        bool ret = depthCam.capture(color, depth);
        if (!ret)
        {
            std::cerr << "Get realsense camera data failure!" << std::endl;
            break;
        }
        vector<vector<Point>> result;
        result = find_obstacle(depth, 20, 255, 500);

        if (cvWaitKey(1) == 27)
            break;
    }

    depthCam.release();
}