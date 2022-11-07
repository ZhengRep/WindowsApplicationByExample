#include "pch.h"
#include "EllipseFigure.h"

EllipseFigure::EllipseFigure()
{
}

EllipseFigure::EllipseFigure(const Color& color, const CPoint& ptTopLeft, BOOL bFilled)
{
}

EllipseFigure::EllipseFigure(const EllipseFigure& ellipse)
{
}

Figure* EllipseFigure::Copy() const
{
    return nullptr;
}

HCURSOR EllipseFigure::GetCursor() const
{
    return HCURSOR();
}

BOOL EllipseFigure::Click(const CPoint& ptMouse)
{
    int xCenter = (m_ptTopLeft.x + m_ptBottomRight.x) / 2;
    int yCenter = (m_ptTopLeft.y + m_ptBottomRight.y) / 2;
	DWORD dHalfSquareSide = SQUARE_SIDE / 2;
	CRect rcLeft(m_ptTopLeft.x - dHalfSquareSide, yCenter - dHalfSquareSide, m_ptTopLeft.x + dHalfSquareSide, yCenter+ dHalfSquareSide);
	if (rcLeft.PtInRect(ptMouse)) {
		m_eDragMode = MODIFY_LEFT;
		return TRUE;
	}
	CRect rcTop(xCenter - dHalfSquareSide, m_ptTopLeft.y - dHalfSquareSide, xCenter + dHalfSquareSide, m_ptTopLeft.y + dHalfSquareSide);
	if (rcTop.PtInRect(ptMouse)) {
		m_eDragMode = MODIFY_TOP;
		return TRUE;
	}
	CRect rcRight(m_ptBottomRight.x - dHalfSquareSide, yCenter - dHalfSquareSide, m_ptBottomRight + dHalfSquareSide, yCenter + dHalfSquareSide);
	if (rcRight.PtInRect(ptMouse)) {
		m_eDragMode = MODIFY_RIGHT;
		return TRUE;
	}
	CRect rcBottom(xCenter - dHalfSquareSide, m_ptBottomRight.y - dHalfSquareSide, xCenter + dHalfSquareSide, m_ptBottomRight.y + dHalfSquareSide);
	if (rcBottom.PtInRect(ptMouse)) {
		m_eDragMode = MODIFY_BOTTOM;
		return TRUE;
	}

	CRgn rgArea;
	rgArea.CreateEllipticRgn(m_ptTopLeft.x, m_ptTopLeft.y, m_ptBottomRight.x, m_ptBottomRight.y);
	if (IsFilled()) {
		m_eDragMode = MOVE_ELLIPSE;
		return rgArea.PtInRegion(ptMouse);
	}
	else {
		int xMin = min(m_ptTopLeft.x, m_ptBottomRight.x);
		int xMax = max(m_ptTopLeft.x, m_ptBottomRight.x);
		int yMin = min(m_ptTopLeft.y, m_ptBottomRight.y);
		int yMax = max(m_ptTopLeft.y, m_ptBottomRight.y);
		CRgn rgSmallArea, rgLargeArea;
		rgSmallArea.CreateEllipticRgn(xMin + dHalfSquareSide, yMin + dHalfSquareSide, xMax - dHalfSquareSide, yMax - dHalfSquareSide);
		rgLargeArea.CreateEllipticRgn(xMin - dHalfSquareSide, yMin - dHalfSquareSide, xMax + dHalfSquareSide, yMax + dHalfSquareSide);
		m_eDragMode = MOVE_ELLIPSE;
		return !rgSmallArea.PtInRegion(ptMouse) & rgLargeArea.PtInRegion(ptMouse);
	}
}

void EllipseFigure::MoveOrModify(const CSize& szDistance)
{
}

void EllipseFigure::Draw(CDC* pDC) const
{
}
