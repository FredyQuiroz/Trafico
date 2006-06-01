#pragma once
#include "rectangulo.h"
# define ANCHO_CEBRA	20

class CInterseccion : public CRectangulo
{
protected:
	COLORREF		m_dwColorLinea;
public:
	CInterseccion(void);
public:
	~CInterseccion(void);
	void Draw(CDC *pDC);
};
