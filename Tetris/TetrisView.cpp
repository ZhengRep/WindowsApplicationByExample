
// TetrisView.cpp : implementation of the CTetrisView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Tetris.h"
#endif

#include "TetrisDoc.h"
#include "TetrisView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTetrisView

IMPLEMENT_DYNCREATE(CTetrisView, CView)

BEGIN_MESSAGE_MAP(CTetrisView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTetrisView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()

	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CTetrisView construction/destruction

CTetrisView::CTetrisView() noexcept
{
	// TODO: add construction code here

}

CTetrisView::~CTetrisView()
{
}

BOOL CTetrisView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTetrisView drawing

void CTetrisView::OnDraw(CDC* pDc /*pDC*/)
{
	CTetrisDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CPen pen(PS_SOLID, 0, BLACK);
	CPen* pOldPen = pDc->SelectObject(&pen);
	pDc->MoveTo(COLS * g_iColWidth, 0);
	pDc->MoveTo(COLS * g_iColWidth, ROWS * g_iRowHeight);

	DrawGrid(pDc);
	DrawScoreAndScoreList(pDc);
	DrawActiveAndNextFigure(pDc);
	pDc->SelectObject(&pOldPen);
}


// CTetrisView printing


void CTetrisView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTetrisView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTetrisView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTetrisView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CTetrisView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTetrisView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

int CTetrisView::OnCreate(LPCREATESTRUCT lpcs)
{
	//check view has been correctly create
	if (CView::OnCreate(lpcs) == -1) {
		return -1;
	}

	m_pTetrisDoc = (CTetrisDoc*)m_pDocument;
	//check(m_pTetrisDoc != NULL);
	ASSERT_VALID(m_pTetrisDoc);
	return 0;
}

void CTetrisView::OnSize(UINT nType, int cx, int cy)
{
	g_iColWidth = ( cx / 2) / COLS;
	g_iRowHeight = cy / ROWS;
}

void CTetrisView::OnSetFocus(CWnd* pOldWnd)
{
}

void CTetrisView::OnKillFocus(CWnd* pNewWnd)
{
}

void CTetrisView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CTetrisView::OnTimer(UINT_PTR nIDEvent)
{
}

void CTetrisView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	m_iColorStatus = lHint;
	if(pHint != NULL)
	{
		CRect rcArea = *(CRect*)pHint;
		rcArea.left *= g_iColWidth;
		rcArea.right *= g_iColWidth;
		rcArea.top *= g_iRowHeight;
		rcArea.bottom *= g_iRowHeight;
		InvalidateRect(&rcArea);
	}
	else {
		Invalidate();
	}
	UpdateWindow();
}

void CTetrisView::DrawGrid(CDC* pDC)
{
	const ColorGrid* pGrid = m_pTetrisDoc->GetGrid();
	for (int iRow = 0; iRow < ROWS; iRow++)
	{
		for (int iCol = 0; iCol < COLS; iCol++)
		{
			COLORREF rfColor = pGrid->Index(iRow, iCol);
			if (rfColor != WHITE) {
				CBrush brush((m_iColorStatus == COLOR) ? rfColor : GrayScale(rfColor));
				CBrush* pOldBursh = pDC->SelectObject(&brush);
				DrawSquare(iRow, iCol, pDC);
				pDC->SelectObject(&pOldBursh);
			}
		}
	}
}

void CTetrisView::DrawScoreAndScoreList(CDC* pDC)
{

}

void CTetrisView::DrawActiveAndNextFigure(CDC* pDC)
{
}


// CTetrisView diagnostics

#ifdef _DEBUG
void CTetrisView::AssertValid() const
{
	CView::AssertValid();
}

void CTetrisView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTetrisDoc* CTetrisView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTetrisDoc)));
	return (CTetrisDoc*)m_pDocument;
}
#endif //_DEBUG


// CTetrisView message handlers

COLORREF GrayScale(COLORREF color)
{
	return COLORREF();
}
