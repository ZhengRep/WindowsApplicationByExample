
// TetrisDoc.h : interface of the CTetrisDoc class
//


#pragma once

typedef CList<int> IntList;
const int FIGURE_ARRAY_SIZE = 7;

class CTetrisDoc : public CDocument
{
protected: // create from serialization only
	CTetrisDoc() noexcept;
	DECLARE_DYNCREATE(CTetrisDoc)

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
	virtual ~CTetrisDoc();
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
	void SaveScoreList();

	int GetScore() const { return m_iScore; };

	const IntList* GetScoreList() { return &m_scoreList; };
	const ColorGrid* GetGrid() { return &m_colorGrid; };
	const Figure& GetActiveFigure() const { return m_activeFigure; };
	const Figure& GetNextFigure() const { return m_nextFigure; };

public:
	void LeftArrowKey();
	void RightArrowKey();
	void UpArrowKey();
	void DownArrowKey();
	BOOL Timer();
	void SpaceKey();

private:
	void GameOver();
	BOOL NewGame();
	int AddScoreToList();
	void DeleteFullRows();
	BOOL isRowFull(int iRow);
	void FlashRow(int iFlashRow);
	void DeleteRow(int iDeleteRow);

private:
	int m_iScore;
	IntList m_scoreList;
	ColorGrid m_colorGrid;
	Figure m_activeFigure, m_nextFigure;
	const CRect NEXT_AREA, SCORE_AREA;
	static Figure m_figureArray[FIGURE_ARRAY_SIZE];
};
