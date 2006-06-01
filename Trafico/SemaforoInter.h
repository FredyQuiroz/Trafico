#pragma once
# include "semaforo.h"
# include "automovil.h"

class CSemaforoInter
{
	CRect		m_pRect;
	CSemaforo	m_pSemaforos[4]; 
public:
	CSemaforoInter(CRect interseccion,int rojov, int rojoh);
public:
	~CSemaforoInter(void);
	void Draw(CDC *pDC);
	void MakeStep();
	bool ValidateStep(CRect paso,CAutomovil *autom);
	int GetTiempoAmarillo();
	int GetTiempoRojoV();
	int GetTiempoRojoH();
	void SetTiempo(int rojov, int rojoh, int amarillo);
	CRect GetInterseccion();
};
