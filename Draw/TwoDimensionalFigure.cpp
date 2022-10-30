#include "pch.h"
#include "TwoDimensionalFigure.h"

TwoDimensionalFigure::TwoDimensionalFigure()
	:m_bFilled(FALSE)
{

}

TwoDimensionalFigure::TwoDimensionalFigure(const Color& color, BOOL bFilled)
	:Figure(color), 
	m_bFilled(bFilled)

{
}

void TwoDimensionalFigure::Serialize(CArchive& archive)
{
	Figure::Serialize(archive);
	if (archive.IsStoring()) {
		archive << m_bFilled;
	}
	else {
		archive >> m_bFilled;
	}
}
