#pragma once
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/legacy/compat.hpp> 
#include<math.h>

class Sumiao1
{
public:
	Sumiao1::Sumiao1(const char*fileName);
	~Sumiao1(void);
public:
	IplImage *cvImageSrc;
	cv::Mat *MatSrc;
	cv::Mat *MatGray;
	cv::Mat *MatGrayLvbo;
	cv::Mat *MatBinaryGrayLvbo;
	cv::Mat *MatBoundGrayLvbo;
	cv::Mat *MatBinaryGrayLvboDelete;

	int    k;
	double b;
	double canthreshold;

	std::string str1;
	std::string str2;
	std::string str3;
	std::string str4;
	std::string str5;
	std::string str6;
public:
	double Weight(double i,double j,double x,double y);
	void getLvbo(cv::Mat *src,cv::Mat *des,int k);
	double getuOfGray(cv::Mat *src);
	void deleteNoise(cv::Mat *src,cv::Mat *acc);

	void showOriginal();
	void showGray();
	void showGrayLvbo();
	void showBinaryGrayLvbo();
	void showBoundGrayLvbo();
	void showBinaryGrayLvboDelete();
};

