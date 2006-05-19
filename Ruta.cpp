#include "StdAfx.h"
#include "Ruta.h"
# include "nodo.h"

CRuta::CRuta(void)
{
	m_nTamano=0;
	m_nMinX=0xfffffff;
	m_nMinY=0xfffffff;
	m_nMaxX=0;
	m_nMaxY=0;
}

CRuta::~CRuta(void)
{
	CNodo *nodo;
	for( int i=0; i<m_pNodos.GetCount(); i++) {
		nodo= (CNodo *)m_pNodos[i];
		delete nodo;
	}
}

CNodo *CRuta::AddNodo(int x, int y, int direccion) {
	
	CNodo *nodo;
	for( int i=0; i<m_pNodos.GetCount(); i++) {
		nodo= (CNodo *)m_pNodos[i];
		if( nodo->m_pPunto.x==x && nodo->m_pPunto.y==y) {
			nodo->SetDireccion(direccion| nodo->GetDireccion());
			return nodo;
		}
	}
	if(x>m_nMaxX)
		m_nMaxX=x;
	if(y>m_nMaxY)
		m_nMaxY=y;
	if(x<m_nMinX)
		m_nMinX=x;
	if(y<m_nMinY)
		m_nMinY=y;
	nodo=new CNodo(direccion, x,y);
	m_pNodos.Add(nodo);
	m_nTamano++;
	return nodo;
}

int CRuta::GetIndex(int x, int y) {

	CNodo *info;
	for( int i=0; i<m_pNodos.GetCount(); i++) {
		info= (CNodo *)m_pNodos[i];
		if( info->m_pPunto.x==x && info->m_pPunto.y==y)
			return i;
	}
	return -1;
}

CNodo *CRuta::GetNodo(CPoint punto) {

	CNodo *info;
	for( int i=0; i<m_pNodos.GetCount(); i++) {
		info= (CNodo *)m_pNodos[i];
		if( info->m_pPunto==punto)
			return info;
	}
	return NULL;
}

CNodo *CRuta::GetNodo(int x, int y) {
	
	CNodo *info;
	for( int i=0; i<m_pNodos.GetCount(); i++) {
		info= (CNodo *)m_pNodos[i];
		if( info->m_pPunto.x==x && info->m_pPunto.y==y)
			return info;
	}
	return NULL;
}

int CRuta::GetIndex(CPoint punto) {

	CNodo *info;
	for( int i=0; i<m_pNodos.GetCount(); i++) {
		info= (CNodo *)m_pNodos[i];
		if( info->m_pPunto==punto)
			return i;
	}
	return -1;
}

void CRuta::Draw(CDC *pDC) {

	pDC->SetTextColor(RGB(255,0,0));
	pDC->SetBkMode(TRANSPARENT);

	CNodo *nodo;
	CString temp;
	for( int i=0; i<m_pNodos.GetCount(); i++) {
		nodo= (CNodo *)m_pNodos[i];
		temp=".";
		pDC->TextOut(nodo->m_pPunto.x, nodo->m_pPunto.y, temp);
	}
}
CNodo *CRuta::GetNodo(int index) {
	if( m_nTamano<index)
		return NULL;
	return (CNodo *)m_pNodos[index];
}

CPoint CRuta::GetPunto(int index) {

	if( m_nTamano<index)
		return NULL;
	return ((CNodo *)m_pNodos[index])->m_pPunto;
}

CRect CRuta::GetLimites() {

	return CRect(m_nMinX, m_nMinY, m_nMaxX, m_nMaxY);
}