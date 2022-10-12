
// RingDoc.h : interface of the CRingDoc class
//


#pragma once

#include<afxtempl.h>
typedef CArray<CPoint> PointArray;
typedef CArray<COLORREF> ColorArray;

static const COLORREF WHITE = RGB(255, 255, 255);
static const COLORREF GREY = RGB(128, 128, 128);
static const COLORREF BLACK = RGB(0, 0, 0);

class CRingDoc : public CDocument
{
protected: // create from serialization only
	CRingDoc() noexcept;
	DECLARE_DYNCREATE(CRingDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CRingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
	
public:
	void MouseDown(CPoint point);
	PointArray& GetPointArray() { return m_pointArray; };
	ColorArray& GetColorArray() { return m_colorArray; };


private:
	PointArray m_pointArray;
	ColorArray m_colorArray;
};
