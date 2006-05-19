#include "StdAfx.h"
#include "Semaforo.h"

CSemaforo::CSemaforo(CRect vS, CRect vI, CRect hD,CRect hI, int vertical, int horizontal)
{
	m_pRectH1=hD;
	m_pRectH2= hI;
	m_pRectV1= vS;
	m_pRectV2= vI;
	m_nVertical= vertical+1;
	m_nHorizontal= horizontal;
	m_nEstado=0;
}

CSemaforo::CSemaforo(CPoint vS, CPoint vI, CPoint hD,CPoint hI, int vertical, int horizontal) {

	m_pPointV1=vS;
	m_pPointV2=vI;
	m_pPointH1=hD;
	m_pPointH2=hI;

	vS.x-=2*SEMAFORO_SIZE;
	vI.x+=2*SEMAFORO_SIZE;
	hD.y-=2*SEMAFORO_SIZE;
	hI.y+=2*SEMAFORO_SIZE;

	m_pRectV1= CRect(vS,CSize(SEMAFORO_SIZE,SEMAFORO_SIZE));
	m_pRectV2= CRect(vI,CSize(SEMAFORO_SIZE,SEMAFORO_SIZE));
	m_pRectH1= CRect(hD,CSize(SEMAFORO_SIZE,SEMAFORO_SIZE));
	m_pRectH2= CRect(hI,CSize(SEMAFORO_SIZE,SEMAFORO_SIZE));

	m_nVertical= vertical+1;
	m_nHorizontal= horizontal;
	m_nEstado=0;

	m_pNodoV1=NULL;
	m_pNodoV2=NULL;
	m_pNodoH1=NULL;
	m_pNodoH2=NULL;
}

CSemaforo::~CSemaforo(void)
{
}

void CSemaforo::Draw(CDC *pDC) {
	
	CBrush brushr(RGB(255,0,0));
	CBrush brushv(RGB(0,255,0));
	CBrush *old=pDC->SelectObject(&brushr);
	pDC->Ellipse(m_nEstado>0 ? m_pRectH1 : m_pRectV1);
	pDC->Ellipse(m_nEstado>0 ? m_pRectH2 : m_pRectV2);
	pDC->SelectObject(&brushv);
	pDC->Ellipse(m_nEstado>0 ? m_pRectV1 : m_pRectH1);
	pDC->Ellipse(m_nEstado>0 ? m_pRectV2 : m_pRectH2);
	pDC->SelectObject(old);
}

bool CSemaforo::NextStep(CRuta *ruta) {
	
	if(!m_pNodoV1)
		m_pNodoV1= ruta->GetNodo(m_pPointV1);
	if(!m_pNodoV2)
		m_pNodoV2= ruta->GetNodo(m_pPointV2);
	if(!m_pNodoH1)
		m_pNodoH1= ruta->GetNodo(m_pPointH1);
	if(!m_pNodoH2)
		m_pNodoH2= ruta->GetNodo(m_pPointH2);
	
	if(m_nEstado>0) {
		m_nEstado++;
		if( m_nEstado==m_nVertical) 
			m_nEstado=0;
	} else {
		m_nEstado--;
		if( m_nEstado==-m_nHorizontal)
			m_nEstado=1;
	}
	if(m_pNodoV1)
		m_pNodoV1->SetRed(m_nEstado<=0);
	if(m_pNodoV2)
		m_pNodoV2->SetRed(m_nEstado<=0);
	if(m_pNodoH1)
		m_pNodoH1->SetRed(m_nEstado>0);
	if(m_pNodoH2)
		m_pNodoH2->SetRed(m_nEstado>0);
	return true;
}