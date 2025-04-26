#include "pch.h"
#include "LabelHelper.h"
#include <string>

void LabelHelper::SetStaticTextControls(const std::vector<CStatic*>& staticTexts)
{
    m_staticTexts = staticTexts;
}

void LabelHelper::UpdatePoints(const std::vector<CPoint>& points)
{
    m_points = points;

    for (size_t i = 0; i < m_staticTexts.size(); ++i)
    {
        if (i < points.size() && m_staticTexts[i] != nullptr)
        {
            CString text;
            text.Format(_T("클릭 지점 %d: (%d, %d)"), static_cast<int>(i + 1), points[i].x, points[i].y);
            m_staticTexts[i]->SetWindowText(text);
        }
        else if (m_staticTexts[i] != nullptr)
        {
            CString text;
            text.Format(_T("클릭 지점 %d: -"), static_cast<int>(i + 1));
            m_staticTexts[i]->SetWindowText(text);
        }
    }
}

void LabelHelper::ResetPointLabels()
{
    for (size_t i = 0; i < m_staticTexts.size(); ++i)
    {
        if (m_staticTexts[i] != nullptr)
        {
            CString text;
            text.Format(_T("클릭 지점 %d: -"), static_cast<int>(i + 1));
            m_staticTexts[i]->SetWindowText(text);
        }
    }
}

void LabelHelper::DrawLabelsOnCanvas(Canvas& canvas, int offsetX, int offsetY)
{
    // Canvas 위에 좌표를 직접 그릴 때 구현
}
