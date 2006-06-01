#include "StdAfx.h"
#include "StartPoint.h"

CStartPoint::CStartPoint(int x, int y, bool hor, bool asc)
{
	m_nX=x;
	m_nY=y;
	m_bHorizontal=hor;
	m_bAscendente=asc;
}

CStartPoint::~CStartPoint(void)
{
}

CAutomovil *CStartPoint::GetCar() {
	CAutomovil *autom= new CAutomovil(m_bHorizontal, m_bAscendente);
	CRect rect(m_nX, m_nY, m_nX+ANCHO_CARRO, m_nY+ANCHO_CARRO);
	if( m_bHorizontal)
		rect.right= rect.left+ALTO_CARRO;
	else rect.bottom= rect.top+ALTO_CARRO;
	autom->SetRect(rect);
	return autom;
}