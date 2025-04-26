#pragma once
#include <vector>
#include <afxwin.h>  // CStatic
#include "Canvas.h"  // ���� ĵ������ ���� �ؽ�Ʈ ǥ��

/*-------------------------------------
  LabelHelper : ��ǥ �� ���� Ŭ����
--------------------------------------*/

class LabelHelper
{
public:
    void SetStaticTextControls(const std::vector<CStatic*>& staticTexts); // Static Text ��Ʈ�� ���
    void UpdatePoints(const std::vector<CPoint>& points);                 // Static Text�� ��ǥ ǥ��
    void ResetPointLabels();                                              // Static Text �ʱ�ȭ

    void DrawLabelsOnCanvas(Canvas& canvas, int offsetX, int offsetY);    // Canvas�� ��ǥ �ؽ�Ʈ ���� �׸���

private:
    std::vector<CStatic*> m_staticTexts; // �� 'Ŭ�� ���� ��'�� �����ϴ� Static Text ��Ʈ��
    std::vector<CPoint> m_points;        // �� 'Ŭ�� ���� ��'�� ��ǥ ����
};
