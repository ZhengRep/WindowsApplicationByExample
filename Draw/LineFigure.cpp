#include "pch.h"
#include "LineFigure.h"

LineFigure::LineFigure()
{
}

LineFigure::LineFigure(const Color& color, const CPoint& ptMouse)
	:Figure(color),
	m_ptFirst(ptMouse)
{

}

LineFigure::LineFigure(const LineFigure& line)
{
	m_ptFirst = line.m_ptFirst;
	m_ptLast = line.m_ptLast;
	m_eDragMode = line.m_eDragMode;

}

Figure* LineFigure::Copy() const
{
	return nullptr;
}

void LineFigure::Serialize(CArchive& archive)
{
}

HCURSOR LineFigure::GetCursor() const
{
	return HCURSOR();
}

BOOL LineFigure::Click(const CPoint& ptMouse)
{
	//Did the user click on the first or last
	DWORD dHalfSquareSide = SQUARE_SIDE / 2;
	CRect rcFirst(m_ptFirst.x - dHalfSquareSide, m_ptFirst.y - dHalfSquareSide, m_ptFirst.x + dHalfSquareSide, m_ptFirst.y + dHalfSquareSide);

	if (rcFirst.PtInRect(ptMouse)) {
		m_eDragMode = MODIFY_FIRST;
		return TRUE;
	}

	//or the second ont
	CRect rcLast(m_ptLast.x - dHalfSquareSide, m_ptLast.y - dHalfSquareSide, m_ptLast.x + dHalfSquareSide, m_ptLast.y + dHalfSquareSide);
	if (rcLast.PtInRect(ptMouse)) {
		m_eDragMode = MODIFY_LAST;
		return TRUE;
	}

	m_eDragMode = MOVE_LINE;
	//if the line is vertival
	if (m_ptFirst.x == m_ptLast.x) {
		CRect rcLine(m_ptFirst.x - dHalfSquareSide, m_ptFirst.y, m_ptLast.x + dHalfSquareSide, m_ptLast.y);
		rcLine.NormalizeRect(); //what is normalize?
		return rcLine.PtInRect(ptMouse);
	}
	else {
		CRect rcLine(m_ptFirst, m_ptLast);
		rcLine.NormalizeRect();
		if (rcLine.PtInRect(ptMouse)) {
			CPoint ptMin = (m_ptFirst.x < m_ptLast.x) ? m_ptFirst : m_ptLast;
			CPoint ptMax = (m_ptFirst.x > m_ptLast.x) ? m_ptFirst : m_ptLast;
			int cxLine = ptMax.x - ptMin.x;
			int cyLine = ptMax.y - ptMin.y;
			int cxMouse = ptMouse.x - ptMin.x;
			int cyMouse = ptMouse.y - ptMin.y;
			return fabs(cyMouse - cxMouse * (double)cyLine / cxLine) <= dHalfSquareSide;
		}
		return FALSE;
	}
}

BOOL LineFigure::DoubleClick(const CPoint& ptMouse)
{
	return 0;
}

BOOL LineFigure::Inside(const CRect& rcInside) const
{
	return 0;
}

void LineFigure::MoveOrModify(const CSize& szDistance)
{
	switch (m_eDragMode)
	{
	case CREATE_LINE:
		m_ptLast += szDistance;
		break;
	case MODIFY_FIRST:
		m_ptFirst += szDistance;
		break;
	case MODIFY_LAST:
		m_ptLast += szDistance;
		break;
	case MOVE_LINE:
		Move(szDistance);
		break;
	}
}

void LineFigure::Move(const CSize& szDistance)
{
	m_ptFirst += szDistance;
	m_ptLast += szDistance;
}

void LineFigure::Draw(CDC* pDC) const
{
	//CPen pen(PS_SOLID, 0, GetColor());

}

CRect LineFigure::GetArea() const
{
	return CRect();
}
