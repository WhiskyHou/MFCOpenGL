
// MFCOpenGlView.h : CMFCOpenGlView ��Ľӿ�
//

#pragma once
#include"GLDraw.h"

class CMFCOpenGlView : public CView
{
protected: // �������л�����
	CMFCOpenGlView();
	DECLARE_DYNCREATE(CMFCOpenGlView)

public:
	GLDraw gldraw;
	int m_wide;
	int m_heigth;
	HGLRC m_hRC;    //Rendering Context��ɫ������  
	CClientDC* m_pDC;        //Device Context�豸������  
	BOOL InitializeOpenGL();    //��ʼ�� OpenGL  
	BOOL SetupPixelFormat();    //�������ظ�ʽ  
	void RenderScene();         //���Ƴ��� 
	void NormalLight();
	bool Normallight;

// ����
public:
	CMFCOpenGlDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMFCOpenGlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // MFCOpenGlView.cpp �еĵ��԰汾
inline CMFCOpenGlDoc* CMFCOpenGlView::GetDocument() const
   { return reinterpret_cast<CMFCOpenGlDoc*>(m_pDocument); }
#endif

