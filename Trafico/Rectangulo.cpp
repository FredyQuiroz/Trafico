#include "StdAfx.h"
#include "Rectangulo.h"

CRectangulo::CRectangulo(void)
{
	m_dwColor=0;
	m_nBordes=0;
}

CRectangulo::~CRectangulo(void)
{
}

CRect CRectangulo::GetRect() {
	return m_pRect;
}

void CRectangulo::SetRect(CRect rect) {
	m_pRect= rect;
}

void CRectangulo::SetBkColor(COLORREF color) {
	m_dwColor=0;
}

void CRectangulo::Draw(CDC *pDC) {

	CBrush brush(m_dwColor);
	CPen pen,*oldpen;
	CBrush *oldbrush= pDC->SelectObject(&brush);
	if(m_nBordes) {
		pen.CreatePen(PS_SOLID, m_nBordes, m_dwBorderColor);
		oldpen= (CPen *)pDC->SelectObject(&pen);
	} else {
		oldpen= (CPen *) pDC->SelectStockObject( NULL_PEN );
	}
	pDC->Rectangle(m_pRect);
	pDC->SelectObject(oldbrush);
	pDC->SelectObject(oldpen);
}
