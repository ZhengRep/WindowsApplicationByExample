#pragma once
class Caret
{
public:
	Caret();
	void SetAndShowCaret(const CRect rcCaret);
	void HideCaret();
	void OnSetFocus(CView* pView);
	void OnKillFocus();
	CView* GetView() const { return m_pFocusView; };

private:
	CView* m_pFocusView;
	BOOL m_bVisible;
	CRect m_rcCaret;
};

