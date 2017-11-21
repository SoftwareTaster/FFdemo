
// OpenGLScence_MFCView.h : COpenGLScence_MFCView 类的接口
//

#pragma once

class RoamingScenceManager;
class COpenGLScence_MFCView : public CView
{
protected: // 仅从序列化创建
	COpenGLScence_MFCView();
	DECLARE_DYNCREATE(COpenGLScence_MFCView)

// 特性
public:
	COpenGLScence_MFCDoc* GetDocument() const;

// 操作
public:
	bool midButtonState;
	bool ctrlKeyState;
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);


	/*************************************************/
	bool SetWindowPixelFormat(HDC hDC);
	// 创建绘制环境(RC)并使之成为当前绘制环境   
	bool CreateViewGLContext(HDC hDC);
	// 初始化openGL
	bool InitGL(void);
	// 绘图代码区
	int DrawGLScene(void);
	//>像素格式的索引值
	int m_GLPixelIndex;
	// 绘制环境，HGLRC是一个指向rendering context的句柄
	HGLRC m_hGLContext;
	/*************************************************/

	RoamingScenceManager*manager;
// 实现
public:
	virtual ~COpenGLScence_MFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // OpenGLScence_MFCView.cpp 中的调试版本
inline COpenGLScence_MFCDoc* COpenGLScence_MFCView::GetDocument() const
   { return reinterpret_cast<COpenGLScence_MFCDoc*>(m_pDocument); }
#endif

