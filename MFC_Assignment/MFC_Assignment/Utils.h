#pragma once
#include <cmath>

class Utils
{
public:
	// �� ���� ������ ���� �߽�, ������ ���
	static bool GetCircleFromThreePoints(const CPoint& p1, const CPoint& p2, const CPoint& p3, CPoint& center, double& radius);
};
