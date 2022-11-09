#include "pch.h"
#include "RectangleFigure.h"

RectangleFigure::RectangleFigure()
{
}

RectangleFigure::RectangleFigure(const Color& color, const CPoint& ptTopLeft, BOOL bFilled)
{
}

RectangleFigure::RectangleFigure(const RectangleFigure& rectangle)
{
}

Figure* RectangleFigure::Copy() const
{
	return nullptr;
}

void RectangleFigure::Serialize(CArchive& archive)
{
}

HCURSOR RectangleFigure::GetCursor() const
{
	return HCURSOR();
}

BOOL RectangleFigure::Click(const CPoint& ptMouse)
{
	//did the user click on the top left corner?
	DWORD dHalfSquareSide = SQUARE_SIDE / 2;
	CRect rcTopLeft(m_ptTopLeft.x - dHalfSquareSide, m_ptTopLeft.y - dHalfSquareSide, m_ptTopLeft.x + dHalfSquareSide, m_ptTopLeft.y + dHalfSquareSide);
	if (rcTopLeft.PtInRect(ptMouse)) {
		m_eDragMode = MODIFY_TOPLEFT;
		return TRUE;
	}
	//Or the top right corner?
	CRect rcTopRight(m_ptBottomRight.x - dHalfSquareSide, m_ptTopLeft.y - dHalfSquareSide, m_ptBottomRight.x + dHalfSquareSide, m_ptTopLeft.y + dHalfSquareSide);
	if (rcTopRight.PtInRect(ptMouse)) {
		m_eDragMode = MODIFY_TOPRIGHT;
		return TRUE;
	}
	//Or the left bottom corner?
	CRect rcBottomLeft(m_ptTopLeft.x - dHalfSquareSide, m_ptBottomRight.y - dHalfSquareSide, m_ptTopLeft.x + dHalfSquareSide, m_ptBottomRight.y + dHalfSquareSide);
	if (rcBottomLeft.PtInRect(ptMouse)) {
		m_eDragMode = MODIFY_BOTTOMLEFT;
		return TRUE;
	}
	//Or the bottom right corner?
	CRect rcBottomRight(m_ptBottomRight.x - dHalfSquareSide, m_ptBottomRight.y - dHalfSquareSide, m_ptBottomRight.x + dHalfSquareSide, m_ptBottomRight.y + dHalfSquareSide);
	if (rcBottomRight.PtInRect(ptMouse)) {
		m_eDragMode = MODIFY_BOTTOMRIGHT;
		return TRUE;
	}

	CRect rcArea(m_ptTopLeft, m_ptBottomRight);
	rcArea.NormalizeRect();
	if (IsFilled()) {
		m_eDragMode = MOVE_RECTANGLE;
		return rcArea.PtInRect(ptMouse);
	}
	else {
		CSize szMargin(dHalfSquareSide, dHalfSquareSide);
		CRect rcSmallArea(rcArea.TopLeft() + szMargin, rcArea.BottomRight() - szMargin);
		CRect rcLargeArea(rcArea.TopLeft() - szMargin, rcArea.BottomRight() + szMargin);
		m_eDragMode = MOVE_RECTANGLE;
		return (rcLargeArea.PtInRect(ptMouse) & !rcSmallArea.PtInRect(ptMouse));
	}
}	

BOOL RectangleFigure::DoubleClick(const CPoint& ptMouse)
{
	return 0;
}

BOOL RectangleFigure::InSide(const CRect& rcInside) const
{
	return 0;
}

void RectangleFigure::Move(const CSize& szDistance)
{
}

void RectangleFigure::MoveOrModify(const CSize& szDistance)
{
}

void RectangleFigure::Draw(CDC* pDC) const
{
}

CRect RectangleFigure::GetArea() const
{
	CRect rcRectangle(m_ptTopLeft, m_ptBottomRight);
	rcRectangle.NormalizeRect();
	if (IsMarked()) {
		DWORD dHalfSquareSide = SQUARE_SIDE / 2;
		rcRectangle.left -= dHalfSquareSide;
		rcRectangle.top -= dHalfSquareSide;
		rcRectangle.bottom += dHalfSquareSide;
		rcRectangle.right += dHalfSquareSide;
	}
	return rcRectangle;
}
