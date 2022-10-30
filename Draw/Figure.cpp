#include "pch.h"
#include "Figure.h"

Figure::Figure()
	:m_figureColor(0),
	m_bMarked(FALSE)
{
}

Figure::Figure(const Color& color, BOOL bMarked)
	:m_figureColor(color),
	m_bMarked(bMarked)
{

}

Figure::Figure(const Figure& figure)
	:m_figureColor(figure.m_figureColor),
	m_bMarked(figure.m_bMarked)
{
}

void Figure::Serialize(CArchive& archive)
{
	CObject::Serialize(archive);
	m_figureColor.Serialize(archive);
}

