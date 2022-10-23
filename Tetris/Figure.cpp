#include "pch.h"
#include "Figure.h"

Figure::Figure()
{
}

Figure::Figure(int iDerection, COLORREF rfColor, const SquareInfo& squareInfo)
    :m_iRow(0),
    m_iCol(COLS / 2),
    m_iDirection(iDerection),
    m_rfColor(rfColor)
{
    memcpy(&m_squareInfo, squareInfo, sizeof(m_squareInfo));
}

Figure Figure::operator=(const Figure& figure)
{
    this->m_iRow = figure.m_iRow;
    this->m_iCol = figure.m_iCol;
    this->m_iDirection = figure.m_iDirection;
    this->m_rfColor = figure.m_rfColor;
    this->m_pColorGrid = figure.m_pColorGrid;
    memcpy(this->m_squareInfo, figure.m_squareInfo, sizeof(m_squareInfo));
    return *this;
}

BOOL Figure::IsSquareValid(int iRow, int iCol) const
{
    return (iRow >= 0 && iRow < ROWS) && (iCol >= 0 && iCol < COLS) && (m_pColorGrid->Index(iRow, iCol) == DEFAULT_COLOR);
}

BOOL Figure::IsFigureValid() const
{
	SquareArray* pSquareArray = m_squareInfo[m_iDirection];

    for (int index = 0; index < SQUARE_INFO_SIZE; index++)
    {
        Square& pSquare = (*pSquareArray)[index]; // traversal is wrong

        if (!IsSquareValid(m_iRow + pSquare.Row(), m_iCol + pSquare.Col())) return FALSE;
    }
    return TRUE;
}

BOOL Figure::MoveLeft()
{
    --m_iCol;
    if (IsFigureValid()) return TRUE;
    else {
        ++m_iCol;
        return FALSE;
    }
}

BOOL Figure::MoveRight()
{
    ++m_iCol;
    if (IsFigureValid()) return TRUE;
    else {
        --m_iCol;
        return FALSE;
    }
}

void Figure::RotateClockwiseOneQuarter()
{
    switch (m_iDirection)
    {
    case NORTH:
        m_iDirection = EAST;
        break;
    case EAST:
        m_iDirection = SOUTH;
        break;
    case SOUTH:
        m_iDirection = WEST;
        break;
    case WEST:
        m_iDirection = NORTH;
        break;
    }
}

void Figure::RotateCounterclockwiseOneQuarter()
{
	switch (m_iDirection)
	{
	case NORTH:
		m_iDirection = WEST;
		break;
	case EAST:
		m_iDirection = NORTH;
		break;
	case SOUTH:
		m_iDirection = EAST;
		break;
	case WEST:
		m_iDirection = SOUTH;
		break;
	}
}

BOOL Figure::MoveDown()
{
	++m_iRow;
	if (IsFigureValid()) return TRUE;
	else {
		--m_iRow;
		return FALSE;
	}
}

void Figure::AddToGrid()
{
    SquareArray* pSquareArray = m_squareInfo[m_iDirection];

    for (int index = 0; index < SQUARE_ARRAY_SIZE; index++)
    {
        Square& pSquare = (*pSquareArray)[index];
        m_pColorGrid->Index(m_iRow + pSquare.Row(), m_iCol + pSquare.Col()) = m_rfColor;
    }
}

void Figure::Draw(int iColorStatus, CDC* pDc) const
{
    CPen pen(PS_SOLID, 0, BLACK);
    CPen* pOldPen = pDc->SelectObject(&pen);

    CBrush brush((iColorStatus == COLOR) ? m_rfColor : GrayScale(m_rfColor));

}

CRect Figure::GetArea() const
{
    int iMinRow = 0, iMaxRow = 0, iMinCol = 0, iMaxCol = 0;
    SquareArray* pSquareArray = m_squareInfo[m_iDirection];

    for (int index = 0; index < SQUARE_ARRAY_SIZE; index++)
    {
        Square& square = (*pSquareArray)[index];
        int iRow = square.Row();
        iMinRow = (iRow < iMinRow) ? iRow : iMinRow;
        iMinRow = (iRow < iMaxRow) ? iMaxRow : iRow;

        int iCol = square.Col();
        iMinCol = (iCol < iMinCol) ? iCol : iMinCol;
        iMaxCol = (iCol < iMaxCol) ? iMaxCol : iCol;
    }

    return CRect(m_iCol + iMinCol, m_iRow + iMinRow, m_iCol + iMaxCol, m_iRow + iMaxRow);
}

void DrawSquare(int iRow, int iCol, CDC* pDC)
{

}
