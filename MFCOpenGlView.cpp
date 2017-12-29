
// MFCOpenGlView.cpp : CMFCOpenGlView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCOpenGl.h"
#endif

#include "MFCOpenGlDoc.h"
#include "MFCOpenGlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCOpenGlView

IMPLEMENT_DYNCREATE(CMFCOpenGlView, CView)

BEGIN_MESSAGE_MAP(CMFCOpenGlView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMFCOpenGlView 构造/析构

CMFCOpenGlView::CMFCOpenGlView() : gldraw()
{
	// TODO: 在此处添加构造代码
	m_hRC = NULL;
	m_pDC = NULL;
	Normallight = false;
}

CMFCOpenGlView::~CMFCOpenGlView()
{
}

BOOL CMFCOpenGlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

	return CView::PreCreateWindow(cs);
}

// CMFCOpenGlView 绘制

void CMFCOpenGlView::OnDraw(CDC* /*pDC*/)
{
	CMFCOpenGlDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	//RenderScene();
	gldraw.RenderScene3(m_wide, m_heigth);
	//gldraw.RenderScene3(m_wide, m_heigth);
}


// CMFCOpenGlView 打印

BOOL CMFCOpenGlView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCOpenGlView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCOpenGlView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCOpenGlView 诊断

#ifdef _DEBUG
void CMFCOpenGlView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCOpenGlView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCOpenGlDoc* CMFCOpenGlView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCOpenGlDoc)));
	return (CMFCOpenGlDoc*)m_pDocument;
}
#endif //_DEBUG





// CMFCOpenGlView 消息处理程序
BOOL CMFCOpenGlView::InitializeOpenGL()
{
	PIXELFORMATDESCRIPTOR pfd;
	int n;
	m_pDC = new CClientDC(this);
	ASSERT(m_pDC != NULL);
	// 设置当前的绘图像素格式  
	if (!SetupPixelFormat())
	{
		return FALSE;
	}

	n = ::GetPixelFormat(m_pDC->GetSafeHdc());
	::DescribePixelFormat(m_pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);
	// 创建绘图描述表  
	m_hRC = wglCreateContext(m_pDC->GetSafeHdc());
	if (m_hRC == NULL)
	{
		return FALSE;
	}
	// 使绘图描述表为当前调用现程的当前绘图描述表  
	if (wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC) == FALSE)
	{
		return FALSE;
	}
	gldraw.map.init();

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	return TRUE;
}

BOOL CMFCOpenGlView::SetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // pfd结构的大小   
		1,                              // 版本号   
		PFD_DRAW_TO_WINDOW |            // 支持在窗口中绘图   
		PFD_SUPPORT_OPENGL |            // 支持 OpenGL   
		PFD_DOUBLEBUFFER,               // 双缓存模式   
		PFD_TYPE_RGBA,                  // RGBA 颜色模式   
		24,                             // 24 位颜色深度   
		0, 0, 0, 0, 0, 0,               // 忽略颜色位   
		0,                              // 没有非透明度缓存   
		0,                              // 忽略移位位   
		0,                              // 无累计缓存   
		0, 0, 0, 0,                     // 忽略累计位   
		32,                             // 32 位深度缓存       
		0,                              // 无模板缓存   
		0,                              // 无辅助缓存   
		PFD_MAIN_PLANE,                 // 主层   
		0,                              // 保留   
		0, 0, 0                         // 忽略层,可见性和损毁掩模   

	};
	int pixelFormat;
	// 为设备描述表得到最匹配的像素格式   
	if ((pixelFormat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == 0)
	{
		MessageBox(_T("ChoosePixelFormat failed"));
		return FALSE;
	}
	// 设置最匹配的像素格式为当前的像素格式   
	if (SetPixelFormat(m_pDC->GetSafeHdc(), pixelFormat, &pfd) == FALSE)
	{
		MessageBox(_T("SetPixelFormat failed"));
		return FALSE;
	}
	return TRUE;
}

void CMFCOpenGlView::RenderScene()
{
	
	//设置清屏颜色为黑色  
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//清除颜色缓冲区和深度缓冲区  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//透视投影变换  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (double)m_wide / (double)m_heigth, 10, 1000);
	//视角变换  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(10, 10, 10, 0, 0, 0, 1, 0, 0);
	//矩阵堆栈函数，和glPopMatrix()相对应  
	glPushMatrix();

	glBegin(GL_LINES);
	glColor3d(1.0, 0.0, 0.0);   // X轴 红色  
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(3.0, 0.0, 0.0);
	glColor3d(0.0, 1.0, 0.0);   // Y轴 绿色  
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 2.0, 0.0);
	glColor3d(0.0, 0.0, 1.0);   // Z轴 蓝色  
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, 2.0);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glutWireCube(0.5);

	glPopMatrix();
	glFinish();
	SwapBuffers(wglGetCurrentDC());
	
}

//光照
void CMFCOpenGlView::NormalLight()
{
	GLfloat light_position[] = { 1.0,1.0,1.0,0.0 };
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	if (Normallight)
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		Normallight = false;
	}
	else
	{
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_COLOR_MATERIAL);
		glLightModeli(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		Normallight = true;
	}
}


int CMFCOpenGlView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	if (InitializeOpenGL())
	{
		SetTimer(1, 20, NULL);
		return 0;
	}
	return 0;
}


void CMFCOpenGlView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	m_wide = cx;    //m_wide为在CVCOpenGL2View类中添加的表示视口宽度的成员变量  
	m_heigth = cy;  //m_height为在CVCOpenGL2View类中添加的表示视口高度的成员变量  
					//避免除数为0  
	if (m_heigth == 0)
	{
		m_heigth = 1;
	}
	//设置视口与窗口的大小  
	glViewport(0, 0, m_wide, m_heigth);
}


void CMFCOpenGlView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	char cChar;//当前被按下的字符
	HCURSOR hCursor = 0;//显示光标句柄
	HCURSOR hPrevCursor = 0;//以前的光标句柄
	cChar = char(nChar);//将按下的键转换为字符
	if (cChar == 'D') {
		//加载箭头光标
		hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		printf("1");
		gldraw.updateX(1);
		this->OnDraw(NULL);
	}
	if (cChar == 'A') {
		//加载箭头光标
		hCursor = AfxGetApp()->LoadStandardCursor(IDC_IBEAM);
		gldraw.updateX(-1);
		this->OnDraw(NULL);
	}
	if (cChar == 'W') {
		//加载箭头光标
		hCursor = AfxGetApp()->LoadStandardCursor(IDC_WAIT);
		gldraw.updateY(1);
		this->OnDraw(NULL);
	}
	if (cChar == 'S') {
		//加载箭头光标
		hCursor = AfxGetApp()->LoadStandardCursor(IDC_WAIT);
		gldraw.updateY(-1);
		this->OnDraw(NULL);
	}
	if (cChar == 'Q') {
		//加载箭头光标
		hCursor = AfxGetApp()->LoadStandardCursor(IDC_WAIT);
		gldraw.updateZ(1);
		this->OnDraw(NULL);
	}
	if (cChar == 'E') {
		//加载箭头光标
		hCursor = AfxGetApp()->LoadStandardCursor(IDC_WAIT);
		gldraw.updateZ(-1);
		this->OnDraw(NULL);
	}
	if (cChar == 'X') {
		hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		hPrevCursor = SetCursor(hCursor);
		if (hPrevCursor)
			DestroyCursor(hPrevCursor);
		exit(0);//退出应用
	}
	if (cChar == 'N') {
		hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		NormalLight();
		this->OnDraw(NULL);
	}
	else {
		if (hCursor) {
			hPrevCursor = SetCursor(hCursor);
			if (hPrevCursor)
				DestroyCursor(hPrevCursor);
		}
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMFCOpenGlView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	gldraw.updateHeadRot(1);
	this->OnDraw(NULL);

	CView::OnTimer(nIDEvent);
}
