#include "pch.h"
#include "Font.h"


MyFont::MyFont()
{
	memset(&m_logFont, 0, sizeof m_logFont);
}

MyFont::MyFont(CString stName, int iSize)
{
	memset(&m_logFont, 0, sizeof m_logFont);
	wcscpy_s(m_logFont.lfFaceName, stName);
	m_logFont.lfWeight = iSize;
}

MyFont::MyFont(const LOGFONT& logFont)
{
	m_logFont = logFont;
}

MyFont::MyFont(const MyFont& font)
{
	m_logFont = font.m_logFont;
}

MyFont MyFont::PointsToMeters() const
{
	LOGFONT logFont = m_logFont;
	logFont.lfWidth = (int)((double)2540 * logFont.lfWidth / 72);
	logFont.lfHeight = (int)((double)2540 * logFont.lfHeight / 72);
	return MyFont(logFont);
}

MyFont& MyFont::operator=(const MyFont& font)
{
	// TODO: insert return statement here
	return MyFont(font);
}

BOOL MyFont::operator==(const MyFont& font) const
{
	return (memcmp(&m_logFont, &font.m_logFont, sizeof m_logFont) == 0);
}

BOOL MyFont::operator!=(const MyFont& font) const
{
	return (memcmp(&m_logFont, &font.m_logFont, sizeof m_logFont) != 0);
}

void MyFont::Serialize(CArchive& archive)
{
	if (archive.IsStoring()) {
		archive.Write(&m_logFont, sizeof m_logFont);
	}
	else {
		archive.Read(&m_logFont, sizeof m_logFont);
	}
}
