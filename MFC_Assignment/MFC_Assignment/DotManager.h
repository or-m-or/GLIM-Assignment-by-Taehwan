#pragma once

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

private:
	std::vector<CPoint> m_points;			// Ŭ���� �� ���
};

