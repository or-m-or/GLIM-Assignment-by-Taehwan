#include "pch.h"
#include "DotManager.h"

/*-----------------------------------
  DotManager : 클릭된 점 관리 클래스
------------------------------------*/

DotManager::DotManager() { }
DotManager::~DotManager() { }

void DotManager::Add(const CPoint& pt)
{
	m_points.push_back(pt);
}

void DotManager::Clear()
{
	m_points.clear();
}

size_t DotManager::Size()
{
	return m_points.size();
}

CPoint DotManager::GetPoint(int idx)
{
	if (0 <= idx && idx <= static_cast<int>(m_points.size()))
		return m_points[idx];
	return CPoint(-1, -1);
}

const std::vector<CPoint>& DotManager::GetPoints()
{
	return m_points;
}

bool DotManager::UpdatePoint(int idx, const CPoint& pt)
{
	if (0 <= idx && idx < static_cast<int>(m_points.size()))
	{
		m_points[idx] = pt;
		return true;
	}
	return false;
}

void DotManager::RedrawAll(Canvas& canvas, int drawX, int drawY, int dotRadius, int thickness)
{
	canvas.Clear();

	for (const CPoint& pt : m_points)
	{
		CPoint local(pt.x - drawX, pt.y - drawY);
		canvas.DrawDot(local.x, local.y, dotRadius);
	}

	if (m_points.size() == 3)
	{
		CPoint center;
		double radius;
		CPoint p1 = m_points[0] - CPoint(drawX, drawY);
		CPoint p2 = m_points[1] - CPoint(drawX, drawY);
		CPoint p3 = m_points[2] - CPoint(drawX, drawY);

		if (Utils::GetCircleFromThreePoints(p1, p2, p3, center, radius))
		{
			canvas.DrawCircle(center, radius, thickness);
		}
	}
}

void DotManager::MoveAllRandomly(int canvasWidth, int canvasHeight, int drawX, int drawY)
{
	if (m_points.empty()) return;

	std::random_device rd;
	std::mt19937 gen(rd());

	int margin = 20;
	std::uniform_int_distribution<> distX(drawX + margin, drawX + canvasWidth - margin - 1);
	std::uniform_int_distribution<> distY(drawY + margin, drawY + canvasHeight - margin - 1);

	for (CPoint& pt : m_points)
	{
		pt.x = distX(gen);
		pt.y = distY(gen);
	}
}
