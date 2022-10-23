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
	if (iRow > -2 && iRow < 0) {
		COLORREF white = RGB(255, 255, 255);
		return white;
	}
	return m_buffer[iRow][iCol];
}

const COLORREF ColorGrid::Index(int iRow, int iCol) const
{
	//The figure shows above grid
	if (iRow > -2 && iRow < 0) {
		COLORREF white = RGB(255, 255, 255);
		return white;
	}
	return m_buffer[iRow][iCol];
}
