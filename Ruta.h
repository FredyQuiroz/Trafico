#pragma once
// # include "nodo.h"
# define RUTA_PRESICION	5

class CNodo;

class CRuta
{
public:
	CPtrArray		m_pNodos;
	int				m_nTamano;
	int				m_nMinX;
	int				m_nMinY;
	int				m_nMaxX;
	int				m_nMaxY;
public:
	CRuta(void);
public:
	~CRuta(void);
	CNodo *AddNodo(int x, int y, int direccion);
	int GetIndex(int x, int y);
	int GetIndex(CPoint punto);
	CPoint GetPunto(int index);
	CNodo *GetNodo(int x, int y);
	CNodo *GetNodo(int index);
	CNodo *GetNodo(CPoint punto);
	void Draw(CDC *pDC);
	CRect   GetLimites();
};

