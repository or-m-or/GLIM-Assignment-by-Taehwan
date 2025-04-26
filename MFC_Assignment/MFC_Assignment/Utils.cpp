#include "pch.h"
#include "Utils.h"

/*-------------------------
  Utils : 유틸리티 클래스
--------------------------*/

bool Utils::GetCircleFromThreePoints(const CPoint& p1, const CPoint& p2, const CPoint& p3, CPoint& center, double& radius)
{
    int x1 = p1.x, y1 = p1.y;
    int x2 = p2.x, y2 = p2.y;
    int x3 = p3.x, y3 = p3.y;

    // 두 벡터 계산: (p2 - p1), (p3 - p1)
    int a1 = x2 - x1;
    int b1 = y2 - y1;
    int a2 = x3 - x1;
    int b2 = y3 - y1;

    // 행렬식 계산 (벡터 외적과 비슷한 역할) → 0이면 세 점이 일직선
    int d = 2 * (a1 * b2 - a2 * b1);
    if (d == 0) return false;  // 세 점이 일직선에 있음 → 원 없음

    // c1, c2 계산
    int c1 = a1 * (x1 + x2) + b1 * (y1 + y2);
    int c2 = a2 * (x1 + x3) + b2 * (y1 + y3);

    // 중심 좌표 (cx, cy) 계산
    int cx = (b2 * c1 - b1 * c2) / d;
    int cy = (a1 * c2 - a2 * c1) / d;

    // 중심 좌표
    center = CPoint(cx, cy);

    // 반지름 = 중심에서 p1까지의 거리
    radius = sqrt((cx - x1) * (cx - x1) + (cy - y1) * (cy - y1));

    return true;
}
