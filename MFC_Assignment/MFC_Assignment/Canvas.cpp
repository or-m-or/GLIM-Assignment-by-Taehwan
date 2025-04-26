#include "pch.h"
#include "Canvas.h"

/*-----------------------------
  Canvas : 백버퍼 관리 클래스
-------------------------------*/

Canvas::Canvas() { }
Canvas::~Canvas() { }

bool Canvas::Init()
{
	if (m_width == 0 || m_height == 0)
		return false; 

	if (!m_canvas.IsNull())
		m_canvas.Destroy();

	m_canvas.Create(m_width, -m_height, 8); // top-down 640x480 8bpp

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
		memset(m_canvas.GetBits(), 255, m_canvas.GetWidth() * m_canvas.GetHeight());
	}
}

void Canvas::DrawDot(int cx, int cy, int radius)
{
	if (m_canvas.IsNull()) return;

	int width = m_canvas.GetWidth();
	int height = m_canvas.GetHeight();
	int pitch = m_canvas.GetPitch();

	unsigned char* buffer = (unsigned char*)m_canvas.GetBits();

	for (int y = cy - radius; y <= cy + radius; ++y)
	{
		for (int x = cx - radius; x <= cx + radius; ++x)
		{
			if (x < 0 || y < 0 || x >= width || y >= height) continue;

			// 원의 방정식
			int dx = x - cx;
			int dy = y - cy;
			if (dx * dx + dy * dy <= radius * radius)
				buffer[y * pitch + x] = 0; 
		}
	}
}

void Canvas::DrawCircle(CPoint center, double radius, int thickness)
{
	if (!IsValid()) return;

	const int width = m_canvas.GetWidth();		
	const int height = m_canvas.GetHeight();	
	const int pitch = m_canvas.GetPitch();		
	unsigned char* buffer = (unsigned char*)m_canvas.GetBits();	// 8bpp grayscale

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			int dx = x - center.x;
			int dy = y - center.y;
			double dist = sqrt(dx * dx + dy * dy); // 유클리디안 거리

			if (dist >= radius - thickness / 2.0 && dist <= radius + thickness / 2.0)
			{
				buffer[y * pitch + x] = 0;
			}
		}
	}
}

void Canvas::Present(CDC* pDC, int drawX, int drawY)
{
	if (IsValid())
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
