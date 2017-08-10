
// FaceMatchDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FaceMatch.h"
#include "FaceMatchDlg.h"
#include "afxdialogex.h"
#include "opencv\cv.h"  
#include <atlconv.h>

using namespace std;  
using namespace cv;  

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFaceMatchDlg 对话框




CFaceMatchDlg::CFaceMatchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFaceMatchDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFaceMatchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFaceMatchDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN_BUTTON, &CFaceMatchDlg::OnBnClickedOpenButton)
	ON_BN_CLICKED(IDC_MATCH_BUTTON, &CFaceMatchDlg::OnBnClickedMatchButton)
END_MESSAGE_MAP()


// CFaceMatchDlg 消息处理程序

BOOL CFaceMatchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
// 	CRect temprect(0,0,640,480);
// 	CWnd::SetWindowPos(NULL,0,0,temprect.Width(),temprect.Height(),SWP_NOZORDER|SWP_NOMOVE);
	namedWindow("view", WINDOW_AUTOSIZE);
	HWND hWnd = (HWND) cvGetWindowHandle("view");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_STATIC_JPG2)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);
	
	namedWindow("view1", WINDOW_AUTOSIZE);
	HWND hhWnd = (HWND) cvGetWindowHandle("view1");
	HWND hhParent = ::GetParent(hhWnd);
	::SetParent(hhWnd, GetDlgItem(IDC_STATIC_JPG1)->m_hWnd);
	::ShowWindow(hhParent, SW_HIDE);

	namedWindow("view2", WINDOW_AUTOSIZE);
	HWND hhhWnd = (HWND) cvGetWindowHandle("view2");
	HWND hhhParent = ::GetParent(hhhWnd);
	::SetParent(hhhWnd, GetDlgItem(IDC_STATIC_JPG3)->m_hWnd);
	::ShowWindow(hhhParent, SW_HIDE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFaceMatchDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFaceMatchDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFaceMatchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


  string ss;
void CFaceMatchDlg::OnBnClickedOpenButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CImage image;
	CFileDialog fileDlg(TRUE, _T("jpg"), NULL, 0, _T("jpg Files(*.jpg)|*.jpg||"), this);
	fileDlg.DoModal();
	CString strFilePath;
	strFilePath = fileDlg.GetPathName();
	if (strFilePath == _T(""))
	{
		return;
	}
	USES_CONVERSION;
	 ss = W2CA((LPCWSTR)strFilePath);
	Mat b=imread(ss);
	cv::Mat m_dst;
	CRect rect;
	GetDlgItem(IDC_STATIC_JPG1)->GetClientRect(&rect);
	cv::Rect dst(rect.left,rect.top,rect.right,rect.bottom);
	cv::resize(b,m_dst,Size(rect.Width(),rect.Height())); 
	imshow("view1",m_dst);
// 	CRect rc;
// 	GetDlgItem(IDC_STATIC_JPG1)->GetClientRect(rc);
// 	
// 	image.Load(strFilePath); //图片文件路径
// 	if (image.GetBPP() == 32)
// 	{
// 		int i; int j;
// 		for (i = 0; i < image.GetWidth(); i++)
// 		{
// 			for (j = 0; j < image.GetHeight(); j++)
// 			{
// 				byte *pByte = (byte *)image.GetPixelAddress(i, j);
// 				pByte[0] = pByte[0] * pByte[3] / 255;
// 				pByte[1] = pByte[1] * pByte[3] / 255;
// 				pByte[2] = pByte[2] * pByte[3] / 255;
// 			}
// 		}
// 	}
// 	CDC* dc;
// 	dc = GetDlgItem(IDC_STATIC_JPG1)->GetDC();
// 
// 	image.Draw(dc->m_hDC, rc);
// 
// 	ReleaseDC(dc);
}

String cascadeName = "E:\\Program\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";  

IplImage* cutImage(IplImage* src, CvRect rect) {  
	cvSetImageROI(src, rect);  
	IplImage* dst = cvCreateImage(cvSize(rect.width, rect.height),  
		src->depth,  
		src->nChannels);  
	cvCopy(src,dst,0);  
	cvResetImageROI(src);  
	return dst;  
}  

IplImage* detect( Mat& img, CascadeClassifier& cascade, double scale)  
{  
	int i = 0;  
	double t = 0;  
	vector<Rect> faces;  
	Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );  
	cvtColor( img, gray, CV_BGR2GRAY );  
	resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );  
	equalizeHist( smallImg, smallImg );  
	cascade.detectMultiScale( smallImg, faces,1.3, 2,CV_HAAR_SCALE_IMAGE,Size(30, 30) );  	
	for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++ )  
	{  
		IplImage* temp = cutImage(&(IplImage(img)), cvRect(r->x, r->y, r->width, r->height));  
		return temp;  
	}  
	return NULL;  
}  

void CFaceMatchDlg::OnBnClickedMatchButton()
{
	// TODO: 在此添加控件通知处理程序代码
// 
// 	INT_PTR nRes;
// 	CTipDlg tipDlg;
// 	tipDlg.DoModal();
	//if(IDCANCEL==nRes)
		//return;	
	string dir_path = "C:/Users/Administrator/Desktop/人脸匹配系统/FaceMatch/目标图库/";  
	Directory dir;  
	vector<string> fileNames = dir.GetListFiles(dir_path, "*.bmp", false);  
	vector<int>vec;
	vector<Mat>vec1;

	for(size_t i = 0; i < fileNames.size(); i++)  
	{  
		string fileName = fileNames[i];  
		string targetImage = dir_path + fileName;  
	
		String srcImage = ss;
    	
		CascadeClassifier cascade;  
		
		if( !cascade.load( cascadeName ) )  
		{  
			
			return ;  
		}  

		Mat srcImg, targetImg,srcImg1;
		IplImage* faceImage1;  
		IplImage* faceImage2;  
		srcImg = imread(srcImage);  
	
		targetImg = imread(targetImage); 
		vec1.push_back(targetImg);
		faceImage1 = detect(srcImg, cascade, 1);  
		if (faceImage1 == NULL) 
		{  
			INT_PTR nRes;
			CReminderDlg reminderDlg;
			nRes=reminderDlg.DoModal();
			if(IDOK==nRes)
			return ;  
		}  
		Mat a=Mat::zeros(targetImg.size(),targetImg.type());
	
		cvtColor(Mat(faceImage1),srcImg1,CV_BGR2GRAY);
		resize( srcImg1, a, targetImg.size(), 0, 0, INTER_LINEAR ); 
		
		cv::Mat m_dst;
		CRect rect;
		GetDlgItem(IDC_STATIC_JPG3)->GetClientRect(&rect);
		cv::Rect dst(rect.left,rect.top,rect.right,rect.bottom);
		cv::resize(a,m_dst,Size(rect.Width(),rect.Height())); 
		imshow("view2",m_dst);
	
		int sum=0;
		int rowNumber = targetImg.rows;  //行数
		int colNumber = targetImg.cols*targetImg.channels();  //列数 x 通道数=每一行元素的个数
		//双重循环，遍历所有的像素值
		for(int i = 0;i < rowNumber;i++)  //行循环
		{  
			uchar* data1 = a.ptr<uchar>(i);  //获取第i行的首地址
			uchar* data2 = targetImg.ptr<uchar>(i);  //
			for(int j = 0;j < colNumber;j++)   //列循环
			{  	
				// ---------【开始处理每个像素】-------------     
				sum+= abs(data1[j]-data2[j]);  
				// ----------【处理结束】---------------------
			}  //行处理结束
		}  
		//cout<<sum<<endl;
		vec.push_back(sum);
		//CompareHist(faceImage1, faceImage2);  
	
		cvReleaseImage(&faceImage1);  
		//cvReleaseImage(&faceImage2); 
	} 
	
	int min;
	int nPosition;
	vector<int>::iterator it1 = vec.begin();
	min=*it1;
	for (it1;it1 != vec.end(); ++it1)  
	{  
		if(*it1<min) min=*it1; 
	}  
	
	vector <int>::iterator iElement = find(vec.begin(),vec.end(),min); 
	if( iElement != vec.end() )  
	{  
		nPosition = distance(vec.begin(),iElement);  
		
		string fileName = fileNames[nPosition];  
		
		Mat targetImg2=vec1.at(nPosition);
		cv::Mat m_dst;
		CRect rect;
		GetDlgItem(IDC_STATIC_JPG2)->GetClientRect(&rect);
		cv::Rect dst(rect.left,rect.top,rect.right,rect.bottom);
		cv::resize(targetImg2,m_dst,Size(rect.Width(),rect.Height())); 
		imshow("view",m_dst);
		
	}  

// 	return EXIT_SUCCESS;  
 	return;

}
