#pragma once

/*
typedef struct tagLOGFONT
{
	LONG lfHeight;
	LONG lfWidth;
	LONG lfEscapement;
	LONG lfOrientation;
	LONG lfWeight;
	BYTE lfItalic;
	BYTE lfUnderline;
	BYTE lfStrikeOut;
	BYTE lfCharSet;
	BYTE lfOutPrecision;
	BYTE lfClipPecision;
	BYTE lfQuality;
	BYTE lfPitchAndFamily;
	TCHAR lfFacceName[LF_FACESIZE];
}LOGFONT, *PLOGFONT;
*/



class MyFont
{
public:
	MyFont();
	MyFont(CString stName, int iSize);
	MyFont(const LOGFONT& logFont);
	MyFont(const MyFont& font);
	operator LOGFONT() { return m_logFont; };
	operator PLOGFONT() { return &m_logFont; };
	MyFont PointsToMeters() const;
	MyFont& operator=(const MyFont& font);
	BOOL operator==(const MyFont& font) const;
	BOOL operator!=(const MyFont& font) const;
	void Serialize(CArchive& archive);
	BOOL IsItalic() const { return m_logFont.lfItalic; };

private:
	LOGFONT m_logFont;
};
