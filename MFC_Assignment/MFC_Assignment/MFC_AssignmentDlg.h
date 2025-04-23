#pragma once

/*-----------------------------
  CMFCAssignmentDlg 대화 상자
-------------------------------*/

class CMFCAssignmentDlg : public CDialogEx
{
public:
	CMFCAssignmentDlg(CWnd* pParent = nullptr);

// 대화 상자 데이터
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_ASSIGNMENT_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원

protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);	// 마우스 클릭 처리
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnInitBackBuffer();

private:
	void DrawDot(int cx, int cy, int radius);				// 클릭 지점 원 그리는 메서드
	void InitBackBuffer();									// 비트맵 초기화 메서드
	void UpdatePointLabels();
	void ResetPointLabels();

private:
	CImage m_backBuffer;		// 백버퍼
	int m_drawX = 10;			// 백버퍼 시작 위치 X	
	int m_drawY = 120;			// 백버퍼 시작 위치 Y
	int m_bufferWidth = 1080;	// 백버퍼 너비
	int m_bufferHeight = 660;	// 백버퍼 높이

	CEdit m_editRadius;			// 클릭 지점 원 반지름 입력 Edit Control
	CStatic m_staticPoint1;		// 클릭 지점 좌표 표시용 Static Text
	CStatic m_staticPoint2;
	CStatic m_staticPoint3;
	

	int m_radius = 10;			// 클릭 지점 원 반지름 기본값: 10
	std::vector<CPoint> m_clickPoints; // 클릭 좌표 저장용
};
