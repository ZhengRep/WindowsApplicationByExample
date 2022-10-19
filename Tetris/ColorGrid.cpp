#include "pch.h"
#include "ColorGrid.h"

ColorGrid::ColorGrid()
{
}

void ColorGrid::Clear()
{

}

COLORREF& ColorGrid::Index(int iRow, int iCol)
{
	// TODO: insert return statement here
	/*check(iRow >= 0 && iRow < ROWS);
	check(iCol >= 0 && iCol < COLS);*/
	return m_buffer[iRow][iCol];
}

const COLORREF ColorGrid::Index(int iRow, int iCol) const
{
	/*check(iRow >= 0 && iRow < ROWS);
	check(iCol >= 0 && iCol < COLS);*/
	return m_buffer[iRow][iCol];
}

void ColorGrid::Serialize(CArchive& archive)
{

}
