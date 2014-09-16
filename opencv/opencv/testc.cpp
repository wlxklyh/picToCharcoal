//#include <string>
//#include <opencv2/opencv.hpp>
//#include <opencv2/legacy/compat.hpp> 
//#include<math.h>
//using namespace cv;
//
////手动实现拉普拉斯算子图像锐化
//void sharpenImage1(const Mat &image, Mat &result)
//{
//    result.create(image.size(),image.type());//为输出图像分配内容
//    /*拉普拉斯滤波核3*3
//         0  -1   0
//        -1   5  -1
//         0  -1   0  */
//    //处理除最外围一圈外的所有像素值
//    for(int i=1; i<image.rows-1; i++)
//    {
//        const uchar * pre = image.ptr<const uchar>(i-1);//前一行
//        const uchar * cur = image.ptr<const uchar>(i);//当前行，第i行
//        const uchar * next = image.ptr<const uchar>(i+1);//下一行
//        uchar * output = result.ptr<uchar>(i);//输出图像的第i行
//        int ch = image.channels();//通道个数
//        int startCol = ch;//每一行的开始处理点
//        int endCol = (image.cols-1)* ch;//每一行的处理结束点
//        for(int j=startCol; j < endCol; j++)
//        {
//            //输出图像的遍历指针与当前行的指针同步递增, 以每行的每一个像素点的每一个通道值为一个递增量, 因为要考虑到图像的通道数
//            //saturate_cast<uchar>保证结果在uchar范围内
//            *output++ = saturate_cast<uchar>(5*cur[j]-pre[j]-next[j]-cur[j-ch]-cur[j+ch]);
//        }
//    }
//    //将最外围一圈的像素值设为0
//    result.row(0).setTo(Scalar(0));
//    result.row(result.rows-1).setTo(Scalar(0));
//    result.col(0).setTo(Scalar(0));
//    result.col(result.cols-1).setTo(Scalar(0));
//    /*/或者也可以尝试将最外围一圈设置为原图的像素值
//    image.row(0).copyTo(result.row(0));
//    image.row(image.rows-1).copyTo(result.row(result.rows-1));
//    image.col(0).copyTo(result.col(0));
//    image.col(image.cols-1).copyTo(result.col(result.cols-1));*/
//}
//
////调用OpenCV函数实现拉普拉斯算子图像锐化
//void sharpenImage2(const Mat &image, Mat &result)
//{
//    Mat kernel = (Mat_<float>(3,3) << 0,-1,0,-1,5,-1,0,-1,0);
//    filter2D(image,result,image.depth(),kernel);
//}
//
//const char* str1="112";
//const char* str2="2233";
//const char* str3="3421412";
////main函数
//int main(){    
//	IplImage *IplImagesrc = cvLoadImage("sample4.bmp");
//    Mat mat (IplImagesrc);
//    Mat result1(cvGetSize(IplImagesrc),CV_8UC1);
//    Mat result2(cvGetSize(IplImagesrc),CV_8UC1);
//	imshow(str1,mat);
//	cv::moveWindow(str1,10,100);
//	waitKey();
//    sharpenImage1(mat,result1);
//	imshow(str2,result1);
//	cv::moveWindow(str2,10,200);
//	waitKey();
//    sharpenImage2(mat,result2);
//	imshow(str3,result2);
//	cv::moveWindow(str3,10,300);
//	waitKey();
//}