#pragma once
#include <vector>
#include <afxwin.h>  // CStatic
#include "Canvas.h"  // 추후 캔버스에 직접 텍스트 표시

/*-------------------------------------
  LabelHelper : 좌표 라벨 관리 클래스
--------------------------------------*/

class LabelHelper
{
public:
    void SetStaticTextControls(const std::vector<CStatic*>& staticTexts); // Static Text 컨트롤 등록
    void UpdatePoints(const std::vector<CPoint>& points);                 // Static Text에 좌표 표시
    void ResetPointLabels();                                              // Static Text 초기화

    void DrawLabelsOnCanvas(Canvas& canvas, int offsetX, int offsetY);    // Canvas에 좌표 텍스트 직접 그리기

private:
    std::vector<CStatic*> m_staticTexts; // 각 '클릭 지점 원'에 대응하는 Static Text 컨트롤
    std::vector<CPoint> m_points;        // 각 '클릭 지점 원'의 좌표 저장
};
