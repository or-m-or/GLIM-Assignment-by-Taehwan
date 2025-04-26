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
	// 캔버스 사이즈 설정 안한경우
	if (m_width == 0 || m_height == 0)
		return false; 

	// 캔버스 이미 존재할 경우
	if (!m_canvas.IsNull())
		m_canvas.Destroy();

	// 백버퍼 새로 생성
	m_canvas.Create(m_width, -m_height, 8); // top-down 640x480 8bpp

	// 팔레트 설정
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
		// 메모리 초기화 함수, 비트맵 픽셀 데이터 직접 초기화
		// 메모리의 값을 원하는 크기 만큼 특정 값으로 초기화할 수 있는 함수
		// void* memset(void* ptr/*메모리 시작 주소*/, int value/*초기화할 값*/, size_t num/*설정할 바이트 수*/);
		memset(m_canvas.GetBits(), 255, m_canvas.GetWidth() * m_canvas.GetHeight());
	}
}

// 클릭 지점 원 생성
void Canvas::DrawDot(int cx, int cy, int radius)
{
	// 배경 생성 X
	if (m_canvas.IsNull()) return;

	// 배경의 가로, 세로 크기 및 한 줄 바이트 수(pitch) 가져옴
	int width = m_canvas.GetWidth();
	int height = m_canvas.GetHeight();
	int pitch = m_canvas.GetPitch();

	// 배경의 실제 픽셀 데이터 가져옴
	unsigned char* buffer = (unsigned char*)m_canvas.GetBits();

	// 클릭 지점 원 그릴 사각형 범위 계산 (cx-radius, cy-radius) ~ (cx+radius, cy+radius)
	for (int y = cy - radius; y <= cy + radius; ++y)
	{
		for (int x = cx - radius; x <= cx + radius; ++x)
		{
			// 배경 범위 벗어나는 경우 무시
			if (x < 0 || y < 0 || x >= width || y >= height) continue;

			// 원의 방정식
			int dx = x - cx;
			int dy = y - cy;
			if (dx * dx + dy * dy <= radius * radius)
				buffer[y * pitch + x] = 0; // 원 안쪽 픽셀 색상 설정, 8bpp라서 0은 검정색
		}
	}
}

void Canvas::DrawCircle(CPoint center, double radius, int thickness)
{
	if (!IsValid()) return;

	const int width = m_canvas.GetWidth();		// 캔버스 가로 길이
	const int height = m_canvas.GetHeight();	// 캔버스 세로 길이
	const int pitch = m_canvas.GetPitch();		// 한 줄당 바이트 수
	unsigned char* buffer = (unsigned char*)m_canvas.GetBits();	// 픽셀 버퍼 포인터 (8bpp grayscale)

	// 화면 전체 순회
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			// 현재 픽셀(x, y)와 원 중심(center.x, center.y) 사이의 거리
			int dx = x - center.x;
			int dy = y - center.y;
			double dist = sqrt(dx * dx + dy * dy); // 유클리디안 거리

			// 현재 픽셀이 원 반지름 +- 외각선 두께 절반 범위 이내라면, 
			if (dist >= radius - thickness / 2.0 && dist <= radius + thickness / 2.0)
			{
				buffer[y * pitch + x] = 0; // 외곽선만 그리기 (검정색, 0)
			}
		}
	}
}

void Canvas::Present(CDC* pDC, int drawX, int drawY)
{
	if (IsValid())
		// 백배퍼 스크린에 그려진 Device Context
		// GetSafeHdc: MFC 객체에서 윈도우 HDC(Handle & Device Context)를 안전하게 가져옴
		// Draw(): pDC에 BitBlt(비트맵 복사) 방식으로 그림
		// drawX, drawY: 렌더링 시작 좌표
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
