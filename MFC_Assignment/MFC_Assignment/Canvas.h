#pragma once

class Canvas
{
public:
	Canvas();
	~Canvas();

	bool Init();				// ĵ���� �ʱ�ȭ
	void SetSize(int width, int height);		// ĵ���� ũ�� ����

	void Clear();									// ĵ���� ���빰 ����
	void DrawDot(int cx, int cy, int radius);			// ĵ������ 'Ŭ�� ���� ��' �׸���
	void DrawCircle(CPoint center, double radius, int thickness = 1);
	void Present(CDC* pDC, int drawX, int drawY);	// ĵ������ �׷��� ���� ȭ�鿡 ������

	int GetWidth();		// ĵ���� ���� ���� ��ȯ
	int GetHeight();	// ĵ���� ���� ���� ��ȯ
	bool IsValid();		// ĵ���� ��ü ���� ���� Ȯ��

private:
	CImage m_canvas;
	int m_width = 0;
	int m_height = 0;
};

