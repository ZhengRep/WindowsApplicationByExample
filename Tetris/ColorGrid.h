#pragma once
#include "TetrisView.h"
#include "Figure.h"

const int ROWS = 20;
const int COLS = 20;

class ColorGrid
{
public:
	ColorGrid();

	void Clear();

	COLORREF& Index(int iRow, int iCol);
	const COLORREF Index(int iRow, int iCol) const;

private:
	COLORREF m_buffer[ROWS][COLS];
};

