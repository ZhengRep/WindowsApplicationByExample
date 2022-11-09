#include "pch.h"
#include "FigureFileManager.h"
#include "ArrowFigure.h"
#include "LineFigure.h"

FigureFileManager::FigureFileManager(Figure* pFigure)
{

}

int FigureFileManager::GetId() const
{
	if (dynamic_cast<ArrowFigure*>(m_pFigure) != NULL) {
		return ARROW;
	}
	else if (dynamic_cast<LineFigure*>(m_pFigure) != NULL) {
		return LINE;
	}
	else {
		return 0;
	}
}

void FigureFileManager::CreateFigure(int iId)
{
	switch (iId)
	{
	case LINE:
		m_pFigure = new LineFigure();
		break;
	default:

	}
}

void FigureFileManager::Serialize(CArchive& archive)
{
	CObject::Serialize(archive);
	if (archive.IsStoring()) {
		archive << GetId();
	}
	if (archive.IsLoading()) {
		int iId;
		archive >> iId;
		CreateFigure(iId);
	}
}
