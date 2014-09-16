#include "Sumiao2.h"

#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/legacy/compat.hpp> 
#include<math.h>

Sumiao2::Sumiao2(const char* filename)
{
	fileName=filename;
	str1="1";
	str2="2";
	str3="3";
	str4="4";
	str5="5";
	cvImageSrc = cvLoadImage(fileName,CV_LOAD_IMAGE_UNCHANGED);

	MatSrc = new cv::Mat(cvImageSrc);
	MatGray = new cv::Mat(cvImageSrc);
	MatGrayInv = new cv::Mat(cvImageSrc);
	MatGrayInvGausi = new cv::Mat(cvImageSrc);
	MatSumiao = new cv::Mat(MatGrayInv->size(),CV_8UC1);

	//【1】灰度图
	cvtColor(*MatSrc,*MatGray,CV_BGR2GRAY);
	//【2】反色
	addWeighted(*MatGray,-1,NULL,0,255,*MatGrayInv);//灰度图反色
	//【3】高斯模糊,高斯核的Size与最后的效果有关  
	GaussianBlur(*MatGrayInv,*MatGrayInvGausi,cv::Size(11,11),0);  
	//【4】融合：颜色减淡
	int width=MatGrayInv->cols;  
	int heigh=MatGrayInv->rows;  
	for (int y=0; y<heigh; y++)
	{
		uchar* P0  = MatGray->ptr<uchar>(y);  
		uchar* P1  = MatGrayInvGausi->ptr<uchar>(y);  
		uchar* P  = MatSumiao->ptr<uchar>(y);  
		for (int x=0; x<width; x++)  
		{  
			int tmp0=P0[x];
			int tmp1=P1[x];  
			P[x] =(uchar) std::min((tmp0+(tmp0*tmp1)
				/(256-tmp1)),255);  
		}
	}
}


Sumiao2::~Sumiao2(void)
{
	cvImageSrc->~IplImage();
	MatSrc->~Mat();
	MatGray->~Mat();
	MatGrayInv->~Mat();
	MatGrayInvGausi->~Mat();
	MatSumiao->~Mat();
	/*
	delete cvImageSrc;
	delete MatSrc;
	delete MatGray;
	delete MatGrayInv;
	delete MatGrayInvGausi;
	delete MatSumiao;*/
}

void Sumiao2::showOriginal()
{
	cv::imshow(str5,*MatSrc);
	cv::moveWindow(str5,10,0);
}

void Sumiao2::showSumiao()
{
	cv::imshow(str1,*MatSumiao);
	cv::moveWindow(str1,10,400);
}

void Sumiao2::showGray()
{
	cv::imshow(str2,*MatGray);
	cv::moveWindow(str2,10,100);
}

void Sumiao2::showGrayInv()
{
	cv::imshow(str3,*MatGrayInv);
	cv::moveWindow(str3,10,200);
}

void Sumiao2::showGausi()
{
	cv::imshow(str4,*MatGrayInvGausi);
	cv::moveWindow(str4,10,300);
}
