#include "pch.h"
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

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CAboutDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}


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

	InitBackBuffer(); // 백버퍼 초기화
	m_editRadius.SetWindowText(_T("10"));

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
		// CDialogEx::OnPaint();
		CPaintDC dc(this);
		if (!m_backBuffer.IsNull())
			m_backBuffer.Draw(dc, m_drawX, m_drawY); // 백버퍼 출력
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
	CString str;
	m_editRadius.GetWindowText(str);
	m_radius = _ttoi(str);  // 문자열 → 정수 변환
	if (m_radius <= 0) m_radius = 10;

	// 클릭한 좌표를 최대 3개까지 저장
	if (m_clickPoints.size() < 3)
		m_clickPoints.push_back(point);

	// Static Text에 좌표 표시
	UpdatePointLabels();

	// 클릭 지점에서 백버퍼 내 좌표로 변환
	int localX = point.x - m_drawX;
	int localY = point.y - m_drawY;

	// 백버퍼 영역 내에서만 그림
	if (localX >= 0 && localY >= 0 
		&& localX < m_backBuffer.GetWidth() 
		&& localY < m_backBuffer.GetHeight())
	{
		DrawDot(localX, localY, m_radius); // 점 그리기
		Invalidate(); // 화면 갱신
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CMFCAssignmentDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}


void CMFCAssignmentDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}

// 초기화 버튼
void CMFCAssignmentDlg::OnBnClickedBtnInitBackBuffer()
{
	InitBackBuffer();		// 백버퍼 초기화
	m_clickPoints.clear();  // 클릭 지점 좌표 초기화
	ResetPointLabels();     // Static Text 초기화 추가
	Invalidate();			// 화면 갱신
}

// 클릭 지점 원 그리는 함수
// cx, cy: 클릭 위치 x, y 좌표
void CMFCAssignmentDlg::DrawDot(int cx, int cy, int radius)
{
	// 배경 생성 X
	if (m_backBuffer.IsNull()) return;

	// 배경의 가로, 세로 크기 및 한 줄 바이트 수(pitch) 가져옴
	int width = m_backBuffer.GetWidth();
	int height = m_backBuffer.GetHeight();
	int pitch = m_backBuffer.GetPitch();

	// 배경의 실제 픽셀 데이터 가져옴
	unsigned char* buffer = (unsigned char*)m_backBuffer.GetBits();
	 
	// 클릭 지점 원 그릴 사각형 범위 계산 (cx-radius, cy-radius) ~ (cx+radius, cy+radius)
	for (int y = cy - radius; y <= cy + radius; ++y)
	{
		for (int x = cx - radius; x <= cx + radius; ++x)
		{
			// 배경 범위 벗어나는 경우 무시
			if (x < 0 || y < 0 || x >= width || y >= height) continue;

			// 원의 방정식
			int dx = x - cx;
			int dy = y - cy;
			if (dx * dx + dy * dy <= radius * radius)
				buffer[y * pitch + x] = 0; // 원 안쪽 픽셀 색상 설정, 8bpp라서 0은 검정색
		}
	}
}

// CImage 초기화
void CMFCAssignmentDlg::InitBackBuffer()
{
	// 백버퍼 이미 존재할 경우
	if (!m_backBuffer.IsNull())
		m_backBuffer.Destroy();

	// 백버퍼 새로 생성
	m_backBuffer.Create(m_bufferWidth, -m_bufferHeight, 8); // top-down 640x480 8bpp

	// 팔레트 설정
	RGBQUAD palette[256];
	for (int i = 0; i < 256; ++i)
		palette[i].rgbRed = palette[i].rgbGreen = palette[i].rgbBlue = i;
	m_backBuffer.SetColorTable(0, 256, palette);

	memset(m_backBuffer.GetBits(), 255, m_backBuffer.GetWidth() * m_backBuffer.GetHeight()); // 흰 배경
}

void CMFCAssignmentDlg::UpdatePointLabels()
{
	if (m_clickPoints.size() > 0)
	{
		CString txt;
		txt.Format(_T("클릭 지점 1: (%d, %d)"), m_clickPoints[0].x, m_clickPoints[0].y);
		m_staticPoint1.SetWindowText(txt);
	}
	if (m_clickPoints.size() > 1)
	{
		CString txt;
		txt.Format(_T("클릭 지점 2: (%d, %d)"), m_clickPoints[1].x, m_clickPoints[1].y);
		m_staticPoint2.SetWindowText(txt);
	}
	if (m_clickPoints.size() > 2)
	{
		CString txt;
		txt.Format(_T("클릭 지점 3: (%d, %d)"), m_clickPoints[2].x, m_clickPoints[2].y);
		m_staticPoint3.SetWindowText(txt);
	}
}

void CMFCAssignmentDlg::ResetPointLabels()
{
	m_staticPoint1.SetWindowText(_T("클릭 지점 1: -"));
	m_staticPoint2.SetWindowText(_T("클릭 지점 2: -"));
	m_staticPoint3.SetWindowText(_T("클릭 지점 3: -"));
}
