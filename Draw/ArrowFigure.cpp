#include "pch.h"
#include "ArrowFigure.h"

ArrowFigure::ArrowFigure()
{
}

ArrowFigure::ArrowFigure(const Color& color, const CPoint& ptMouse)
{

}

ArrowFigure::ArrowFigure(const ArrowFigure& arrow)
    :LineFigure(arrow),
    Figure(arrow)
{
    m_ptLeft = arrow.m_ptLeft;
    m_ptRight = arrow.m_ptRight;
}

Figure* ArrowFigure::Copy() const
{
    return nullptr;
}

void ArrowFigure::Serialize(CArchive& archive)
{
}

BOOL ArrowFigure::DoubleClick(const CPoint& ptMouse)
{
    if (LineFigure::Click(ptMouse)) {
        CPoint ptTemp = m_ptFirst;
        m_ptFirst = m_ptLast;
        m_ptLast = ptTemp;

        SetArrowPoints();
        return TRUE;
    }
    return FALSE;
}

void ArrowFigure::MoveOrModify(const CSize& szDistance)
{
}

void ArrowFigure::Move(const CSize& szDistance)
{
}

void ArrowFigure::Draw(CDC* pDC) const
{
    LineFigure::Draw(pDC);
    CPen pen(PS_SOLID, 0, (COLORREF)Figure::GetColor());
    CPen* pOldPen = pDC->SelectObject(&pen);
    pDC->MoveTo(m_ptLast);
    pDC->LineTo(m_ptLeft);
    pDC->MoveTo(m_ptLast);
    pDC->LineTo(m_ptRight);
    pDC->SelectObject(pOldPen);

}

CRect ArrowFigure::GetArea() const
{
    CRect rcLine = LineFigure::GetArea();
    CRect rcLeftArrow(m_ptLast, m_ptLeft);
    rcLeftArrow.NormalizeRect();
    rcLine.UnionRect(rcLine, rcLeftArrow);
    CRect rcRightArrow(m_ptLast, m_ptRight);
    rcRightArrow.NormalizeRect();
    rcLine.UnionRect(rcLine, rcRightArrow);
    return rcLine;
}

void ArrowFigure::SetArrowPoints()
{
    int iHeight = m_ptLast.y - m_ptFirst.y;
    int iWidth = m_ptLast.x - m_ptFirst.x;
    const double PI = 3.14159265;
    double dAlpha = atan2((double)iHeight, (double)iWidth);
    double dBeta = dAlpha + PI;
    double dLeftAngle = dBeta - PI / 4;
    double dRightAngle = dBeta + PI / 4;
    m_ptFirst.x = m_ptLast.x + (int)(ARROW_LENGTH * cos(dLeftAngle));
    m_ptLeft.y = m_ptLast.y + (int)(ARROW_LENGTH * sin(dLeftAngle));
    m_ptLast.x = m_ptLast.x + (int)(ARROW_LENGTH * cos(dRightAngle));
    m_ptLast.y = m_ptLast.y + (int)(ARROW_LENGTH * sin(dRightAngle));
}
