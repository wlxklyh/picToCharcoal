#pragma once
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/legacy/compat.hpp> 
#include<math.h>

class Sumiao2
{
public:
	Sumiao2::Sumiao2(const char* filename);
	~Sumiao2(void);
public:
	const char *fileName;
	std::string str1;
	std::string str2;
	std::string str3;
	std::string str4;
	std::string str5;

	IplImage *cvImageSrc;
	cv::Mat *MatSrc;
	cv::Mat *MatGray;
	cv::Mat *MatGrayInv;
	cv::Mat *MatGrayInvGausi;
	cv::Mat *MatSumiao;
public:
	void showOriginal();
	void showSumiao();
	void showGray();
	void showGrayInv();
	void showGausi();
};

