#include "pch.h"
#include "Color.h"

Color::Color()
{
	m_crRedGreenBlue = COLORREF(RGB(255, 255, 255));
}

 Color::Color(const COLORREF crRedGreenBlue)
{
	 m_crRedGreenBlue = crRedGreenBlue;
}

 Color::Color(const Color& color)
{
	 m_crRedGreenBlue = color.m_crRedGreenBlue;
}

 //how to implement?
 /*Color::operator COLORREF() const
{

}*/

 Color& Color::operator=(const Color& color)
{
	// TODO: insert return statement here
	 this->m_crRedGreenBlue = color.m_crRedGreenBlue;
	 return *this;
}

 void Color::Serialize(CArchive& ar)
{

}

 Color& Color::Inverse() const
{
	 int iRed = GetRValue(m_crRedGreenBlue);
	 int iGreen = GetGValue(m_crRedGreenBlue);
	 int iBlue = GetBValue(m_crRedGreenBlue);
	 return Color(COLORREF(RGB(255 - iRed, 255 - iGreen, 255 - iBlue)));
}