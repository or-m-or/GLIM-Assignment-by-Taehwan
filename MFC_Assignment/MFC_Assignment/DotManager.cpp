#include "pch.h"
#include "DotManager.h"

DotManager::DotManager()
{
}

DotManager::~DotManager()
{
}

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
