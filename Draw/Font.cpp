#include "pch.h"
#include "Font.h"

Font::Font()
{
}

Font::Font(CString stName, int iSize)
{
	memset(&m_logFont, 0, sizeof m_logFont);
	wcscpy_s(m_logFont.lfFacceName, stName);
	m_logFont.lfWeight = iSize;
}

Font::Font(const LOGFONT& logFont)
{
	m_logFont = logFont;
}

Font::Font(const Font& font)
{
	m_logFont = font.m_logFont;
}

Font Font::PointsToMeters() const
{
	LOGFONT logFont = m_logFont;
	logFont.lfWidth = (int)((double)2540 * logFont.lfWidth / 72);
	logFont.lfHeight = (int)((double)2540 * logFont.lfHeight / 72);
	return Font(logFont);
}

Font& Font::operator=(const Font& font)
{
	// TODO: insert return statement here
	return Font(font);
}

BOOL Font::operator==(const Font& font) const
{
	return (memcmp(&m_logFont, &font.m_logFont, sizeof m_logFont) == 0);
}

BOOL Font::operator!=(const Font& font) const
{
	return (memcmp(&m_logFont, &font.m_logFont, sizeof m_logFont) != 0);
}

void Font::Serialize(CArchive& archive)
{
	if (archive.IsStoring()) {
		archive.Write(&m_logFont, sizeof m_logFont);
	}
	else {
		archive.Read(&m_logFont, sizeof m_logFont);
	}
}
