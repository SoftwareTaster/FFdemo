
// OpenGLScence_MFCView.cpp : COpenGLScence_MFCView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// COpenGLScence_MFCView ����/����

COpenGLScence_MFCView::COpenGLScence_MFCView()
{
	// TODO:  �ڴ˴���ӹ������
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
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;// �ڿͻ�������

	return CView::PreCreateWindow(cs);
}

// COpenGLScence_MFCView ����

void COpenGLScence_MFCView::OnDraw(CDC* /*pDC*/)
{
	COpenGLScence_MFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// COpenGLScence_MFCView ��ӡ


void COpenGLScence_MFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COpenGLScence_MFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void COpenGLScence_MFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void COpenGLScence_MFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}

bool COpenGLScence_MFCView::SetWindowPixelFormat(HDC hDC)
{
	//���崰�ڵ����ظ�ʽ
	PIXELFORMATDESCRIPTOR pixelDesc =
	{
		sizeof(PIXELFORMATDESCRIPTOR),           //nSize�ṹ����
		1,                                       //nVersion�ṹ�汾
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER | PFD_SUPPORT_GDI,        //dwFlags����OpenGL��δ�������
		/*
		wFlags�ܽ������±�־��
		PFD_DRAW_TO_WINDOW ʹ֮���ڴ��ڻ��������豸���ڻ�ͼ��
		PFD_DRAW_TO_BITMAP ʹ֮�����ڴ��е�λͼ��ͼ��
		PFD_SUPPORT_GDI ʹ֮�ܵ���GDI������ע�����ָ����PFD_DOUBLEBUFFER�����ѡ���Ч����
		PFD_SUPPORT_OpenGL ʹ֮�ܵ���OpenGL������
		PFD_GENERIC_FORMAT �����������ظ�ʽ��Windows GDI��������ɵ�����Ӳ���豸��������֧�֣�����ָ����һ�
		PFD_NEED_PALETTE ���߻������Ƿ���Ҫ��ɫ�壬�����������ɫ��ʹ��24�� 32λɫ�����Ҳ��Ḳ�ǵ�ɫ�壻
		PFD_NEED_SYSTEM_PALETTE �����־ָ���������Ƿ��ϵͳ��ɫ�嵱���������ɫ���һ���֣�
		PFD_DOUBLEBUFFER ָ��ʹ����˫��������ע��GDI������ʹ����˫�������Ĵ����л�ͼ����
		PFD_STEREO ָ�����һ������Ƿ�����ͼ������֯��
		PFD_SWAP_LAYER_BUFFERS
		*/
		PFD_TYPE_RGBA,  //iPixelType,��ɫģʽ����������PFD_TYPE_RGBA��ζ��ÿһλ(bit)�������rgb��������ֵ��PFD_TYPE_COLORINDEX��ζ��ÿһλ��������ڲ�ɫ���ұ��е�����ֵ
		24,   //cColorBits������ָ��һ����ɫ��λ������RGBA��˵��λ��������ɫ�к졢�̡�����������ռ��λ��������ɫ������ֵ��˵��ָ���Ǳ��е���ɫ����
		0, 0, 0, 0, 0, 0,  //cRedBits��cRedShifts��cGreenBits��cGreenShifts��cBlueBits��cBlueShifts��,�����������ã�һ����0
		//cRedBits��cGreenBits��cBlueBits������������Ӧ������ʹ�õ�λ����
		//cRedShift��cGreenShift��cBlue-Shift������������������ɫ��ʼ��ƫ������ռ��λ����
		0,                                       //cAlphaBits,RGB��ɫ������Alpha��λ��                            
		0,                                 //cAlphaShift���Ѿ��������ã���0                   
		0,                                       //cAcuumBits�ۼƻ����λ��
		0, 0, 0, 0,                                 //cAcuumRedBits/cAcuumGreenBits/cAcuumBlueBits/cAcuumAlphaBits,�����������ã���0
		32,                                      //cDepthBits��Ȼ����λ��
		0,                                       //cStencilBits,ģ�建���λ��
		0,                                       //cAuxBuffers�����������λ����һ����0
		PFD_MAIN_PLANE,                          //iLayerType,˵����������ͣ��ɺ�����0�������ڵİ汾������
		//PFD_MAIN_PLANE,PFD_OVER_LAY_PLANE,PFD_UNDERLAY_PLANE
		0, 0, 0, 0                                  //bReserved,dwLayerMask,dwVisibleMask,dwDamageMask,������0
	};

	this->m_GLPixelIndex = ChoosePixelFormat(hDC, &pixelDesc);//ѡ������������ظ�ʽ
	/*
	ChoosePixelFormat��������������һ����hDc����һ����һ��ָ��PIXELFORMATDESCRIPTOR�ṹ��ָ��&pixelDesc
	�ú������ش����ظ�ʽ������ֵ,�������0���ʾʧ�ܡ�
	���纯��ʧ�ܣ�����ֻ�ǰ�����ֵ��Ϊ1���� DescribePixelFormat�õ����ظ�ʽ������
	����������һ��û�õ�֧�ֵ����ظ�ʽ����ChoosePixelFormat���᷵������Ҫ������ظ�ʽ��ӽ���һ��ֵ
	һ�����ǵõ�һ�����ظ�ʽ������ֵ����Ӧ�����������ǾͿ��Ե���SetPixelFormat�������ظ�ʽ������ֻ������һ�Ρ�
	*/
	if (this->m_GLPixelIndex == 0)
	{//ѡ��ʧ��
		this->m_GLPixelIndex = 1;//Ĭ�ϵ����ظ�ʽ
		//��Ĭ�ϵ����ظ�ʽ��������
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

	//WglCreateContext��������һ���µ�OpenGL��Ⱦ������(RC)
	//����������������ڻ��Ƶ���hdc���ص��豸
	//�����Ⱦ�������к��豸������(dc)һ�������ظ�ʽ.
	this->m_hGLContext = wglCreateContext(hDC);//����RC

	if (this->m_hGLContext == NULL)
	{//����ʧ��
		return FALSE;
	}

	/*
	wglMakeCurrent �����趨OpenGL��ǰ�߳�(�߳������)����Ⱦ������
	�Ժ�����߳����е�OpenGL���ö��������hdc��ʶ���豸�ϻ��ơ�
	��Ҳ����ʹ��wglMakeCurrent �������ı�����̵߳ĵ�ǰ��Ⱦ����
	ʹ֮�����ǵ�ǰ����Ⱦ������
	*/
	if (wglMakeCurrent(hDC, this->m_hGLContext) == FALSE)
	{//ѡΪ��ǰRCʧ��
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


// COpenGLScence_MFCView ���

#ifdef _DEBUG
void COpenGLScence_MFCView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLScence_MFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLScence_MFCDoc* COpenGLScence_MFCView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLScence_MFCDoc)));
	return (COpenGLScence_MFCDoc*)m_pDocument;
}
#endif //_DEBUG


// COpenGLScence_MFCView ��Ϣ�������


int COpenGLScence_MFCView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	//�õ�һ�����ڶ���CWnd����������ָ��ľ����HWND��  
	HWND hWnd = this->GetSafeHwnd();
	//GetDC�ú�������һָ�����ڵĿͻ������������Ļ����ʾ�豸�����Ļ����ľ��
	//�Ժ������GDI������ʹ�øþ�������豸�����Ļ����л�ͼ��
	HDC hDC = ::GetDC(hWnd);

	if (this->SetWindowPixelFormat(hDC) == FALSE)
	{//�������ظ�ʽ
		return 0;
	}
	if (this->CreateViewGLContext(hDC) == FALSE)
	{//����RC��ѡΪ����
		return 0;
	}
	if (!this->InitGL())
	{//��ʼ��openGL
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

	// TODO:  �ڴ˴������Ϣ����������
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
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CView::OnPaint()
	this->DrawGLScene();
	SwapBuffers(dc.m_hDC);
}


void COpenGLScence_MFCView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnMButtonDown(nFlags, point);
	manager->getInitPos(point.x, point.y);
	midButtonState = true;
}


void COpenGLScence_MFCView::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnMButtonUp(nFlags, point);
	midButtonState = false;
}


void COpenGLScence_MFCView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO:  �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN)
	{

		if (pMsg->wParam == VK_CONTROL)//ֱ�����������Ϳ�����Ӧ��ָ��
		{
			ctrlKeyState = true;
		}

	}

	if (pMsg->message == WM_KEYUP)
	{

		if (pMsg->wParam == VK_CONTROL)//ֱ�����������Ϳ�����Ӧ��ָ��
		{
			ctrlKeyState = false;
		}

	}
	return CView::PreTranslateMessage(pMsg);
}
