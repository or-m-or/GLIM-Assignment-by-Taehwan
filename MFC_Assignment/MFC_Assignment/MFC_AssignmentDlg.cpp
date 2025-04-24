#include "pch.h"
#include "framework.h"
#include "MFC_Assignment.h"
#include "MFC_AssignmentDlg.h"
#include "afxdialogex.h"
#include "Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/*---------------------
  CAboutDlg 대화 상자
----------------------*/

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX) { }
void CAboutDlg::DoDataExchange(CDataExchange* pDX) { CDialogEx::DoDataExchange(pDX); }
void CAboutDlg::OnBnClickedOk() { CDialogEx::OnOK(); }

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


/*-----------------------------
  CMFCAssignmentDlg 대화 상자
-------------------------------*/

CMFCAssignmentDlg::CMFCAssignmentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_ASSIGNMENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCAssignmentDlg::DoDataExchange(CDataExchange* pDX)
{ 
	CDialogEx::DoDataExchange(pDX);							// 부모 클래스 바인딩
	DDX_Control(pDX, IDC_EDIT_DOT_RADIUS, m_editRadius);	// Edit Control(클릭 지점 원 반지름) <-> m_editRadius 변수 연결
	DDX_Control(pDX, IDC_STATIC_POINT1, m_staticPoint1);	// Static Text(클릭 지점 좌표)
	DDX_Control(pDX, IDC_STATIC_POINT2, m_staticPoint2);
	DDX_Control(pDX, IDC_STATIC_POINT3, m_staticPoint3);
	DDX_Control(pDX, IDC_EDIT_CIRCLE_THICKNESS, m_editThickness);	// Edit Control(정원 두께) <-> m_editThickness
	DDX_Control(pDX, IDC_STATIC_CIRCLE_CENTER, m_staticCenter);
	DDX_Control(pDX, IDC_STATIC_CIRCLE_RADIUS, m_staticRadius);
}

BEGIN_MESSAGE_MAP(CMFCAssignmentDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN() // 마우스 클릭 시 처리 함수
	ON_BN_CLICKED(IDOK, &CMFCAssignmentDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCAssignmentDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_INITIMAGE, &CMFCAssignmentDlg::OnBnClickedBtnInitBackBuffer)
END_MESSAGE_MAP()


// CMFCAssignmentDlg 메시지 처리기
BOOL CMFCAssignmentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 함
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정
	// 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	// 프레임워크가 이 작업을 자동으로 수행
	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		

	InitCanvas(); // 백버퍼 초기화
	m_editRadius.SetWindowText(_T("10"));	// 클릭 지점 원 반지름
	m_editThickness.SetWindowText(_T("5")); // 정원 두께

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환
}

void CMFCAssignmentDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면 아래 코드 필요
// 문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는 프레임워크에서 이 작업을 자동으로 수행
void CMFCAssignmentDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춤
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		m_canvas.Present(&dc, m_drawX, m_drawY);
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시
HCURSOR CMFCAssignmentDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 마우스 클릭 시 클릭 지점 원 그리기
void CMFCAssignmentDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 3개 초과 시 무시
	if (m_dots.Size() >= 3) return;

	CString radiusText;
	// 클릭 지점 원 반지름
	m_editRadius.GetWindowText(radiusText);
	m_radius = _ttoi(radiusText);  // 문자열 → 정수 변환
	if (m_radius <= 0) m_radius = 10;

	// 정원 두께
	CString thicknessText;
	m_editThickness.GetWindowText(thicknessText); // 두께 입력값 가져오기
	m_thickness = _ttoi(thicknessText);
	if (m_thickness <= 0) m_thickness = 5;

	// 클릭한 좌표 저장
	m_dots.Add(point);
	UpdatePointLabels(); 	// Static Text에 좌표 표시

	// 클릭 지점에서 백버퍼 내 좌표로 계산
	CPoint local(point.x - m_drawX, point.y - m_drawY);

	// 백버퍼 영역 내에서만 그림
	if (local.x >= 0 && local.y >= 0 
		&& local.x < m_canvas.GetWidth() 
		&& local.y < m_canvas.GetHeight())
	{
		m_canvas.DrawDot(local.x, local.y, m_radius); // 점 그리기
	}

	// 3점 클릭 시 정원 그리기
	if (m_dots.Size() == 3)
	{
		CPoint center;
		double radius;
		CPoint p1 = m_dots.GetPoint(0) - CPoint(m_drawX, m_drawY);
		CPoint p2 = m_dots.GetPoint(1) - CPoint(m_drawX, m_drawY);
		CPoint p3 = m_dots.GetPoint(2) - CPoint(m_drawX, m_drawY);

		if (Utils::GetCircleFromThreePoints(p1, p2, p3, center, radius))
		{
			m_canvas.DrawCircle(center, radius, m_thickness); 

			// 중심 좌표와 반지름 UI 표시
			CString centerStr, radiusStr;
			centerStr.Format(_T("정원 중심: (%d, %d)"), center.x, center.y);
			radiusStr.Format(_T("정원 반지름: %.2f"), radius);
			m_staticCenter.SetWindowText(centerStr);
			m_staticRadius.SetWindowText(radiusStr);
		}
	}

	Invalidate(); // 화면 갱신
	CDialogEx::OnLButtonDown(nFlags, point);
}

// OK 버튼 (닫기)
void CMFCAssignmentDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}

// 취소 버튼
void CMFCAssignmentDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}

// 초기화 버튼
void CMFCAssignmentDlg::OnBnClickedBtnInitBackBuffer()
{
	InitCanvas();			// 캔버스 초기화
	m_dots.Clear();			// 클릭 지점 좌표 초기화
	ResetPointLabels();     // 클릭 지점 원 좌표 표시 라벨 초기화
	ResetCircleLabels();	// 정원 정보 표시 라벨 초기화
	Invalidate();			// 화면 갱신
}

void CMFCAssignmentDlg::InitCanvas()
{
	m_canvas.Init(m_bufferWidth, m_bufferHeight);
}

void CMFCAssignmentDlg::UpdatePointLabels()
{
	if (m_dots.Size() > 0)
	{
		CPoint pt = m_dots.GetPoint(0);
		CString txt;
		txt.Format(_T("클릭 지점 1: (%d, %d)"), pt.x, pt.y);
		m_staticPoint1.SetWindowText(txt);
	}
	if (m_dots.Size() > 1)
	{
		CPoint pt = m_dots.GetPoint(1);
		CString txt;
		txt.Format(_T("클릭 지점 2: (%d, %d)"), pt.x, pt.y);
		m_staticPoint2.SetWindowText(txt);
	}
	if (m_dots.Size() > 2)
	{
		CPoint pt = m_dots.GetPoint(2);
		CString txt;
		txt.Format(_T("클릭 지점 3: (%d, %d)"), pt.x, pt.y);
		m_staticPoint3.SetWindowText(txt);
	}
}

void CMFCAssignmentDlg::ResetPointLabels()
{
	m_staticPoint1.SetWindowText(_T("클릭 지점 1: -"));
	m_staticPoint2.SetWindowText(_T("클릭 지점 2: -"));
	m_staticPoint3.SetWindowText(_T("클릭 지점 3: -"));
}

void CMFCAssignmentDlg::ResetCircleLabels()
{
	m_staticCenter.SetWindowText(_T("정원 중심: -"));
	m_staticRadius.SetWindowText(_T("정원 반지름: -"));
}
