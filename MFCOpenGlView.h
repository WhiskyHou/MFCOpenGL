
// MFCOpenGlView.h : CMFCOpenGlView 类的接口
//

#pragma once
#include"GLDraw.h"

class CMFCOpenGlView : public CView
{
protected: // 仅从序列化创建
	CMFCOpenGlView();
	DECLARE_DYNCREATE(CMFCOpenGlView)

public:
	GLDraw gldraw;
	int m_wide;
	int m_heigth;
	HGLRC m_hRC;    //Rendering Context着色描述表  
	CClientDC* m_pDC;        //Device Context设备描述表  
	BOOL InitializeOpenGL();    //初始化 OpenGL  
	BOOL SetupPixelFormat();    //设置像素格式  
	void RenderScene();         //绘制场景 
	void NormalLight();
	bool Normallight;

// 特性
public:
	CMFCOpenGlDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCOpenGlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // MFCOpenGlView.cpp 中的调试版本
inline CMFCOpenGlDoc* CMFCOpenGlView::GetDocument() const
   { return reinterpret_cast<CMFCOpenGlDoc*>(m_pDocument); }
#endif

