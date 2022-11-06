#include "pch.h"
#include "TextFigure.h"

TextFigure::TextFigure()
{
}

TextFigure::TextFigure(const Color& color, const CPoint& ptMouse, const Font& font, CDC* pDC)
{
}

TextFigure::TextFigure(const TextFigure& text)
{
}

Figure* TextFigure::Copy() const
{
    return nullptr;
}

void TextFigure::Serialize(CArchive& archive)
{
    Figure::Serialize(archive);
    m_font.Serialize(archive);
    m_caretArray.Serialize(archive);
    if (archive.IsStoring()) {
        archive << m_ptText << m_stText << m_szText << m_iAverageWidth;
    }
    if(archive.IsLoading()) {
        archive >> m_ptText >> m_stText >> m_szText >> m_iAverageWidth;
        m_iEditIndex = 0;
    }
}

BOOL TextFigure::Click(const CPoint& ptMouse)
{
    m_eDragMode = MOVE_TEXT;
    CRect rcText(m_ptText, m_szText);
    return rcText.PtInRect(ptMouse);
}

BOOL TextFigure::DoubleClick(const CPoint& ptMouse)
{
    CRect rcText(m_ptText, m_szText);
    if (rcText.PtInRect(ptMouse)) {
        CPoint ptTextMouse = ptMouse - m_ptText;
        int iSize = m_stText.GetLength();
        for (int index = 0; index < iSize; index++)
        {
            int iFirstPos = m_caretArray[index];
            int iLastPos = m_caretArray[index + 1] - 1;
            if (ptTextMouse.x >= iFirstPos && ptTextMouse.x <= iLastPos) {
                if ((ptTextMouse.x - iFirstPos) < (iLastPos - ptTextMouse.x)) {
                    m_iEditIndex = index;
                }
                else {
                    m_iEditIndex = index + 1;
                }
                break;
            }
        }
        m_eDragMode = EDIT_TEXT;
        m_stPreviousText = m_stText;
        return TRUE;
    }
    return FALSE;
}

BOOL TextFigure::Inside(const CRect& rcInside) const
{
    CRect rcText(m_ptText, m_szText);
    rcText.NormalizeRect();
    return rcInside.PtInRect(rcText.TopLeft()) & rcInside.PtInRect(rcText.BottomRight());
}

void TextFigure::MoveOrModify(const CSize& szDistance)
{
}

void TextFigure::Move(const CSize& szDistance)
{
}

BOOL TextFigure::KeyDown(UINT uChar, CDC* pDC, KeyboardState eKeyboardState)
{
    return 0;
}

void TextFigure::SetPreviousText(CDC* pDC)
{
}

void TextFigure::Draw(CDC* pDC) const
{
}

CRect TextFigure::GetArea() const
{
    return CRect();
}

Font* TextFigure::GetFont()
{
    return nullptr;
}

void TextFigure::SetFont(const Font& font, CDC* pDC)
{
}

void TextFigure::GenerateCaretArray(CDC* pDC)
{
}

CRect TextFigure::GetCaretArray(KeyboardState eKeyboardState)
{
    return CRect();
}

HCURSOR TextFigure::GetCursor() const
{
    return HCURSOR();
}
