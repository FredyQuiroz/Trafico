#include "StdAfx.h"
#include "Carretera.h"
# define ANCHO_LINEA	2
# define LARGO_LINEA	20

CCarretera::CCarretera(void)
{
	m_dwColorLinea= RGB(255,255,255);
}

CCarretera::~CCarretera(void)
{
}

void CCarretera::Draw(CDC *pDC) {

	CRectangulo::Draw(pDC);

	CPen pen(PS_SOLID, ANCHO_LINEA, m_dwColorLinea);
	CPen *old= (CPen *)pDC->SelectObject(&pen);
	bool draw=false;
	CPoint	punto;
	punto= m_pRect.CenterPoint();

	if( m_pRect.Width()> m_pRect.Height()) { // horizontal
		for( int i=m_pRect.left; i<m_pRect.right; i+=LARGO_LINEA) {
			punto.x= i;
			if( draw) 
				pDC->LineTo(punto);
			else 
				pDC->MoveTo(punto);
			draw=!draw;
		}
	} else { // vertical
		for( int i=m_pRect.top; i<m_pRect.bottom; i+=LARGO_LINEA) {
			punto.y= i;
			if( draw) 
				pDC->LineTo(punto);
			else 
				pDC->MoveTo(punto);
			draw=!draw;
		}
	}
	pDC->SelectObject(old);
}
