#include <Windows.h>
#include <CommDlg.h>
#include <iostream>
#include <string>
#include "Sumiao1.h"
using namespace std;

static OPENFILENAME ofn ;

void PopFileInitialize (HWND hwnd)
{
	static TCHAR szFilter[] = TEXT ("所有图片文件\0*.bmp;*.dib;*.jpg;*.jpeg;*.jpe;*.gif;*.tiff;*.ico\0")  \
		TEXT ("JPEG文件 (*.jpg;*.jpeg;*.jpe)\0*.jpg;*.jpeg;*.jpe\0") \
		TEXT ("位图文件 (*.bmp;*.dib)\0*.bmp;*.dib\0") \
		TEXT ("GIF (*.gif)\0*.gif\0") \
		TEXT ("TIFF (*.tiff)\0*.tiff") \
		TEXT ("ICO (*.ico)\0*.ico\0\0");

	ofn.lStructSize       = sizeof (OPENFILENAME) ;
	ofn.hwndOwner         = hwnd ;
	ofn.hInstance         = NULL ;
	ofn.lpstrFilter       = szFilter ;
	ofn.lpstrCustomFilter = NULL ;
	ofn.nMaxCustFilter    = 0 ;
	ofn.nFilterIndex      = 0 ;
	ofn.lpstrFile         = NULL ;          // Set in Open and Close functions
	ofn.nMaxFile          = MAX_PATH ;
	ofn.lpstrFileTitle    = NULL ;          // Set in Open and Close functions
	ofn.nMaxFileTitle     = MAX_PATH ;
	ofn.lpstrInitialDir   = NULL ;
	ofn.lpstrTitle        = NULL ;
	ofn.Flags             = 0 ;             // Set in Open and Close functions
	ofn.nFileOffset       = 0 ;
	ofn.nFileExtension    = 0 ;
	ofn.lpstrDefExt       = TEXT ("jpg") ;
	ofn.lCustData         = 0L ;
	ofn.lpfnHook          = NULL ;
	ofn.lpTemplateName    = NULL ;
}

BOOL PopFileOpenDlg (HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
{
	ofn.hwndOwner         = hwnd ;
	ofn.lpstrFile         = pstrFileName ;
	ofn.lpstrFileTitle    = pstrTitleName ;
	ofn.Flags             = OFN_HIDEREADONLY | OFN_CREATEPROMPT ;

	return GetOpenFileName (&ofn) ;
}

int main()
{
	static TCHAR     szFileName[MAX_PATH], szTitleName[MAX_PATH] ;
	HWND      hwnd;
	hwnd=GetForegroundWindow(); //获取前台窗口句柄。本程序中的前台窗口就是控制台窗口。 
	PopFileInitialize (hwnd);  //初始化ofn
	PopFileOpenDlg(hwnd, szFileName, szTitleName);//打开文件对话框
	if(strcmp(szFileName,"")==0){cout<<"没有输入\n";return 0;}
	string str(szFileName);
	Sumiao1 test(szFileName);
	test.showOriginal();
	test.showGray();
	test.showGrayLvbo();
	test.showBinaryGrayLvbo();
	test.showBoundGrayLvbo();
	test.showBinaryGrayLvboDelete();

	IplImage saveImage=*(test.MatBinaryGrayLvboDelete);
	cvSaveImage((str.substr(0,str.find("."))+"save.jpg").c_str(),&saveImage);
	cv::waitKey();
	return 0;
}