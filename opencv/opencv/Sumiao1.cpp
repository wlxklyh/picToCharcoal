#include "Sumiao1.h"


Sumiao1::Sumiao1(const char*fileName)
{
	str1="1";
	str2="2";
	str3="3";
	str4="4";
	str5="5";
	str6="6";
	k=3;
	b=0.97;
	canthreshold=6.0;

	IplImage *cvImageSrc = cvLoadImage(fileName,CV_LOAD_IMAGE_UNCHANGED);
	MatSrc=new cv::Mat(cvImageSrc);
	MatGray=new cv::Mat(cvGetSize(cvImageSrc),CV_8UC1);
	MatGrayLvbo=new cv::Mat(cvGetSize(cvImageSrc),CV_8UC1);
	MatBinaryGrayLvbo=new cv::Mat(cvGetSize(cvImageSrc),CV_8UC1);
	MatBoundGrayLvbo=new cv::Mat(cvGetSize(cvImageSrc),CV_8UC1);
	MatBinaryGrayLvboDelete=new cv::Mat(cvGetSize(cvImageSrc),CV_8UC1);

	//¡¾1¡¿»Ò¶ÈÍ¼
	cvtColor(*MatSrc,*MatGray,CV_BGR2GRAY);
	//¡¾2¡¿¹ýÂËÆ÷
	getLvbo(MatGray,MatGrayLvbo,k);
	//¡¾3¡¿¶þÖµ»¯ÂË²¨Í¼  MatBinaryGrayLvbo
	double uofGray = getuOfGray(MatGrayLvbo);
	double B=uofGray*b;
	cv::threshold(*MatGrayLvbo, *MatBinaryGrayLvbo
		, B, 255, CV_THRESH_BINARY );
	//¡¾4¡¿±ßÔµ¼ì²âÂË²¨Í¼  MatBinaryGrayLvbo
	cv::Canny(*MatGrayLvbo, *MatBoundGrayLvbo, 
		canthreshold, canthreshold * 3, 3);
	addWeighted(*MatBoundGrayLvbo,-1,NULL,0,
		255,*MatBoundGrayLvbo);
	MatBinaryGrayLvboDelete=new cv::Mat(*MatBinaryGrayLvbo);
	//¡¾5¡¿Í¨¹ý±ßÔµ¼ì²âÀ´¶ÔMatBinaryGrayLvboÈ¥Ôë
	deleteNoise(MatBinaryGrayLvboDelete,MatBoundGrayLvbo);

}



Sumiao1::~Sumiao1(void)
{

}

double Sumiao1::Weight( double i,double j,double x,double y )
{
	if(i==x&&j==y)return 1;
	else return (1.0/sqrt((x-i)*(x-i)+(y-j)*(y-j)));
}

void Sumiao1::getLvbo( cv::Mat *src,cv::Mat *des,int k )
{
	int h=src->rows;
	int w=src->cols;
	for(int y=0;y<h;y++)
	{
		uchar* p0=src->ptr<uchar>(y);
		uchar* p1=des->ptr<uchar>(y);
		for(int x=0;x<w;x++)
		{
			int tmp0=p0[x];
			int x1=(x-k<0?0:x-k);
			int y1=(y-k<0?0:y-k);
			int x2=(x+k>w?w:x+k);
			int y2=(y+k>h?h:y+k);
			double sum=0.0;
			double Sum2=0.0;
			for(int j=y1;j<y2;j++)
			{
				uchar *pk=src->ptr<uchar>(j);
				for(int i=x1;i<x2;i++)
				{
					int tmpk=pk[i];
					sum+=Weight(i,j,x,y)*(tmp0-tmpk);
					Sum2+=Weight(i,j,x,y);
				}
			}
			Sum2-=1;
			sum=(sum+Sum2*255)/(2*Sum2*255)*255;
			p1[x]=sum;
		}
	}
}

double Sumiao1::getuOfGray( cv::Mat *src )
{
	int grayArray[256];
	memset(grayArray,0,sizeof(grayArray));
	double h=src->rows;
	double w=src->cols;
	for(int y=0;y<h;y++)
	{
		uchar* p0=src->ptr<uchar>(y);
		for(int x=0;x<w;x++)
		{
			grayArray[p0[x]]++;
		}
	}
	double sum=0.0;
	for(int i=0;i<256;i++)
	{
		sum+=1.0*i*(1.0*grayArray[i]/(h*w));
	}
	return sum;
}

void Sumiao1::deleteNoise( cv::Mat *src,cv::Mat *acc )
{
	int h=src->rows;
	int w=src->cols;
	for(int y=0;y<h;y++)
	{
		uchar* p0=src->ptr<uchar>(y);
		for(int x=0;x<w;x++)
		{
			if(p0[x]!=255){
				int x1=(x-1<0?0:x-1);
				int y1=(y-1<0?0:y-1);
				int x2=(x+1>w?w:x+1);
				int y2=(y+1>h?h:y+1);
				bool isHaveBound=false;
				for(int j=y1;j<y2;j++)
				{
					uchar* pacc=acc->ptr<uchar>(j);
					for(int i=x1;i<x2;i++)
					{
						if(i==x&&y==j)continue;
						else 
						{
							if(pacc[i]!=255)
							{
								isHaveBound=true;
							}
						}
					}
				}
				if(isHaveBound==false)p0[x]=255;
			}
		}
	}
}

void Sumiao1::showOriginal()
{
	imshow(str1,*MatSrc);
	cv::moveWindow(str1,10,0);
}

void Sumiao1::showGray()
{
	//Êä³ö
	imshow(str2,*MatGray);
	cv::moveWindow(str2,10,100);
}

void Sumiao1::showGrayLvbo()
{
	//Êä³ö
	imshow(str3,*MatGrayLvbo);
	cv::moveWindow(str3,10,200);
}

void Sumiao1::showBinaryGrayLvbo()
{
	//Êä³ö
	imshow(str4,*MatBinaryGrayLvbo);
	cv::moveWindow(str4,10,300);
}

void Sumiao1::showBoundGrayLvbo()
{
	//Êä³ö
	imshow(str5,*MatBoundGrayLvbo);
	cv::moveWindow(str5,10,400);
}

void Sumiao1::showBinaryGrayLvboDelete()
{
	//Êä³ö
	imshow(str6,*MatBinaryGrayLvboDelete);
	cv::moveWindow(str6,10,500);
}
