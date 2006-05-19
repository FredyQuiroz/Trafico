#pragma once
# include "ruta.h"

# define AUTO_ANCHO		10
# define AUTO_ALTO		10
# define MAX_DELAY		3
# define MAX_INTENTOS	10000

class CAuto
{
	CRect			m_pRect;
	CPoint			m_pDestino;
	int				m_nLlegada;
	int				m_nOldDireccion;
	bool			m_bHorizontal;
	int				m_nIntentos;
	bool			m_bShowDestino;
public:
	CAuto(int x, int y,CPoint destino);
	~CAuto(void);
	CRect GetRect();
	bool SetPoint(CPoint *punto);
	void Draw(CDC *pDC);
	bool NextStep(CRuta *ruta);
};
