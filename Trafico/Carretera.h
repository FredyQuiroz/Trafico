#pragma once
#include "rectangulo.h"

class CCarretera : public CRectangulo
{
protected:
	COLORREF		m_dwColorLinea;
public:
	CCarretera(void);
public:
	~CCarretera(void);
	void Draw(CDC *pDC);
};
