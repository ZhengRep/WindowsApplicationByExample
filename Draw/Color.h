#pragma once

static const COLORREF BLACK = RGB(0, 0, 0);

class Color
{
public:
	Color();
	Color(const COLORREF crRedGreenBlue);
	Color(const Color& color);

	operator COLORREF() const;
	Color& operator=(const Color& color);
	void Serialize(CArchive& ar);
	Color& Inverse() const;

private:
	COLORREF m_crRedGreenBlue;
};

