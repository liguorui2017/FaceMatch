
// FaceMatchDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CFaceMatchDlg �Ի���




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


// CFaceMatchDlg ��Ϣ�������

BOOL CFaceMatchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFaceMatchDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFaceMatchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


  string ss;
void CFaceMatchDlg::OnBnClickedOpenButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
// 	image.Load(strFilePath); //ͼƬ�ļ�·��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
// 
// 	INT_PTR nRes;
// 	CTipDlg tipDlg;
// 	tipDlg.DoModal();
	//if(IDCANCEL==nRes)
		//return;	
	string dir_path = "C:/Users/Administrator/Desktop/����ƥ��ϵͳ/FaceMatch/Ŀ��ͼ��/";  
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
		int rowNumber = targetImg.rows;  //����
		int colNumber = targetImg.cols*targetImg.channels();  //���� x ͨ����=ÿһ��Ԫ�صĸ���
		//˫��ѭ�����������е�����ֵ
		for(int i = 0;i < rowNumber;i++)  //��ѭ��
		{  
			uchar* data1 = a.ptr<uchar>(i);  //��ȡ��i�е��׵�ַ
			uchar* data2 = targetImg.ptr<uchar>(i);  //
			for(int j = 0;j < colNumber;j++)   //��ѭ��
			{  	
				// ---------����ʼ����ÿ�����ء�-------------     
				sum+= abs(data1[j]-data2[j]);  
				// ----------�����������---------------------
			}  //�д������
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
