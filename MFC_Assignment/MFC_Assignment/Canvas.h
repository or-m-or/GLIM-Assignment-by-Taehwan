#pragma once

class Canvas
{
public:
	Canvas();
	~Canvas();

	bool Init();				// 캔버스 초기화
	void SetSize(int width, int height);		// 캔버스 크기 설정

	void Clear();									// 캔버스 내용물 삭제
	void DrawDot(int cx, int cy, int radius);			// 캔버스에 '클릭 지점 원' 그리기
	void DrawCircle(CPoint center, double radius, int thickness = 1);
	void Present(CDC* pDC, int drawX, int drawY);	// 캔버스에 그려진 내용 화면에 렌더링

	int GetWidth();		// 캔버스 가로 길이 반환
	int GetHeight();	// 캔버스 세로 길이 반환
	bool IsValid();		// 캔버스 객체 생성 유무 확인

private:
	CImage m_canvas;
	int m_width = 0;
	int m_height = 0;
};

