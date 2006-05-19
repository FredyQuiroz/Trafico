#include "StdAfx.h"
#include "Carretera.h"
# include "nodo.h"

CCarretera::CCarretera(int x, int y,int largo, bool ascendente, bool horizontal)
{
	m_bHorizontal=horizontal;
	m_bAscendente= ascendente;

	m_pRect.bottom= m_pRect.top=y;
	m_pRect.right= m_pRect.left=x;
	if( m_bHorizontal) {
		m_pRect.bottom+= ANCHO_CARRETERA;
		m_pRect.right+= largo;
	} else {
		m_pRect.right+= ANCHO_CARRETERA;
		m_pRect.bottom+= largo;
	}
}

CCarretera::~CCarretera(void)
{
}

void CCarretera::BuildNodos(CRuta *ruta,bool especial/*=false*/) {

	int direccion=0;
	CNodo *nodo;
	if( m_bHorizontal) {
		direccion= m_bAscendente ? DIRECCION_DERECHA : DIRECCION_IZQUIERDA;
		int y= m_pRect.top+(ANCHO_CARRETERA/2);
		for( int i=m_pRect.left; i<m_pRect.right; i+=RUTA_PRESICION) {
			nodo= ruta->AddNodo(i,y,direccion);
			if( especial) {
				if(m_bAscendente) {
					if(nodo->GetDireccion()&DIRECCION_ARRIBA)
						nodo->SetDireccion(direccion);
				} else if(nodo->GetDireccion()&DIRECCION_ABAJO)
					nodo->SetDireccion(direccion);
			}
		}
	} else {
		direccion= m_bAscendente ? DIRECCION_ABAJO : DIRECCION_ARRIBA;
		int x= m_pRect.left+(ANCHO_CARRETERA/2);
		for( int i=m_pRect.top; i<m_pRect.bottom; i+=RUTA_PRESICION) {
			nodo=ruta->AddNodo(x,i,direccion);
			if( especial) {
				if(m_bAscendente) {
					if(nodo->GetDireccion()&DIRECCION_DERECHA)
						nodo->SetDireccion(direccion);
				} else if(nodo->GetDireccion()&DIRECCION_IZQUIERDA)
					nodo->SetDireccion(direccion);
			}
		}
	}
}

void CCarretera::Draw(CDC *pDC) {

	CBrush brush(RGB(0,0,0));
	CBrush *old= pDC->SelectObject(&brush);

	pDC->Rectangle(m_pRect);
	pDC->SelectObject(old);

	/*if( m_bHorizontal) {
		pDC->TextOut(m_pRect.left, m_pRect.top, m_bAscendente ? ">" : "<");
		pDC->TextOut(m_pRect.right, m_pRect.top, m_bAscendente ? ">" : "<");
	} else {
		pDC->TextOut(m_pRect.left, m_pRect.top, m_bAscendente ? "B" : "A");
		pDC->TextOut(m_pRect.left, m_pRect.bottom, m_bAscendente ? "B" : "A");
	}*/
}
