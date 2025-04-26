#pragma once
#include "Canvas.h"

class DotManager
{
public:
	DotManager();
	~DotManager();

	void Add(const CPoint& pt);				// �� �߰�
	void Clear();							// �� ��� �ʱ�ȭ
	size_t Size();							// ����� �� ���� ��ȯ
	CPoint GetPoint(int idx);				// idx��° �� ���� ��ȯ
	const std::vector<CPoint>& GetPoints(); // ��ü �� ��� ��ȯ
	bool UpdatePoint(int idx, const CPoint& pt);

	void RedrawAll(Canvas& canvas, int drawX, int drawY, int dotRadius, int thickness); // �巡�� �� �ٽ� �׸�

	void MoveAllRandomly(int canvasWidth, int canvasHeight, int drawX, int drawY);

private:
	std::vector<CPoint> m_points;			// Ŭ���� �� ���
};

