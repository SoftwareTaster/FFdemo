
// OpenGLScence_MFCView.h : COpenGLScence_MFCView ��Ľӿ�
//

#pragma once

class RoamingScenceManager;
class COpenGLScence_MFCView : public CView
{
protected: // �������л�����
	COpenGLScence_MFCView();
	DECLARE_DYNCREATE(COpenGLScence_MFCView)

// ����
public:
	COpenGLScence_MFCDoc* GetDocument() const;

// ����
public:
	bool midButtonState;
	bool ctrlKeyState;
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);


	/*************************************************/
	bool SetWindowPixelFormat(HDC hDC);
	// �������ƻ���(RC)��ʹ֮��Ϊ��ǰ���ƻ���   
	bool CreateViewGLContext(HDC hDC);
	// ��ʼ��openGL
	bool InitGL(void);
	// ��ͼ������
	int DrawGLScene(void);
	//>���ظ�ʽ������ֵ
	int m_GLPixelIndex;
	// ���ƻ�����HGLRC��һ��ָ��rendering context�ľ��
	HGLRC m_hGLContext;
	/*************************************************/

	RoamingScenceManager*manager;
// ʵ��
public:
	virtual ~COpenGLScence_MFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

#ifndef _DEBUG  // OpenGLScence_MFCView.cpp �еĵ��԰汾
inline COpenGLScence_MFCDoc* COpenGLScence_MFCView::GetDocument() const
   { return reinterpret_cast<COpenGLScence_MFCDoc*>(m_pDocument); }
#endif

