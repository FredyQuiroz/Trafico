#pragma once
# include "ruta.h"
# define ANCHO_CARRETERA	20

class CCarretera
{
	CRect	m_pRect;
	bool	m_bHorizontal;
	int		m_nCarriles;
	bool	m_bAscendente;
public:
	CCarretera(int x, int y,int largo, bool ascendente, bool horizontal);
	~CCarretera(void);
	void BuildNodos(CRuta *ruta,bool especial=false);
	void Draw(CDC *pDC);
};
