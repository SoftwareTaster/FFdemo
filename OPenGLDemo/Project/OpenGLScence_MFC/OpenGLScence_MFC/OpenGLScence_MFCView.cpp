
// OpenGLScence_MFCView.cpp : COpenGLScence_MFCView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "OpenGLScence_MFC.h"
#endif

#include"GL/glew.h"
#include"GL/glut.h"
#include "OpenGLScence_MFCDoc.h"
#include "OpenGLScence_MFCView.h"
#include "RoamingScenceManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenGLScence_MFCView

IMPLEMENT_DYNCREATE(COpenGLScence_MFCView, CView)

BEGIN_MESSAGE_MAP(COpenGLScence_MFCView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COpenGLScence_MFCView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
//	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// COpenGLScence_MFCView 构造/析构

COpenGLScence_MFCView::COpenGLScence_MFCView()
{
	// TODO:  在此处添加构造代码
	this->m_GLPixelIndex = 0;
	this->m_hGLContext = NULL;
	midButtonState = false;
	ctrlKeyState = false;
	manager = new RoamingScenceManager();

}

COpenGLScence_MFCView::~COpenGLScence_MFCView()
{

}

BOOL COpenGLScence_MFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;// 在客户区绘制

	return CView::PreCreateWindow(cs);
}

// COpenGLScence_MFCView 绘制

void COpenGLScence_MFCView::OnDraw(CDC* /*pDC*/)
{
	COpenGLScence_MFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// COpenGLScence_MFCView 打印


void COpenGLScence_MFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COpenGLScence_MFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void COpenGLScence_MFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void COpenGLScence_MFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}

bool COpenGLScence_MFCView::SetWindowPixelFormat(HDC hDC)
{
	//定义窗口的像素格式
	PIXELFORMATDESCRIPTOR pixelDesc =
	{
		sizeof(PIXELFORMATDESCRIPTOR),           //nSize结构长度
		1,                                       //nVersion结构版本
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER | PFD_SUPPORT_GDI,        //dwFlags告诉OpenGL如何处理像素
		/*
		wFlags能接收以下标志：
		PFD_DRAW_TO_WINDOW 使之能在窗口或者其他设备窗口画图；
		PFD_DRAW_TO_BITMAP 使之能在内存中的位图画图；
		PFD_SUPPORT_GDI 使之能调用GDI函数（注：如果指定了PFD_DOUBLEBUFFER，这个选项将无效）；
		PFD_SUPPORT_OpenGL 使之能调用OpenGL函数；
		PFD_GENERIC_FORMAT 假如这种象素格式由Windows GDI函数库或由第三方硬件设备驱动程序支持，则需指定这一项；
		PFD_NEED_PALETTE 告诉缓冲区是否需要调色板，本程序假设颜色是使用24或 32位色，并且不会覆盖调色板；
		PFD_NEED_SYSTEM_PALETTE 这个标志指明缓冲区是否把系统调色板当作它自身调色板的一部分；
		PFD_DOUBLEBUFFER 指明使用了双缓冲区（注：GDI不能在使用了双缓冲区的窗口中画图）；
		PFD_STEREO 指明左、右缓冲区是否按立体图像来组织。
		PFD_SWAP_LAYER_BUFFERS
		*/
		PFD_TYPE_RGBA,  //iPixelType,颜色模式，包括两种PFD_TYPE_RGBA意味着每一位(bit)组代表着rgb各分量的值。PFD_TYPE_COLORINDEX意味着每一位组代表着在彩色查找表中的索引值
		24,   //cColorBits定义了指定一个颜色的位数。对RGBA来说，位数是在颜色中红、绿、蓝各分量所占的位数。对颜色的索引值来说，指的是表中的颜色数。
		0, 0, 0, 0, 0, 0,  //cRedBits、cRedShifts、cGreenBits、cGreenShifts、cBlueBits、cBlueShifts用,基本不被采用，一般置0
		//cRedBits、cGreenBits、cBlueBits用来表明各相应分量所使用的位数。
		//cRedShift、cGreenShift、cBlue-Shift用来表明各分量从颜色开始的偏移量所占的位数。
		0,                                       //cAlphaBits,RGB颜色缓存中Alpha的位数                            
		0,                                 //cAlphaShift，已经不被采用，置0                   
		0,                                       //cAcuumBits累计缓存的位数
		0, 0, 0, 0,                                 //cAcuumRedBits/cAcuumGreenBits/cAcuumBlueBits/cAcuumAlphaBits,基本不被采用，置0
		32,                                      //cDepthBits深度缓存的位数
		0,                                       //cStencilBits,模板缓存的位数
		0,                                       //cAuxBuffers，辅助缓存的位数，一般置0
		PFD_MAIN_PLANE,                          //iLayerType,说明层面的类型，可忽略置0，是早期的版本，包括
		//PFD_MAIN_PLANE,PFD_OVER_LAY_PLANE,PFD_UNDERLAY_PLANE
		0, 0, 0, 0                                  //bReserved,dwLayerMask,dwVisibleMask,dwDamageMask,必须置0
	};

	this->m_GLPixelIndex = ChoosePixelFormat(hDC, &pixelDesc);//选择最相近的像素格式
	/*
	ChoosePixelFormat接受两个参数：一个是hDc，另一个是一个指向PIXELFORMATDESCRIPTOR结构的指针&pixelDesc
	该函数返回此像素格式的索引值,如果返回0则表示失败。
	假如函数失败，我们只是把索引值设为1并用 DescribePixelFormat得到像素格式描述。
	假如你申请一个没得到支持的像素格式，则ChoosePixelFormat将会返回与你要求的像素格式最接近的一个值
	一旦我们得到一个像素格式的索引值和相应的描述，我们就可以调用SetPixelFormat设置像素格式，并且只需设置一次。
	*/
	if (this->m_GLPixelIndex == 0)
	{//选择失败
		this->m_GLPixelIndex = 1;//默认的像素格式
		//用默认的像素格式进行设置
		//
		if (DescribePixelFormat(hDC, this->m_GLPixelIndex, sizeof(PIXELFORMATDESCRIPTOR), &pixelDesc) == 0)
		{
			return FALSE;
		}
	}

	if (SetPixelFormat(hDC, this->m_GLPixelIndex, &pixelDesc) == FALSE)
	{
		return FALSE;
	}
	return TRUE;

}

bool COpenGLScence_MFCView::CreateViewGLContext(HDC hDC)
{

	//WglCreateContext函数创建一个新的OpenGL渲染描述表(RC)
	//此描述表必须适用于绘制到由hdc返回的设备
	//这个渲染描述表将有和设备上下文(dc)一样的像素格式.
	this->m_hGLContext = wglCreateContext(hDC);//创建RC

	if (this->m_hGLContext == NULL)
	{//创建失败
		return FALSE;
	}

	/*
	wglMakeCurrent 函数设定OpenGL当前线程(线程相关性)的渲染环境。
	以后这个线程所有的OpenGL调用都是在这个hdc标识的设备上绘制。
	你也可以使用wglMakeCurrent 函数来改变调用线程的当前渲染环境
	使之不再是当前的渲染环境。
	*/
	if (wglMakeCurrent(hDC, this->m_hGLContext) == FALSE)
	{//选为当前RC失败
		return FALSE;
	}
	return TRUE;

}

bool COpenGLScence_MFCView::InitGL(void)
{
	manager->init();
	return true;
}

int COpenGLScence_MFCView::DrawGLScene(void)
{
	manager->render();
	glFlush();
	return TRUE;                                
}

void COpenGLScence_MFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COpenGLScence_MFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COpenGLScence_MFCView 诊断

#ifdef _DEBUG
void COpenGLScence_MFCView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLScence_MFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLScence_MFCDoc* COpenGLScence_MFCView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLScence_MFCDoc)));
	return (COpenGLScence_MFCDoc*)m_pDocument;
}
#endif //_DEBUG


// COpenGLScence_MFCView 消息处理程序


int COpenGLScence_MFCView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	//得到一个窗口对象（CWnd的派生对象）指针的句柄（HWND）  
	HWND hWnd = this->GetSafeHwnd();
	//GetDC该函数检索一指定窗口的客户区域或整个屏幕的显示设备上下文环境的句柄
	//以后可以在GDI函数中使用该句柄来在设备上下文环境中绘图。
	HDC hDC = ::GetDC(hWnd);

	if (this->SetWindowPixelFormat(hDC) == FALSE)
	{//设置像素格式
		return 0;
	}
	if (this->CreateViewGLContext(hDC) == FALSE)
	{//创建RC并选为所用
		return 0;
	}
	if (!this->InitGL())
	{//初始化openGL
		return 0;
	}
	return 0;
}


void COpenGLScence_MFCView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	glViewport(0, -(cx - cy) / 2, cx, cx);
}


void COpenGLScence_MFCView::OnDestroy()
{
	CView::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
	if (wglGetCurrentContext() != NULL)
	{
		wglMakeCurrent(NULL, NULL);
	}
	if (this->m_hGLContext != NULL)
	{
		wglDeleteContext(this->m_hGLContext);
		this->m_hGLContext = NULL;
	}

	delete manager;
	manager = NULL;
}


void COpenGLScence_MFCView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CView::OnPaint()
	this->DrawGLScene();
	SwapBuffers(dc.m_hDC);
}


void COpenGLScence_MFCView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CView::OnMButtonDown(nFlags, point);
	manager->getInitPos(point.x, point.y);
	midButtonState = true;
}


void COpenGLScence_MFCView::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CView::OnMButtonUp(nFlags, point);
	midButtonState = false;
}


void COpenGLScence_MFCView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CView::OnMouseMove(nFlags, point);
	if (midButtonState)
	{
		if (ctrlKeyState)
		{
			manager->executeTranslateOperation(point.x, point.y);
		} 
		else
		{
			manager->executeRotateOperation(point.x, point.y);
		}
		
		OnPaint();
	}
}


BOOL COpenGLScence_MFCView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (zDelta>=0)
	{
		manager->executeScaleOperation(-0.1);
	}
	else
	{
		manager->executeScaleOperation(0.1);
	}
	OnPaint();

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}



BOOL COpenGLScence_MFCView::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{

		if (pMsg->wParam == VK_CONTROL)//直接用虚码代替就可以响应所指键
		{
			ctrlKeyState = true;
		}

	}

	if (pMsg->message == WM_KEYUP)
	{

		if (pMsg->wParam == VK_CONTROL)//直接用虚码代替就可以响应所指键
		{
			ctrlKeyState = false;
		}

	}
	return CView::PreTranslateMessage(pMsg);
}
