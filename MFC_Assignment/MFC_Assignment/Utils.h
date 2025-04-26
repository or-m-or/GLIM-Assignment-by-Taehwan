#pragma once
#include <cmath>

/*-------------------------
  Utils : 유틸리티 클래스
--------------------------*/

class Utils
{
public:
	// 세 점을 지나는 원의 중심, 반지름 계산
	static bool GetCircleFromThreePoints(const CPoint& p1, const CPoint& p2, const CPoint& p3, CPoint& center, double& radius);
};
