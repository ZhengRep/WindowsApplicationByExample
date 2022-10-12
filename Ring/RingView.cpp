
// RingView.cpp : implementation of the CRingView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Ring.h"
#endif

#include "RingDoc.h"
#include "RingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRingView

IMPLEMENT_DYNCREATE(CRingView, CScrollView)

BEGIN_MESSAGE_MAP(CRingView, CScrollView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CRingView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CRingView construction/destruction

CRingView::CRingView() noexcept
{
	// TODO: add construction code here

}

CRingView::~CRingView()
{
}

BOOL CRingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// CRingView drawing

void CRingView::OnDraw(CDC* pDC/*pDC*/)
{
	CRingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	PointArray& pointArray = pDoc->GetPointArray();
	ColorArray& colorArray = pDoc->GetColorArray();

	int iSize = (int)pointArray.GetSize();
	for (int i = 0; i < iSize; i++)
	{
		CPoint point = pointArray[i];
		COLORREF color = colorArray[i];

		CPen pen(PS_SOLID, 0, BLACK);
		CBrush brush(color);

		pDC->Ellipse(point.x - 50, point.y - 50, point.x + 50, point.y + 50);

		CPen* pOldPen = pDC->SelectObject(&pen);
		CBrush* pOldBrush = pDC->SelectObject(&brush);
	}
}

void CRingView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CRingView printing


void CRingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CRingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CRingView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CRingView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

void CRingView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->MouseDown(point);

	CScrollView::OnLButtonDown(nFlags, point);
}


// CRingView diagnostics

#ifdef _DEBUG
void CRingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CRingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CRingDoc* CRingView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRingDoc)));
	return (CRingDoc*)m_pDocument;
}
#endif //_DEBUG


// CRingView message handlers
