#include "StdAfx.h"
#include "SemaforoInter.h"
# include "interseccion.h"

# define SEPARADOR_ESQUINA	5

CSemaforoInter::CSemaforoInter(CRect interseccion,int rojov, int rojoh)
{
	m_pRect= interseccion;
	CRect sem;
	m_pSemaforos[0].SetPos(CSemaforo::pos_horder);
	sem.right= sem.left= interseccion.right+SEPARADOR_ESQUINA;
	sem.right+= ALTO_SEMAFO; 
	sem.bottom= sem.top= interseccion.top-SEPARADOR_ESQUINA;
	sem.top-=ANCHO_SEMAFORO;
	m_pSemaforos[0].SetRect(sem);
	m_pSemaforos[0].SetTiempo(rojoh, rojov);
	m_pSemaforos[0].SetColor(CSemaforo::verde);
	sem= interseccion;
	sem.left= sem.right;
	sem.right+=ANCHO_CEBRA;
	sem.bottom-= sem.Height()/2;
	m_pSemaforos[0].SetCebra(sem);

	m_pSemaforos[1].SetPos(CSemaforo::pos_horizq);
	sem.right= sem.left= interseccion.left-SEPARADOR_ESQUINA;
	sem.left-= ALTO_SEMAFO; 
	sem.bottom= sem.top= interseccion.bottom+SEPARADOR_ESQUINA;
	sem.bottom+=ANCHO_SEMAFORO;
	m_pSemaforos[1].SetRect(sem);
	m_pSemaforos[1].SetTiempo(rojoh, rojov);
	m_pSemaforos[1].SetColor(CSemaforo::verde);
	sem= interseccion;
	sem.right= sem.left;
	sem.left-=ANCHO_CEBRA;
	sem.top+= sem.Height()/2;
	m_pSemaforos[1].SetCebra(sem);

	m_pSemaforos[2].SetPos(CSemaforo::pos_verder);
	sem.right= sem.left= interseccion.right+SEPARADOR_ESQUINA;
	sem.right+= ANCHO_SEMAFORO; 
	sem.bottom= sem.top= interseccion.bottom+SEPARADOR_ESQUINA;
	sem.bottom+=ALTO_SEMAFO;
	m_pSemaforos[2].SetRect(sem);
	m_pSemaforos[2].SetTiempo(rojov, rojoh);
	m_pSemaforos[2].SetColor(CSemaforo::rojo);
	sem= interseccion;
	sem.top=sem.bottom;
	sem.bottom+=ANCHO_CEBRA;
	sem.left+= sem.Width()/2;
	m_pSemaforos[2].SetCebra(sem);

	m_pSemaforos[3].SetPos(CSemaforo::pos_verizq);
	sem.right= sem.left= interseccion.left-SEPARADOR_ESQUINA;
	sem.left-= ANCHO_SEMAFORO;
	sem.bottom= sem.top= interseccion.top-SEPARADOR_ESQUINA;
	sem.top-=ALTO_SEMAFO;
	m_pSemaforos[3].SetRect(sem);
	m_pSemaforos[3].SetTiempo(rojov, rojoh);
	m_pSemaforos[3].SetColor(CSemaforo::rojo);
	sem= interseccion;
	sem.bottom=sem.top;
	sem.top-=ANCHO_CEBRA;
	sem.right-= sem.Width()/2;
	m_pSemaforos[3].SetCebra(sem);
}

CSemaforoInter::~CSemaforoInter(void)
{
}

CRect CSemaforoInter::GetInterseccion() {
	return m_pRect;
}

int CSemaforoInter::GetTiempoAmarillo() {
	return m_pSemaforos[0].GetTiempoAmarillo();
}

int CSemaforoInter::GetTiempoRojoV() {
	return m_pSemaforos[0].GetTiempoVerde();
}

int CSemaforoInter::GetTiempoRojoH() {
	return m_pSemaforos[0].GetTiempoRojo();
}

void CSemaforoInter::SetTiempo(int rojov, int rojoh, int amarillo) {
	m_pSemaforos[0].SetTiempo(rojoh, rojov);
	m_pSemaforos[1].SetTiempo(rojoh, rojov);
	m_pSemaforos[2].SetTiempo(rojov, rojoh);
	m_pSemaforos[3].SetTiempo(rojov, rojoh);
	for( int i=0; i<4; i++) {
		m_pSemaforos[i].SetTiempoAmarillo(amarillo);
	}
}

bool CSemaforoInter::ValidateStep(CRect paso,CAutomovil *autom) {

	for( int i=0; i<4; i++) {

		CRect rect= m_pSemaforos[i].GetCebra();
		if( rect.IntersectRect(rect, paso)) {
			if( autom->SetSemaforo(&m_pSemaforos[i])!=&m_pSemaforos[i]) 
				m_pSemaforos[i].AddAuto();
			if( m_pSemaforos[i].GetColor()!=CSemaforo::verde) {
				CPoint car= paso.CenterPoint();
				switch(m_pSemaforos[i].GetPos()) {
					case CSemaforo::pos_horder:
						if( car.x>rect.right)
							return false;
						break;
					case CSemaforo::pos_horizq:
						if( car.x<rect.left)
							return false;
						break;
					case CSemaforo::pos_verder:
						if( car.y>rect.bottom)
							return false;
						break;
					case CSemaforo::pos_verizq:
						if( car.y<rect.top)
							return false;
						break;
				}
			}
		}
	}
	return true;
}

void CSemaforoInter::Draw(CDC *pDC) {
	
	int total=0;
	for( int i=0; i<4; i++) {
		m_pSemaforos[i].Draw(pDC);
		total+=m_pSemaforos[i].GetAutomoviles();
	}
	CString texto;
	texto.Format("%d Automoviles", total);
	pDC->TextOut(m_pRect.right+10, m_pRect.bottom+50, texto);
	CTimeSpan span(0,0,0,abs(m_pSemaforos[0].GetTiempoActual()));
	texto.Format("%s para cambio", span.Format("%M:%S"));
	pDC->TextOut(m_pRect.right+10, m_pRect.bottom+70, texto);
}

void CSemaforoInter::MakeStep() {
	for( int i=0; i<4; i++) {
		m_pSemaforos[i].MakeStep();
	}
}
