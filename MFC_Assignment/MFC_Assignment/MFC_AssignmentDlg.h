#pragma once
#include "Canvas.h"
#include "DotManager.h"

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
	void InitCanvas();
	void UpdatePointLabels();
	void ResetPointLabels();
	void ResetCircleLabels();
	void OnMouseMove(UINT nFlags, CPoint point); // 드래그 처리
	void OnLButtonUp(UINT nFlags, CPoint point); // 드래그 종료 afx_msg...?

private:
	Canvas m_canvas;			// 선택 지점 원, 세점을 잇는 원 등을 그릴 캔버스
	DotManager m_dots;			// 클릭 지점 원 관리 객체

	int m_drawX = 10;			// 캔버스 시작 위치 X	
	int m_drawY = 120;			// 캔버스 시작 위치 Y
	int m_bufferWidth = 1080;	// 캔버스 가로 길이
	int m_bufferHeight = 660;	// 캔버스 세로 길이

	CEdit m_editRadius;			// 클릭 지점 원 반지름 입력 Edit Control
	CStatic m_staticPoint1;		// 클릭 지점 좌표 표시용 Static Text
	CStatic m_staticPoint2;
	CStatic m_staticPoint3;
	int m_radius = 10;			// 클릭 지점 원 반지름 기본값: 10

	CEdit m_editThickness;		// 정원 외각선 두께
	int m_thickness = 5;		// 외각선 기본값: 5
	CStatic m_staticCenter;		// 정원 중심 좌표
	CStatic m_staticRadius;		// 정원 반지름

	bool m_dragging = false;	// 드래그 여부
	int m_draggedIdx = -1;		// 드래그 중인 점 인덱스(m_dots 중에서)
};
