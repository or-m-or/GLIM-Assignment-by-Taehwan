#pragma once
#include "Canvas.h"

class DotManager
{
public:
	DotManager();
	~DotManager();

	void Add(const CPoint& pt);				// 점 추가
	void Clear();							// 점 목록 초기화
	size_t Size();							// 저장된 점 개수 반환
	CPoint GetPoint(int idx);				// idx번째 점 정보 반환
	const std::vector<CPoint>& GetPoints(); // 전체 점 목록 반환
	bool UpdatePoint(int idx, const CPoint& pt);

	void RedrawAll(Canvas& canvas, int drawX, int drawY, int dotRadius, int thickness); // 드래그 시 다시 그림

	void MoveAllRandomly(int canvasWidth, int canvasHeight, int drawX, int drawY);

private:
	std::vector<CPoint> m_points;			// 클릭된 점 목록
};

