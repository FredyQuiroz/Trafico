#pragma once
# include "automovil.h"

# define	ANCHO_CARRETERA		50
# define	ANCHO_CARRO			40
# define	BORDE_AUTO			5
# define	ALTO_CARRO			70

class CStartPoint
{
protected:
	int		m_nX;
	int		m_nY;
	bool	m_bHorizontal;
	bool	m_bAscendente;
public:
	CStartPoint(int x, int y, bool hor, bool asc);
public:
	~CStartPoint(void);
	CAutomovil	*GetCar();
};
