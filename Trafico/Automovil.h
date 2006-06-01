#pragma once
#include "rectangulo.h"
# include "semaforo.h"

# define SEPARACION_AUTOS	5

class CAutomovil : public CRectangulo
{
	bool	m_bHorizontal;
	bool	m_bAscendente;
	int		m_nPasos;
	CSemaforo	*m_pSemaforo;
public:
	CAutomovil(bool hor, bool asc);
public:
	~CAutomovil(void);
	void Draw(CDC *pDC);
	CRect MakeStep();
	bool IsValidRect(CRect rect);
	CSemaforo *SetSemaforo(CSemaforo *sem); 
};
