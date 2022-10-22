#pragma once

const COLORREF BLACK = RGB(0, 0, 0);
const COLORREF WHITE = RGB(255, 255, 255);
const COLORREF DEFAULT_COLOR = WHITE;

class ColorGrid;

enum {NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3};

const int SQUARE_ARRAY_SIZE = 4;
const int SQUARE_INFO_SIZE = 4;

// one figure have four square and saved in SquareArray
typedef Square SquareArray[SQUARE_ARRAY_SIZE]; //one figure = four Square

//one square have 
//north east south west
typedef SquareArray* SquareInfo[SQUARE_INFO_SIZE]; //squareinfo does have four deferent Figure

class Figure
{
public:
	Figure() {};
	Figure(int iDerection, COLORREF rfColor, const SquareInfo& squareInfo);
	Figure operator=(const Figure& figure);
	void SetColorGrid(ColorGrid* pColorGrid) { m_pColorGrid = pColorGrid; };
	
private:
	BOOL IsSquareValid(int iRow, int iCol) const;

public:
	BOOL IsFigureValid() const;
	BOOL MoveLeft();
	BOOL MoveRight();

public:
	void RotateClockwiseOneQuarter();
	void RotateCounterclockwiseOneQuarter();

	CRect GetArea() const;
	BOOL MoveDown();
	void AddToGrid();

public:
	void Draw(int iColorStatus, CDC* pDc) const;
	friend void DrawSquare(int iRow, int iCol, CDC* pDC);

private:
	ColorGrid* m_pColorGrid;
	COLORREF m_rfColor;
	int m_iRow, m_iCol, m_iDirection;
	SquareInfo m_squareInfo; //record different rotate figure

};

typedef CArray<const Figure> FigurePtrArray;