
// TetrisView.h : interface of the CTetrisView class
//

#pragma once

const int TIMER_ID = 0;
enum {COLOR = 0, GRAY = 1};

class CTetrisDoc;
COLORREF GrayScale(COLORREF color);

class CTetrisView : public CView
{
protected: // create from serialization only
	CTetrisView() noexcept;
	DECLARE_DYNCREATE(CTetrisView)

// Attributes
public:
	CTetrisDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CTetrisView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

private:
	void DrawGrid(CDC* pDC);
	void DrawScoreAndScoreList(CDC* pDC);
	void DrawActiveAndNextFigure(CDC* pDC);

private:
	CTetrisDoc* m_pTetrisDoc;
	int m_iColorStatus;

};

#ifndef _DEBUG  // debug version in TetrisView.cpp
inline CTetrisDoc* CTetrisView::GetDocument() const
   { return reinterpret_cast<CTetrisDoc*>(m_pDocument); }
#endif

