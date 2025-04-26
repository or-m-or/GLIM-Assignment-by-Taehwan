#include "pch.h"
#include "Canvas.h"
#include <cmath>

Canvas::Canvas()
{
}

Canvas::~Canvas()
{
}

bool Canvas::Init()
{
	// ĵ���� ������ ���� ���Ѱ��
	if (m_width == 0 || m_height == 0)
		return false; 

	// ĵ���� �̹� ������ ���
	if (!m_canvas.IsNull())
		m_canvas.Destroy();

	// ����� ���� ����
	m_canvas.Create(m_width, -m_height, 8); // top-down 640x480 8bpp

	// �ȷ�Ʈ ����
	RGBQUAD palette[256];
	for (int i = 0; i < 256; ++i)
		palette[i].rgbRed = palette[i].rgbGreen = palette[i].rgbBlue = i;
	m_canvas.SetColorTable(0, 256, palette);

	Clear();
	return true;
}

void Canvas::SetSize(int width, int height)
{
	m_width = width;
	m_height = height;
}

void Canvas::Clear()
{
	if (IsValid())
	{
		// �޸� �ʱ�ȭ �Լ�, ��Ʈ�� �ȼ� ������ ���� �ʱ�ȭ
		// �޸��� ���� ���ϴ� ũ�� ��ŭ Ư�� ������ �ʱ�ȭ�� �� �ִ� �Լ�
		// void* memset(void* ptr/*�޸� ���� �ּ�*/, int value/*�ʱ�ȭ�� ��*/, size_t num/*������ ����Ʈ ��*/);
		memset(m_canvas.GetBits(), 255, m_canvas.GetWidth() * m_canvas.GetHeight());
	}
}

// Ŭ�� ���� �� ����
void Canvas::DrawDot(int cx, int cy, int radius)
{
	// ��� ���� X
	if (m_canvas.IsNull()) return;

	// ����� ����, ���� ũ�� �� �� �� ����Ʈ ��(pitch) ������
	int width = m_canvas.GetWidth();
	int height = m_canvas.GetHeight();
	int pitch = m_canvas.GetPitch();

	// ����� ���� �ȼ� ������ ������
	unsigned char* buffer = (unsigned char*)m_canvas.GetBits();

	// Ŭ�� ���� �� �׸� �簢�� ���� ��� (cx-radius, cy-radius) ~ (cx+radius, cy+radius)
	for (int y = cy - radius; y <= cy + radius; ++y)
	{
		for (int x = cx - radius; x <= cx + radius; ++x)
		{
			// ��� ���� ����� ��� ����
			if (x < 0 || y < 0 || x >= width || y >= height) continue;

			// ���� ������
			int dx = x - cx;
			int dy = y - cy;
			if (dx * dx + dy * dy <= radius * radius)
				buffer[y * pitch + x] = 0; // �� ���� �ȼ� ���� ����, 8bpp�� 0�� ������
		}
	}
}

void Canvas::DrawCircle(CPoint center, double radius, int thickness)
{
	if (!IsValid()) return;

	const int width = m_canvas.GetWidth();		// ĵ���� ���� ����
	const int height = m_canvas.GetHeight();	// ĵ���� ���� ����
	const int pitch = m_canvas.GetPitch();		// �� �ٴ� ����Ʈ ��
	unsigned char* buffer = (unsigned char*)m_canvas.GetBits();	// �ȼ� ���� ������ (8bpp grayscale)

	// ȭ�� ��ü ��ȸ
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			// ���� �ȼ�(x, y)�� �� �߽�(center.x, center.y) ������ �Ÿ�
			int dx = x - center.x;
			int dy = y - center.y;
			double dist = sqrt(dx * dx + dy * dy); // ��Ŭ����� �Ÿ�

			// ���� �ȼ��� �� ������ +- �ܰ��� �β� ���� ���� �̳����, 
			if (dist >= radius - thickness / 2.0 && dist <= radius + thickness / 2.0)
			{
				buffer[y * pitch + x] = 0; // �ܰ����� �׸��� (������, 0)
			}
		}
	}
}

void Canvas::Present(CDC* pDC, int drawX, int drawY)
{
	if (IsValid())
		// ����� ��ũ���� �׷��� Device Context
		// GetSafeHdc: MFC ��ü���� ������ HDC(Handle & Device Context)�� �����ϰ� ������
		// Draw(): pDC�� BitBlt(��Ʈ�� ����) ������� �׸�
		// drawX, drawY: ������ ���� ��ǥ
		m_canvas.Draw(pDC->GetSafeHdc(), drawX, drawY);
}

int Canvas::GetWidth()
{
	return m_canvas.GetWidth();
}

int Canvas::GetHeight()
{
	return m_canvas.GetHeight();
}

bool Canvas::IsValid()
{
	return !m_canvas.IsNull();
}
