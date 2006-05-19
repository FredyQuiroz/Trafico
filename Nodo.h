#pragma once
# include "auto.h"

# define DIRECCION_ARRIBA		1
# define DIRECCION_ABAJO		2
# define DIRECCION_DERECHA		4
# define DIRECCION_IZQUIERDA	8 

class CNodo
{
	CAuto	*m_pAuto;
	int		m_nDireccion;
	bool	m_bSemaforo;
public:
	CPoint	m_pPunto;
	CNodo(int direccion,CPoint punto);
	CNodo(int direccion,int x, int y);
	~CNodo(void);
	int GetDireccion();
	void SetDireccion(int direccion);
	bool SetAuto(CAuto *Auto=NULL);
	CAuto *GetAuto();
	void SetRed(bool red);
};
