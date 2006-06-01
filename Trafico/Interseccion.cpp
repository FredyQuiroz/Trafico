#include "StdAfx.h"
#include "Interseccion.h"

# define ANCHO_LINEA_I	2

CInterseccion::CInterseccion(void)
{
	m_dwBorderColor= m_dwColorLinea= RGB(255,255,255);
	m_nBordes= ANCHO_LINEA_I;
}

CInterseccion::~CInterseccion(void)
{
}

void CInterseccion::Draw(CDC *pDC) {

	CRectangulo::Draw(pDC);

	CPen pen(PS_SOLID, ANCHO_LINEA_I, m_dwColorLinea);
	CPen *old= (CPen *)pDC->SelectObject(&pen);
	pDC->MoveTo(m_pRect.TopLeft());
	pDC->LineTo(m_pRect.BottomRight());
	pDC->MoveTo(m_pRect.right, m_pRect.top);
	pDC->LineTo(m_pRect.left, m_pRect.bottom);

	// cebras verticales
	pen.DeleteObject();
	pen.CreatePen(PS_SOLID, m_pRect.Width()/20,m_dwColorLinea);
	pDC->SelectObject(&pen);
	CPoint punto;
	for( int i= m_pRect.left; i<m_pRect.right; i+=10) {
		punto.x=i;
		punto.y=m_pRect.top-5;
		pDC->MoveTo(punto);
		punto.y-=ANCHO_CEBRA-10;
		pDC->LineTo(punto);

		punto.y= m_pRect.bottom+5;
		pDC->MoveTo(punto);
		punto.y+=ANCHO_CEBRA-10;
		pDC->LineTo(punto);
	}

	// cebras horizontales
	for( int i= m_pRect.top; i<m_pRect.bottom; i+=10) {
		
		punto.y=i;
		punto.x=m_pRect.left-5;
		pDC->MoveTo(punto);
		punto.x-=ANCHO_CEBRA-10;
		pDC->LineTo(punto);

		punto.x= m_pRect.right+5;
		pDC->MoveTo(punto);
		punto.x+=ANCHO_CEBRA-10;
		pDC->LineTo(punto);
	}
	// linea de separacion de las cebras
	// linea superior
	punto.x= m_pRect.left;
	punto.y=m_pRect.top-ANCHO_CEBRA;
	pDC->MoveTo(punto);
	punto.x= m_pRect.right;
	pDC->LineTo(punto);
	// linea inferior
	punto.x= m_pRect.left;
	punto.y=m_pRect.bottom+ANCHO_CEBRA;
	pDC->MoveTo(punto);
	punto.x= m_pRect.right;
	pDC->LineTo(punto);
	// linea derecha
	punto.x= m_pRect.right+ANCHO_CEBRA;
	punto.y=m_pRect.top;
	pDC->MoveTo(punto);
	punto.y= m_pRect.bottom;
	pDC->LineTo(punto);
	// linea izquierda
	punto.x= m_pRect.left-ANCHO_CEBRA;
	punto.y=m_pRect.top;
	pDC->MoveTo(punto);
	punto.y= m_pRect.bottom;
	pDC->LineTo(punto);

	pDC->SelectObject(old);

}