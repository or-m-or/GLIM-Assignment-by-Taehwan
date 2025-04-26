#pragma once
#include "Canvas.h"

/*-----------------------------------
  DotManager : 클릭된 점 관리 클래스
------------------------------------*/

class DotManager
{
public:
	DotManager();
	~DotManager();

	void Add(const CPoint& pt);						// '클릭 지점 원' 추가
	void Clear();									// '클릭 지점 원' 목록 초기화
	size_t Size();									// '클릭 지점 원' 개수 반환
	CPoint GetPoint(int idx);						// idx 번째 '클릭 지점 원' 정보 반환
	const std::vector<CPoint>& GetPoints();			// 전체 '클릭 지점 원' 목록 반환
	bool UpdatePoint(int idx, const CPoint& pt);	// 특정 인덱스의 점 위치 업데이트
	void RedrawAll(Canvas& canvas, int drawX, int drawY, int dotRadius, int thickness); // 점과 원 다시 그리기 (점 클릭 후 드래그 시 사용)
	void MoveAllRandomly(int canvasWidth, int canvasHeight, int drawX, int drawY);		// 모든 점을 랜덤하게 이동

private:
	std::vector<CPoint> m_points;					// 클릭된 점 목록
};

