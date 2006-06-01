#include "StdAfx.h"
#include "Automovil.h"

CAutomovil::CAutomovil(bool hor, bool asc)
{
	m_bAscendente= asc;
	m_bHorizontal=hor;
	int  r = (((double) rand() / (double) RAND_MAX) * 256);
	int  g = (((double) rand() / (double) RAND_MAX) * 256);
	int  b = (((double) rand() / (double) RAND_MAX) * 256);
	m_dwColor= RGB(r,g,b);
	m_nPasos= 5;
	m_pSemaforo=NULL;
}

CAutomovil::~CAutomovil(void)
{
}

CSemaforo *CAutomovil::SetSemaforo(CSemaforo *sem) {

	CSemaforo *old= m_pSemaforo;
	m_pSemaforo= sem;
	return old;
}

void CAutomovil::Draw(CDC *pDC) {
	
	CRectangulo::Draw(pDC);
}

CRect CAutomovil::MakeStep() {

	CRect rect=m_pRect;
	int step= m_nPasos;
	if( !m_bAscendente)
		step*=-1;
	if( m_bHorizontal) {
		rect.MoveToX(rect.left+step);
	} else {
		rect.MoveToY(rect.top+step);
	}
	return rect;
}

bool CAutomovil::IsValidRect(CRect rect) {
	
	CPoint point= m_pRect.CenterPoint();
	if( m_bHorizontal) {
		if( m_bAscendente) {
			if( point.x>rect.right)
				return false;
		} else {
			if( point.x<rect.left)
				return false;
		}
	} else {
		if( m_bAscendente) {
			if( point.y>rect.bottom)
				return false;
		} else {
			if( point.y<rect.top)
				return false;
		}
	}
	return true;
}