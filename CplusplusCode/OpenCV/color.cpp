
/*************************************************************************
	> Author:ZX Xie 
	> Mail:1514806752@qq.com 
 ************************************************************************/


#include "../inc/detect.h"

Mat ToRBG(cv::Mat image)  //产出是一个mask
{

    cv::Mat result = Mat(image.rows, image.cols, CV_8UC1);
	imshow("origin",image);
	waitKey(0); 

    int num_row = image.rows;
    int num_col = image.cols;

    //参数
    int Bsup, Binf, Gsup, Ginf, Rsup, Rinf;
    Bsup = 255;   Binf = 70;    
    Gsup = 60;   Ginf = 0;
    Rsup = 60;   Rinf = 0;

    inRange(image, Scalar(Binf, Ginf, Rinf), Scalar(Bsup, Gsup, Rsup), result);
    
    imshow("RGBresult",result);
    waitKey(0);
    return result;
}


Mat ToHSV(cv::Mat image)  //产出是一个mask
{

    cv::Mat result = Mat(image.rows, image.cols, CV_8UC1);
    cv::Mat hsv_image;       //转HSV
    hsv_image.create(image.size(), image.type());
    cv::cvtColor(image, hsv_image, CV_BGR2HSV);
	imshow("origin",image);
	waitKey(0); 

    int num_row = image.rows;
    int num_col = image.cols;

    //参数
    int hsup, hinf, ssup, sinf, vsup, vinf;
    hsup = 130;   hinf = 100;    
    ssup = 255;   sinf = 150;
    vsup = 150;   vinf = 60;

    inRange(hsv_image, Scalar(hinf, sinf, vinf), Scalar(hsup, ssup, vsup), result);
    
    imshow("HSVresult",result);
    waitKey(0); 
    return result;
}

void detect(Mat image) {
    Mat im1 = ToRBG(image);
    Mat im2 = ToHSV(image);
    cv::Mat element_20(20, 20, CV_8U, cv::Scalar(1));
    cv::morphologyEx(im1, im1, cv::MORPH_OPEN, element_20);
    cv::morphologyEx(im2, im2, cv::MORPH_OPEN, element_20);
    Mat result = im2 & im1;
    cv::morphologyEx(result, result, cv::MORPH_OPEN, element_20);
    imshow("mix", result);
}


/* readVideo
* @param filePath 文件绝对路径
* 根据绝对路径读取需要还原背景的文件
*/
void Recovery::readVideo(String filePath) {
    video = VideoCapture(filePath);
    if (!video.isOpened()) {
        cout << "could not load video file ..." << endl;
    }
}


/* process
* 进行还原过程
*/

typedef struct p{
    Vec3b rgb;
    int count;
}point;

void Recovery::process() {
    clock_t start, end;
    start = clock();
    //允许偏差范围
    int knn = 30;
    // 获取图像总帧数
    int totalFrameNumber = video.get(CV_CAP_PROP_FRAME_COUNT);
    cout << totalFrameNumber << endl;
    //抽样样本数
    int skip = 2;
    int samplesNumber = totalFrameNumber/skip;
    //int skip = totalFrameNumber/samplesNumber;
    Mat frame[samplesNumber];
    video.read(frame[0]);
    int nr = frame[0].rows; //行数
    int nc = frame[0].cols; //列数乘通道数
    // 读取样本点到frame矩阵数列
    int count = 1;
    namedWindow("origin",WINDOW_NORMAL);
    namedWindow("mix",WINDOW_NORMAL);
    namedWindow("HSVresult",WINDOW_NORMAL);
    namedWindow("RGBresult",WINDOW_NORMAL);
    image = frame[0];
    for (int i = 1; i < samplesNumber; ++i) {
        for (int j = 0; j < skip; ++j) {
            video.grab();
        }
        video.retrieve(frame[i]);
        if(!frame[i].empty()) {
            detect(frame[i]);
        }
        else cout << "error"<<endl;
    }
    //finish
    cout << "finish!!!\n";
    //if (imwrite("result2.jpg",image)){
    //    cout << "保存成功\n";
    //}
    video.release();
    end = clock();
    cout << "Process time: " << (double)(end-start)/CLOCKS_PER_SEC << "s\n";
}

/* showResult
* 窗口展示背景还原后的结果
*/
void Recovery::showResult() {
    if( image.empty() )  // Check for invalid input
    {
        cout <<  "Could not open or find the image" << endl;
    }
    namedWindow( "show the result", WINDOW_NORMAL); // Create a window for display.
    imshow("show the result", image );                // Show our image inside it.
    waitKey(0); // Wait for a keystroke in the window
}
