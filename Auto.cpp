#include "StdAfx.h"
#include "Auto.h"
# include "nodo.h"

CAuto::CAuto(int x, int y,CPoint destino)
{
	m_pRect= CRect(x-(AUTO_ANCHO/2), y-(AUTO_ALTO/2), x+(AUTO_ANCHO/2), y+(AUTO_ALTO/2));
	m_pDestino= destino;
	m_nLlegada=0;
	m_nOldDireccion=0;
	m_bHorizontal=true;
	m_nIntentos=0;
	m_bShowDestino= AfxGetApp()->GetProfileInt("control", "showd", 1)==1;
}

CAuto::~CAuto(void)
{
}

CRect CAuto::GetRect() {
	return m_pRect;
}

bool CAuto::SetPoint(CPoint *punto) {
	
	if( *punto==m_pRect.CenterPoint())
		return false;
	m_pRect.bottom= m_pRect.top= punto->y-(AUTO_ALTO/2);
	m_pRect.bottom+= AUTO_ALTO;
	m_pRect.right= m_pRect.left= punto->x-(AUTO_ANCHO/2);
	m_pRect.right+= AUTO_ANCHO;
	return true;
}

void CAuto::Draw(CDC *pDC) {

	CBrush brush(RGB(0,0,255));
	CBrush *old= pDC->SelectObject(&brush);
	pDC->Rectangle(m_pRect);
	pDC->SelectObject(old);
	if(m_bShowDestino) {
		pDC->SetTextColor(RGB(255,0,0));
		pDC->SetBkMode(TRANSPARENT);
		pDC->TextOut(m_pDestino.x, m_pDestino.y, "x");
	}
}

bool CAuto::NextStep(CRuta *ruta) {

	CPoint punto=m_pRect.CenterPoint();
	if( punto==m_pDestino) {
		m_nLlegada++;
		if(m_nLlegada==MAX_DELAY) {
			CNodo *nuevo= ruta->GetNodo(punto.x, punto.y);
			if(nuevo)
				nuevo->SetAuto();
		}
		return m_nLlegada!=MAX_DELAY;
	}
	CNodo *nodo=NULL;
	nodo=ruta->GetNodo(punto.x, punto.y);
	if(!nodo)
		return false;
	CPoint original=punto;

	int direccion= nodo->GetDireccion();
	bool unico=true;
	switch(direccion) {
		case DIRECCION_DERECHA:
			punto.x+=RUTA_PRESICION;
			break;
		case DIRECCION_ABAJO:
			punto.y+=RUTA_PRESICION;
			break;
		case DIRECCION_IZQUIERDA:
			punto.x-=RUTA_PRESICION;
			break;
		case DIRECCION_ARRIBA:
			punto.y-=RUTA_PRESICION;
			break;
		default:
			unico=false;
			break;
	}
	if(!unico) {
		if( m_bHorizontal) {
			if( !unico && direccion&DIRECCION_DERECHA) {
				if( punto.x<m_pDestino.x) {
					punto.x+=RUTA_PRESICION;
					unico=true;
				}
			}
			if( !unico && direccion&DIRECCION_IZQUIERDA) {
				if( punto.x>m_pDestino.x) {
					punto.x-=RUTA_PRESICION;
					unico=true;
				}
			}
			if( !unico && direccion&DIRECCION_ARRIBA) {
				if( punto.y>m_pDestino.y) {
					punto.y-=RUTA_PRESICION;
					unico=true;
				}
			}
			if( !unico && direccion&DIRECCION_ABAJO) {
				if( punto.y<m_pDestino.y) {
					punto.y+=RUTA_PRESICION;
					unico=true;
				}
			}
		} else {
			if( !unico && direccion&DIRECCION_ARRIBA) {
				if( punto.y>m_pDestino.y) {
					punto.y-=RUTA_PRESICION;
					unico=true;
				}
			}
			if( !unico && direccion&DIRECCION_ABAJO) {
				if( punto.y<m_pDestino.y) {
					punto.y+=RUTA_PRESICION;
					unico=true;
				}
			}
			if( !unico && direccion&DIRECCION_DERECHA) {
				if( punto.x<m_pDestino.x) {
					punto.x+=RUTA_PRESICION;
					unico=true;
				}
			}
			if( !unico && direccion&DIRECCION_IZQUIERDA) {
				if( punto.x>m_pDestino.x) {
					punto.x-=RUTA_PRESICION;
					unico=true;
				}
			}
		}
	}
	if( !unico) {
		if( m_bHorizontal) {
			if( direccion&DIRECCION_DERECHA) {
				punto.x+=RUTA_PRESICION;
			} else if( direccion&DIRECCION_IZQUIERDA) {
				punto.x-=RUTA_PRESICION;
			} else if( direccion&DIRECCION_ARRIBA) {
				punto.y-=RUTA_PRESICION;
			} else if( direccion&DIRECCION_ABAJO) {
				punto.y+=RUTA_PRESICION;
			} 
		} else {
			if( direccion&DIRECCION_ARRIBA) {
				punto.y-=RUTA_PRESICION;
			} else if( direccion&DIRECCION_ABAJO) {
				punto.y+=RUTA_PRESICION;
			} else if( direccion&DIRECCION_DERECHA) {
				punto.x+=RUTA_PRESICION;
			} else if( direccion&DIRECCION_IZQUIERDA) {
				punto.x-=RUTA_PRESICION;
			}
		}
	}
	m_nIntentos++;
	CNodo *nuevo= ruta->GetNodo(punto.x, punto.y);
	if(nuevo && nuevo->SetAuto(this)) {
		nodo->SetAuto();
		SetPoint(&punto);
		if( m_bHorizontal) {
			if(m_pDestino.x==punto.x) {
				m_nIntentos=0;
			}
		} else {
			if(m_pDestino.y==punto.y) {
				m_nIntentos=0;
			}
		}
		if( m_nIntentos==10) {
			m_bHorizontal=!m_bHorizontal;
		}
	}
	if( m_nIntentos==MAX_INTENTOS) {
		if(nuevo)
			nuevo->SetAuto();
		if( nodo)
			nodo->SetAuto();
		return false;
	}
	return true;
}
