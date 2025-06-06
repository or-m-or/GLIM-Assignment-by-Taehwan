﻿#include "pch.h"
#include "framework.h"
#include "MFC_Assignment.h"
#include "MFC_AssignmentDlg.h"
#include "afxdialogex.h"

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
	ON_WM_MOUSEMOVE()	// 드래그
	ON_WM_LBUTTONUP()	// 클릭 해제
	ON_BN_CLICKED(IDOK, &CMFCAssignmentDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_INITIMAGE, &CMFCAssignmentDlg::OnBnClickedBtnInitBackBuffer)
	ON_BN_CLICKED(IDC_BTN_RANDOM_MOVE_ONCE, &CMFCAssignmentDlg::OnBnClickedBtnRandomMoveOnce)
	ON_BN_CLICKED(IDC_BTN_RANDOM_MOVE_MULTIPLE, &CMFCAssignmentDlg::OnBnClickedBtnRandomMoveMultiple)
	ON_MESSAGE(WM_RANDOM_MOVE, &CMFCAssignmentDlg::OnRandomMove) // 랜덤 이동
	ON_MESSAGE(WM_RANDOM_MOVE_DONE, &CMFCAssignmentDlg::OnRandomMoveDone)
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
	m_mouseState = MouseState::Selecting;	// 처음엔 점을 찍는 모드로 시작

	m_labelHelper.SetStaticTextControls({ &m_staticPoint1, &m_staticPoint2, &m_staticPoint3 });

	// 랜덤 이동 위해 사용
	srand(static_cast<unsigned int>(time(0)));

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
	if (m_mouseState == MouseState::Selecting)
	{
		if (m_dots.Size() >= 3) return;

		CString radiusText, thicknessText;

		m_editRadius.GetWindowText(radiusText);
		m_radius = _ttoi(radiusText);  
		if (m_radius <= 0) m_radius = 10;

		m_editThickness.GetWindowText(thicknessText); 
		m_thickness = _ttoi(thicknessText);
		if (m_thickness <= 0) m_thickness = 5;

		m_dots.Add(point);
		m_labelHelper.UpdatePoints(m_dots.GetPoints());

		CPoint local(point.x - m_drawX, point.y - m_drawY);

		if (local.x >= 0 && local.y >= 0
			&& local.x < m_canvas.GetWidth()
			&& local.y < m_canvas.GetHeight())
		{
			m_canvas.DrawDot(local.x, local.y, m_radius); // '클릭 지점 원' 그리기
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

				CString centerStr, radiusStr;
				centerStr.Format(_T("정원 중심: (%d, %d)"), center.x, center.y);
				radiusStr.Format(_T("정원 반지름: %.2f"), radius);
				m_staticCenter.SetWindowText(centerStr);
				m_staticRadius.SetWindowText(radiusStr);
			}
			m_mouseState = MouseState::Dragging;
		}
		Invalidate(); 
	}
	else if (m_mouseState == MouseState::Dragging)
	{
		for (int i = 0; i < 3; ++i)
		{
			CPoint pt = m_dots.GetPoint(i);
			CRect rect(pt.x - 5, pt.y - 5, pt.x + 5, pt.y + 5);
			if (rect.PtInRect(point))
			{
				m_draggedIdx = i;	
				SetCapture();
				break;
			}
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

// OK 버튼 (닫기)
void CMFCAssignmentDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}

// 초기화 버튼
void CMFCAssignmentDlg::OnBnClickedBtnInitBackBuffer()
{
	InitCanvas();							// 캔버스 초기화
	m_dots.Clear();							// 클릭 지점 좌표 초기화
	m_labelHelper.ResetPointLabels();		// 클릭 지점 원 좌표 표시 라벨 초기화
	ResetCircleLabels();					// 정원 정보 표시 라벨 초기화

	m_mouseState = MouseState::Selecting;	// 선택 모드로 변경
	m_draggedIdx = -1;

	Invalidate();							// 화면 갱신
}

// 캔버스(백버퍼) 초기화
void CMFCAssignmentDlg::InitCanvas()
{
	m_canvas.SetSize(m_bufferWidth, m_bufferHeight);
	m_canvas.Init();
}

// 정원 라벨 초기화
void CMFCAssignmentDlg::ResetCircleLabels()
{
	m_staticCenter.SetWindowText(_T("정원 중심: -"));
	m_staticRadius.SetWindowText(_T("정원 반지름: -"));
}

// 드래그 처리
void CMFCAssignmentDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_mouseState == MouseState::Dragging && (nFlags & MK_LBUTTON))
	{

		if (m_draggedIdx != -1)
		{
			// 좌표 갱신
			m_dots.UpdatePoint(m_draggedIdx, point);
			m_dots.RedrawAll(m_canvas, m_drawX, m_drawY, m_radius, m_thickness);
			m_labelHelper.UpdatePoints(m_dots.GetPoints());
			Invalidate(); // 화면 갱신
			UpdateWindow();
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

// 드래그 종료
void CMFCAssignmentDlg::OnLButtonUp(UINT nFlags, CPoint point)
{

	if (m_mouseState == MouseState::Dragging)
	{
		m_draggedIdx = -1;
		ReleaseCapture(); // 마우스 캡처 해제
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}

// 랜덤 이동 버튼 (1회)
void CMFCAssignmentDlg::OnBnClickedBtnRandomMoveOnce()
{
	MoveDotsRandomly();
}

// 랜덤 이동 버튼 (10회 반복)
void CMFCAssignmentDlg::OnBnClickedBtnRandomMoveMultiple()
{
	if (m_isRandomMoveRunning)
		return; // 이미 실행 중이면 무시

	m_isRandomMoveRunning = true;

	// 이전에 이미 돌아가던 스레드가 있으면 join하고 시작
	if (m_randomMoveThread.joinable())
		m_randomMoveThread.join();

	m_randomMoveThread = std::thread([this]() {
		for (int i = 0; i < 10; ++i)
		{
			PostMessage(WM_RANDOM_MOVE);
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		PostMessage(WM_RANDOM_MOVE_DONE); 
		});
}

// '클릭 지점 원' 랜덤 이동 메시지 처리
LRESULT CMFCAssignmentDlg::OnRandomMove(WPARAM wParam, LPARAM lParam)
{
	MoveDotsRandomly(); 
	return 0;
}

// '클릭 지점 원' 이동 완료 메시지 처리
LRESULT CMFCAssignmentDlg::OnRandomMoveDone(WPARAM wParam, LPARAM lParam)
{
	if (m_randomMoveThread.joinable())
		m_randomMoveThread.join(); 

	m_isRandomMoveRunning = false; 
	return 0;
}

// '클릭 지점 원' 랜덤 이동 + 다시 그리기
void CMFCAssignmentDlg::MoveDotsRandomly()
{
	if (m_dots.Size() != 3) return;

	m_dots.MoveAllRandomly(m_canvas.GetWidth(), m_canvas.GetHeight(), m_drawX, m_drawY);

	m_dots.RedrawAll(m_canvas, m_drawX, m_drawY, m_radius, m_thickness);
	m_labelHelper.UpdatePoints(m_dots.GetPoints());
	Invalidate();
	UpdateWindow();
}