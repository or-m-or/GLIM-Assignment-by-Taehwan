#include "pch.h"
#include "Utils.h"

/*-------------------------
  Utils : ��ƿ��Ƽ Ŭ����
--------------------------*/

bool Utils::GetCircleFromThreePoints(const CPoint& p1, const CPoint& p2, const CPoint& p3, CPoint& center, double& radius)
{
    int x1 = p1.x, y1 = p1.y;
    int x2 = p2.x, y2 = p2.y;
    int x3 = p3.x, y3 = p3.y;

    // �� ���� ���: (p2 - p1), (p3 - p1)
    int a1 = x2 - x1;
    int b1 = y2 - y1;
    int a2 = x3 - x1;
    int b2 = y3 - y1;

    // ��Ľ� ��� (���� ������ ����� ����) �� 0�̸� �� ���� ������
    int d = 2 * (a1 * b2 - a2 * b1);
    if (d == 0) return false;  // �� ���� �������� ���� �� �� ����

    // c1, c2 ���
    int c1 = a1 * (x1 + x2) + b1 * (y1 + y2);
    int c2 = a2 * (x1 + x3) + b2 * (y1 + y3);

    // �߽� ��ǥ (cx, cy) ���
    int cx = (b2 * c1 - b1 * c2) / d;
    int cy = (a1 * c2 - a2 * c1) / d;

    // �߽� ��ǥ
    center = CPoint(cx, cy);

    // ������ = �߽ɿ��� p1������ �Ÿ�
    radius = sqrt((cx - x1) * (cx - x1) + (cy - y1) * (cy - y1));

    return true;
}
