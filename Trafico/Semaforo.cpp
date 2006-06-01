#include "StdAfx.h"
#include "Semaforo.h"

# define TIEMPO_AMARILLO	5

CSemaforo::CSemaforo(void)
{
	m_nEstado= 0;
	m_nTiempoRojo=0;
	m_nTiempoVerde=0;
	m_nTiempoActual=0;
	m_nPosicion=0;
	m_nAutos=0;
	m_nTiempoAmarillo= TIEMPO_AMARILLO;
}

CSemaforo::~CSemaforo(void)
{
}

void CSemaforo::SetTiempoAmarillo(int tiempo) {
	m_nTiempoAmarillo= tiempo;
}

void CSemaforo::SetTiempo(int rojo,int verde) {
	
	m_nTiempoRojo= rojo;
	m_nTiempoVerde= verde;
}

CRect CSemaforo::GetCebra() {
	return m_pCebra;
}

void CSemaforo::SetCebra(CRect cebra) {
	m_pCebra= cebra;
}

int  CSemaforo::GetAutomoviles() {

	return m_nAutos;
}

int  CSemaforo::GetTiempoActual() {
	
	return m_nTiempoActual;
}

void CSemaforo::Draw(CDC *pDC) {

	CRectangulo::Draw(pDC);
	int colorr= RGB(255, 0,0);
	int colorv= RGB(0,255,0);
	int colora= RGB(255,255,0);
	switch(m_nEstado) {
		case CSemaforo::rojoamarillo:
			colorv=RGB(0,85,0);
			break;
		case CSemaforo::rojo:
			colora= RGB(85,85,0);
			colorv=RGB(0,85,0);
			break;
		case CSemaforo::verde:
			colora= RGB(85,85,0);
			colorr= RGB(85, 0,0);
			break;
		case CSemaforo::amarillo:
			colorr= RGB(85, 0,0);
			colorv=RGB(0,85,0);
			break;
	}
	CBrush brushr(colorr);
	CBrush brusha(colora);
	CBrush brushv(colorv);
	CRect red, green, yellow;
	int ancho=0;
	red= m_pRect;
	green= m_pRect;
	yellow= m_pRect;
	CString texto,tiempo;

	texto.Format("%d A", m_nAutos);

	switch(m_nPosicion) {
		case CSemaforo::pos_horder:
			ancho= m_pRect.Width()/3;
			red.right=red.left+ancho;
			yellow.right=yellow.left= red.right;
			yellow.right+=ancho;
			green.left=green.right= yellow.right;
			green.right+=ancho;
			pDC->TextOut(m_pRect.left,m_pRect.top-20,texto);
			break;
		case CSemaforo::pos_horizq:
			ancho= m_pRect.Width()/3;
			green.right=green.left+ancho;
			yellow.right=yellow.left= green.right;
			yellow.right+=ancho;
			red.left=red.right= yellow.right;
			red.right+=ancho;
			pDC->TextOut(m_pRect.left,m_pRect.bottom,texto);
			break;
		case CSemaforo::pos_verder:
			ancho= m_pRect.Height()/3;
			red.bottom=red.top+ancho;
			yellow.bottom=yellow.top= red.bottom;
			yellow.bottom+=ancho;
			green.top=green.bottom= yellow.bottom;
			green.bottom+=ancho;
			pDC->TextOut(m_pRect.right,m_pRect.top,texto);
			break;
		case CSemaforo::pos_verizq:
			ancho= m_pRect.Height()/3;
			green.bottom=green.top+ancho;
			yellow.bottom=yellow.top= green.bottom;
			yellow.bottom+=ancho;
			red.top=red.bottom= yellow.bottom;
			red.bottom+=ancho;
			pDC->TextOut(m_pRect.left-30,m_pRect.top,texto);
			break;
	}
	red.DeflateRect(1,1);
	CBrush *oldbrush= pDC->SelectObject(&brushr);
	pDC->Ellipse(red);
	yellow.DeflateRect(1,1);
	pDC->SelectObject(&brusha);
	pDC->Ellipse(yellow);
	green.DeflateRect(1,1);
	pDC->SelectObject(&brushv);
	pDC->Ellipse(green);

	pDC->SelectObject(oldbrush);
}

void CSemaforo::AddAuto(int autos) {
	m_nAutos+=autos;
}

void CSemaforo::SetColor(int color) {
	m_nEstado= color;
	switch( m_nEstado) {
		case CSemaforo::rojo:
			m_nTiempoActual=-m_nTiempoRojo;
			break;
		case CSemaforo::verde:
			m_nTiempoActual=m_nTiempoVerde;
			break;
		default:
			m_nTiempoActual= 0;
			break;
	}
}

int	 CSemaforo::GetPos() {
	return m_nPosicion;
}

void CSemaforo::SetPos(int pos) {
	
	m_nPosicion= pos;
}

int CSemaforo::GetColor() {
	
	return m_nEstado;
}

int CSemaforo::GetTiempoAmarillo() {

	return m_nTiempoAmarillo;
}
int CSemaforo::GetTiempoRojo() {

	return m_nTiempoRojo;
}
int CSemaforo::GetTiempoVerde() {

	return m_nTiempoVerde;
}

void CSemaforo::MakeStep() {

	switch(m_nEstado) {
		case CSemaforo::rojo:
			m_nTiempoActual++;
			if( m_nTiempoActual==0) {
				m_nEstado=CSemaforo::rojoamarillo;
			}
			break;
		case CSemaforo::verde:
			m_nTiempoActual--;
			if( m_nTiempoActual==0) {
				m_nEstado=CSemaforo::amarillo;
			}
			break;
		case CSemaforo::amarillo:
			if( m_nTiempoActual<m_nTiempoAmarillo) {
				m_nTiempoActual++;
			} else {
				m_nTiempoActual=-m_nTiempoRojo;
				m_nEstado= CSemaforo::rojo;
			}
			break;
		case CSemaforo::rojoamarillo:
			if( m_nTiempoActual<m_nTiempoAmarillo) {
				m_nTiempoActual++;
			} else {
				m_nTiempoActual=m_nTiempoVerde;
				m_nEstado= CSemaforo::verde;
			}
			break;
	}
}
