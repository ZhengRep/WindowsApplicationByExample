#include "pch.h"
#include "ColorGrid.h"

ColorGrid::ColorGrid()
{
	for (int iRow = 0; iRow < ROWS; iRow++)
	{
		for (int iCol = 0; iCol < COLS; iCol++)
		{
			m_buffer[iRow][iCol] = WHITE;
		}
	}
}

void ColorGrid::Clear()
{
	for (int iRow = 0; iRow < ROWS; iRow++)
	{
		for (int iCol = 0; iCol < COLS; iCol++)
		{
			m_buffer[iRow][iCol] = WHITE;
		}
	}
}

COLORREF& ColorGrid::Index(int iRow, int iCol)
{
	// TODO: insert return statement here
	check(iRow >= 0 && iRow < ROWS);
	check(iCol >= 0 && iCol < COLS);
	return m_buffer[iRow][iCol];
}

const COLORREF ColorGrid::Index(int iRow, int iCol) const
{
	check(iRow >= 0 && iRow < ROWS);
	check(iCol >= 0 && iCol < COLS);
	return m_buffer[iRow][iCol];
}
