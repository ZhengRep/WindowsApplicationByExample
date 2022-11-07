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

BOOL TextFigure::KeyDown(UINT uChar, CDC* pDC)
{
    int iLength = m_stText.GetLength();
    switch (uChar)
    {
    case VK_HOME:
        if (m_iEditIndex > 0) {
            m_iEditIndex = 0;
        }
        break;
    case VK_END:
        if (m_iEditIndex < iLength) {
            m_iEditIndex = iLength;
        }
        break;
    case VK_LEFT:
        if (m_iEditIndex > 0) {
            m_iEditIndex--;
        }
        break;
    case VK_RIGHT:
        if (m_iEditIndex < iLength) {
            m_iEditIndex++;
        }
        break;
        //...
    }
    return FALSE;
}

BOOL TextFigure::CharDown(UINT uChar, CDC* pDC, KeyboardState eKeyboardState)
{
    if (m_iEditIndex == m_stText.GetLength()) {
        m_stText.AppendChar(uChar);
    }
    else {
        switch (eKeyboardState)
        {
        case KS_INSERT:
            m_stText.Insert(m_iEditIndex, uChar);
            break;
        case KS_OVERWRITE:
            m_stText.SetAt(m_iEditIndex, uChar);
            break;
        }
    }
    ++m_iEditIndex;
    GenerateCaretArray(pDC);
}

void TextFigure::SetPreviousText(CDC* pDC)
{
}

void TextFigure::Draw(CDC* pDC) const
{
    CFont cFont;
    cFont.CreatePointFontIndirect(m_font.PointsToMeters());
    CFont* pPreFont = pDC->SelectObject(&cFont); 
    pDC->SetTextColor((COLORREF)GetColor());
    pDC->TextOutW(m_ptText.x, m_ptText.y + m_szText.cy, m_stText);
    pDC->SelectObject(pPreFont);
    if (IsMarked()) {
        CPen pen(PS_SOLID, 0, BLACK);
        CPen* pOldPen = pDC->SelectObject(&pen);
        CBrush brush(BLACK);
        CBrush* pOldBrush = pDC->SelectObject(&brush);
        int xLeft = m_ptText.x;
        int xRight = m_ptText.x + m_szText.cx;
        int yTop = m_ptText.y;
        int yBottom = m_ptText.y + m_szText.cy;
        int xCenter = m_ptText.x + m_szText.cx / 2;
        int yCenter = m_ptText.y + m_szText.cy / 2;
        DWORD dHalfSquareSide = SQUARE_SIDE / 2;
        CRect rcLeft(xLeft - dHalfSquareSide, yCenter - dHalfSquareSide, xLeft + dHalfSquareSide, yCenter + dHalfSquareSide);
        CRect rcRight(xRight - dHalfSquareSide, yCenter - dHalfSquareSide, xRight + dHalfSquareSide, yCenter + dHalfSquareSide);
        CRect rcTop(xCenter - dHalfSquareSide, yTop - dHalfSquareSide, xCenter + dHalfSquareSide, yTop + dHalfSquareSide);
        CRect rcBottom(xCenter - dHalfSquareSide, yBottom - dHalfSquareSide, xCenter + dHalfSquareSide, yBottom + dHalfSquareSide);
        pDC->Rectangle(rcLeft);
        pDC->Rectangle(rcRight);
        pDC->Rectangle(rcTop);
        pDC->Rectangle(rcBottom);

        pDC->SelectObject(pOldPen);
        pDC->SelectObject(pOldBrush);
    }
}

CRect TextFigure::GetArea() const
{
    CRect rcText(m_ptText, m_szText);
    rcText.NormalizeRect();
    if (IsMarked()) {
        DWORD dHalfSquareSide = SQUARE_SIDE / 2;
        rcText.left -= dHalfSquareSide;
        rcText.right += dHalfSquareSide;
        rcText.top -= dHalfSquareSide;
        rcText.bottom += dHalfSquareSide;
    }
    return rcText;
}

Font* TextFigure::GetFont()
{
    return nullptr;
}

void TextFigure::SetFont(const Font& font, CDC* pDC)
{
    m_font = font;
    GenerateCaretArray(pDC);
}

void TextFigure::GenerateCaretArray(CDC* pDC)
{
    CFont cFont;
    cFont.CreatePointFontIndirect(m_font.PointsToMeters());
    CFont* pPrevFont = pDC->SelectObject(&cFont);
    TEXTMETRIC textMetric;
    pDC->GetTextMetrics(&textMetric);
    m_iAverageWidth = textMetric.tmAveCharWidth;
    if (!m_stText.IsEmpty()) {
        m_szText = pDC->GetTextExtent(m_stText);
    }
    else {
        m_szText.SetSize(0, textMetric.tmHeight);
    }
    int iWidth = 0, iSize = m_stText.GetLength();
    m_caretArray.SetSize(iSize + 1);
    for (int iIndex = 0; iIndex < iSize; ++iIndex)
    {
        CSize szChar = pDC->GetTextExtent(m_stText.Mid(iIndex, 1));
        m_caretArray[iIndex] = iWidth;
        iWidth = +szChar.cx;
    }
    m_caretArray[iSize] = iWidth;
    pDC->SelectObject(pPrevFont);
}

CRect TextFigure::GetCaretArray(KeyboardState eKeyboardState)
{
    CPoint ptCaret(m_ptText.x + m_caretArray[m_iEditIndex], m_ptText.y);
    switch (eKeyboardState)
    {
    case KS_INSERT:
    {
        CSize szCaret(1, m_szText.cy);
        return CRect(ptCaret, ptCaret + szCaret);
    }
    break;
    case KS_OVERWRITE:
    {
        CSize szCaret(m_iAverageWidth, m_szText.cy);
        return CRect(ptCaret, ptCaret + szCaret);
    }
    break;
    }
    return CRect();
}

HCURSOR TextFigure::GetCursor() const
{
    return HCURSOR();
}
