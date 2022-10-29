
// TetrisDoc.cpp : implementation of the CTetrisDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Tetris.h"
#endif

#include "TetrisDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "FigureInfo.h"

Figure redFigue(NORTH, RED, RedInfo);
Figure brownFigue(EAST, BROWN, BrownInfo);
Figure turqoiseFigure(EAST, TURQUOISE, TurquoiseInfo);
Figure greenFigure(EAST, GREEN, GreenInfo);
Figure yellowFigure(SOUTH, YELLOW, YellowInfo);
Figure blueFigure(SOUTH, BLUE, BlueInfo);
Figure purpleFigure(SOUTH, PURPLE, PurpleInfo);

Figure CTetrisDoc::m_figureArray[FIGURE_ARRAY_SIZE] = { redFigue, brownFigue, turqoiseFigure, greenFigure, yellowFigure, blueFigure, purpleFigure };


// CTetrisDoc

IMPLEMENT_DYNCREATE(CTetrisDoc, CDocument)

BEGIN_MESSAGE_MAP(CTetrisDoc, CDocument)
END_MESSAGE_MAP()


// CTetrisDoc construction/destruction

CTetrisDoc::CTetrisDoc() noexcept
	:m_iScore(0)
{
	// TODO: add one-time construction code here
	//to load score list
	m_activeFigure = m_figureArray[rand() % FIGURE_ARRAY_SIZE];
	m_activeFigure.SetColorGrid(&m_colorGrid);

	m_nextFigure = m_figureArray[rand() % FIGURE_ARRAY_SIZE];

	m_scoreList = new IntList;

	LoadScoreList();
}

CTetrisDoc::~CTetrisDoc()
{
	//to store score list
}

BOOL CTetrisDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}


#ifdef SHARED_HANDLERS

// Support for thumbnails
void CTetrisDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CTetrisDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CTetrisDoc::SetSearchContent(const CString& value)
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

// CTetrisDoc diagnostics

#ifdef _DEBUG
void CTetrisDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTetrisDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG



void CTetrisDoc::SaveScoreList()
{
	CFile file;
	file.Open(_T("TetrisHistoryScore"),CFile::modeWrite);
	CArchive ar(&file, CArchive::store);
	m_scoreList->Serialize(ar);
	ar.Close();
	file.Close();
}

void CTetrisDoc::LoadScoreList()
{
	CFile file;
	file.Open(_T("TetrisHistoryScore"), CFile::modeRead | CFile::modeNoTruncate | CFile::modeCreate);
	if (file.GetLength()) {
		CArchive ar(&file, CArchive::load);
		m_scoreList->Serialize(ar);
		ar.Close();
	}
	file.Close();
}
// CTetrisDoc commands

void CTetrisDoc::LeftArrowKey()
{
	CRect rcOldArea = m_activeFigure.GetArea();
	if (m_activeFigure.MoveLeft())
	{
		CRect rcNewArea = m_activeFigure.GetArea();
		UpdateAllViews(NULL, COLOR, (CObject*)&rcOldArea);
		UpdateAllViews(NULL, COLOR, (CObject*)&rcNewArea);
		SetModifiedFlag();
	}
}

void CTetrisDoc::RightArrowKey()
{

	CRect rcOldArea = m_activeFigure.GetArea();
	if (m_activeFigure.MoveRight())
	{
		CRect rcNewArea = m_activeFigure.GetArea();
		UpdateAllViews(NULL, COLOR, (CObject*)&rcOldArea);
		UpdateAllViews(NULL, COLOR, (CObject*)&rcNewArea);
		SetModifiedFlag();
	}
}

void CTetrisDoc::UpArrowKey()
{
	CRect rcOldArea = m_activeFigure.GetArea();
	m_activeFigure.RotateCounterclockwiseOneQuarter();
	if (m_activeFigure.IsFigureValid()) {
		CRect rcNewArea = m_activeFigure.GetArea();
		UpdateAllViews(NULL, COLOR, (CObject*)&rcOldArea);
		UpdateAllViews(NULL, COLOR, (CObject*)&rcNewArea);
		SetModifiedFlag();
	}
	else {
		m_activeFigure.RotateClockwiseOneQuarter();
	}
}

void CTetrisDoc::DownArrowKey()
{
	CRect rcOldArea = m_activeFigure.GetArea();
	m_activeFigure.RotateClockwiseOneQuarter();
	if (m_activeFigure.IsFigureValid()) {
		CRect rcNewArea = m_activeFigure.GetArea();
		UpdateAllViews(NULL, COLOR, (CObject*)&rcOldArea);
		UpdateAllViews(NULL, COLOR, (CObject*)&rcNewArea);
		SetModifiedFlag();
	}
	else {
		m_activeFigure.RotateCounterclockwiseOneQuarter();
	}
}

BOOL CTetrisDoc::Timer()
{
	SetModifiedFlag();
	CRect rcOldArea = m_activeFigure.GetArea();
	if (m_activeFigure.MoveDown()) {
		CRect rcNewArea = m_activeFigure.GetArea();
		UpdateAllViews(NULL, COLOR, (CObject*)&rcOldArea);
		UpdateAllViews(NULL, COLOR, (CObject*)&rcNewArea);
		return TRUE;
	}
	else {
		m_activeFigure.AddToGrid();
		m_activeFigure = m_nextFigure;
		m_activeFigure.SetColorGrid(&m_colorGrid);

		CRect rcActiveArea = m_activeFigure.GetArea();
		UpdateAllViews(NULL, COLOR, (CObject*)&rcActiveArea);
		m_nextFigure = m_figureArray[rand() % FIGURE_ARRAY_SIZE];
		UpdateAllViews(NULL, COLOR, (CObject*)&NEXT_AREA);
		DeleteFullRows();
		if (!m_activeFigure.IsFigureValid()) { //is full
			GameOver();
		}
		return FALSE;
	}
}

void CTetrisDoc::SpaceKey()
{
	while (Timer())
	{
		Sleep(20);
	}
}

void CTetrisDoc::GameOver()
{
	UpdateAllViews(NULL, GRAY);
	if (NewGame()) {
		m_colorGrid.Clear();
		m_activeFigure = m_figureArray[rand() % FIGURE_ARRAY_SIZE];
		m_activeFigure.SetColorGrid(&m_colorGrid);

		m_iScore = 0;

		m_nextFigure = m_figureArray[rand() % FIGURE_ARRAY_SIZE];
		UpdateAllViews(NULL, COLOR);
	}
	else {
		SaveScoreList();
		exit(0);
	}
}

BOOL CTetrisDoc::NewGame()
{

	CString showMsg;
	int rank;
	if ((rank = AddScoreToList()) != 0) {
		showMsg.Format(TEXT("Get new score!\nCurrent score %d rank %d!\nNew game again?"), m_iScore, rank);
	}
	else {
		showMsg.Format(TEXT("Current score is: %d.\n New game again?"), m_iScore);
	}
	if (MessageBox(NULL, showMsg, TEXT("Tetris"), MB_YESNO) == IDYES) {
		return TRUE;
	}
	return FALSE;
}


//return rank
int CTetrisDoc::AddScoreToList()
{
	// 2
	// 3 -> 3 2
	// 1 -> 3 2 1
	// 0 -> 3 2 1 0
	// 5 -> 5 3 2 1
	// 4 -> 5 4 3 2 
	int size = static_cast<int>(m_scoreList->GetCount());
	//sorted insert value
	if (size == 0) {
		m_scoreList->AddTail(m_iScore);
		return 1;
	}
	POSITION pos = m_scoreList->GetHeadPosition();
	POSITION posPre = m_scoreList->GetHeadPosition();
	int lastValue;
	int hisScore;
	int index;
	if (size < 10) { //top 4 and is not full
		for (index = 1; index <= size; index++)
		{
			if (index != 1) lastValue = m_scoreList->GetNext(posPre);
			hisScore = m_scoreList->GetNext(pos);
			if (hisScore < m_iScore) {
				if (index == 1) {
					m_scoreList->AddHead(m_iScore);
				}
				else {
					//swap before
					m_scoreList->InsertAfter(m_scoreList->Find(lastValue), m_iScore);
				}
				return index;
			}
		}
		m_scoreList->AddTail(m_iScore);
		return ++index;
	}
	else { //is full
		for (index = 1; index <= size; index++)
		{
			if (index != 1) lastValue = m_scoreList->GetNext(posPre);
			hisScore = m_scoreList->GetNext(pos);
			if (hisScore < m_iScore) {
				if (index == 1) {
					m_scoreList->AddHead(m_iScore);
				}
				else {
					//swap before
					m_scoreList->InsertAfter(m_scoreList->Find(lastValue), m_iScore);
				}
				m_scoreList->RemoveTail();
				return index;
			}
		}
		return 0;
	}
}

void CTetrisDoc::DeleteFullRows()
{
	int iRow = ROWS - 1;
	while (iRow >= 0)
	{
		if (isRowFull(iRow)) {
			FlashRow(iRow);
			DeleteRow(iRow);
			++m_iScore;
			UpdateAllViews(NULL, COLOR, (CObject*)&SCORE_AREA);
		}
		else {
			--iRow;
		}
	}
}

BOOL CTetrisDoc::isRowFull(int iRow)
{
	for (int iCol = 0; iCol < COLS; iCol++)
	{
		if (m_colorGrid.Index(iRow, iCol) == DEFAULT_COLOR) return FALSE;
	}
	return TRUE;
}

void CTetrisDoc::FlashRow(int iFlashRow)
{
	for (int iCount = 0; iCount < 3; ++iCount)
	{
		CRect rcRowArea(0, iFlashRow, COLS, iFlashRow + 1);
		UpdateAllViews(NULL, GRAY, (CObject*)&rcRowArea);
		Sleep(50);
		CRect rcRowArea2(0, iFlashRow, COLS, iFlashRow + 1);
		UpdateAllViews(NULL, COLOR, (CObject*)&rcRowArea2);
		Sleep(50);
	}
}

void CTetrisDoc::DeleteRow(int iDeleteRow)
{
	for (int iRow = iDeleteRow; iRow > 0; --iRow)
	{
		for (int iCol = 0; iCol < COLS; iCol++)
		{
			m_colorGrid.Index(iRow, iCol) = m_colorGrid.Index(iRow - 1, iCol);
		}
	}
	for (int iCol = 0; iCol < COLS; ++iCol)
	{
		m_colorGrid.Index(0, iCol) = WHITE;
	}
	CRect rcArea(0, 0, COLS, iDeleteRow + 1);
	UpdateAllViews(NULL, COLOR, (CObject*)&rcArea);
}

