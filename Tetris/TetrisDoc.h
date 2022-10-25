
// TetrisDoc.h : interface of the CTetrisDoc class
//


#pragma once
#include "Figure.h"
#include "TetrisView.h"

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
	void LoadScoreList();

	int GetScore() const { return m_iScore; };

	const IntList* GetScoreList() { return m_scoreList; };
	const Figure& GetActiveFigure() const { return m_activeFigure; };
	const Figure& GetNextFigure() const { return m_nextFigure; };
	const ColorGrid* GetGrid() const { return &m_colorGrid; };

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
	IntList* m_scoreList; //record top 10 score
	int m_iScore;
	ColorGrid m_colorGrid;
	Figure m_activeFigure, m_nextFigure;
	const CRect NEXT_AREA, SCORE_AREA;
	static Figure m_figureArray[FIGURE_ARRAY_SIZE];
};
