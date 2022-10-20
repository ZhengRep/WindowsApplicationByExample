
// RingDoc.cpp : implementation of the CRingDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Ring.h"
#endif

#include "RingDoc.h"

#include <propkey.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CRingDoc

IMPLEMENT_DYNCREATE(CRingDoc, CDocument)

BEGIN_MESSAGE_MAP(CRingDoc, CDocument)
	ON_COMMAND(ID_BUTTON_COLORRED, OnColorRed)
	ON_COMMAND(ID_BUTTON_COLORDIALOG, OnColorDialog)
END_MESSAGE_MAP()


// CRingDoc construction/destruction

CRingDoc::CRingDoc() noexcept
{
	// TODO: add one-time construction code here
	m_nextColor = AfxGetApp()->GetProfileInt(_T("Ring"), _T("Color"), WHITE);

}

CRingDoc::~CRingDoc()
{
	AfxGetApp()->WriteProfileInt(_T("Ring"), _T("Color"), m_nextColor);
}

BOOL CRingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CRingDoc serialization

void CRingDoc::Serialize(CArchive& ar)
{
	m_colorArray.Serialize(ar);
	m_pointArray.Serialize(ar);

	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_nextColor; //to store << extraction
	}
	else
	{
		// TODO: add loading code here
		ar >> m_nextColor; //to load >> insertion
	}
}

/*
cin  >> extraction
cout <<  insertion
*/

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CRingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CRingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}



void CRingDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}


#endif // SHARED_HANDLERS

void CRingDoc::OnColorRed()
{
	m_nextColor = RED;
}

void CRingDoc::OnColorDialog()
{
	CColorDialog colorDialog(m_nextColor);
	if (colorDialog.DoModal() == IDOK)
	{
		m_nextColor = colorDialog.GetColor();
	}
}

void CRingDoc::MouseDown(CPoint point)
{
	m_pointArray.Add(point);
	m_colorArray.Add(m_nextColor);

	SetModifiedFlag(TRUE);

	UpdateAllViews(NULL);
}
// CRingDoc diagnostics

#ifdef _DEBUG
void CRingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CRingDoc commands
