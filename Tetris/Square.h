#pragma once
class Square
{
public:
	Square(int iRow, int iCol);

	int Row() const { return m_iRow; };
	int Col() const { return m_iCol; };

private:
	int m_iRow;
	int m_iCol;
};

