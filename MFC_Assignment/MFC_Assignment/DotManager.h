#pragma once
#include "Canvas.h"

/*-----------------------------------
  DotManager : Ŭ���� �� ���� Ŭ����
------------------------------------*/

class DotManager
{
public:
	DotManager();
	~DotManager();

	void Add(const CPoint& pt);						// 'Ŭ�� ���� ��' �߰�
	void Clear();									// 'Ŭ�� ���� ��' ��� �ʱ�ȭ
	size_t Size();									// 'Ŭ�� ���� ��' ���� ��ȯ
	CPoint GetPoint(int idx);						// idx ��° 'Ŭ�� ���� ��' ���� ��ȯ
	const std::vector<CPoint>& GetPoints();			// ��ü 'Ŭ�� ���� ��' ��� ��ȯ
	bool UpdatePoint(int idx, const CPoint& pt);	// Ư�� �ε����� �� ��ġ ������Ʈ
	void RedrawAll(Canvas& canvas, int drawX, int drawY, int dotRadius, int thickness); // ���� �� �ٽ� �׸��� (�� Ŭ�� �� �巡�� �� ���)
	void MoveAllRandomly(int canvasWidth, int canvasHeight, int drawX, int drawY);		// ��� ���� �����ϰ� �̵�

private:
	std::vector<CPoint> m_points;					// Ŭ���� �� ���
};

