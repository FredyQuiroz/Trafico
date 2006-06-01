#pragma once
#include "rectangulo.h"

# define ALTO_SEMAFO		30
# define ANCHO_SEMAFORO		10

class CSemaforo : public CRectangulo
{
protected:
	CRect		m_pCebra;
	int			m_nEstado;
	int			m_nTiempoRojo;
	int			m_nTiempoVerde;
	int			m_nTiempoActual;
	int			m_nTiempoAmarillo;
	int			m_nPosicion;
	int			m_nAutos;
public:
	enum {
		rojo=0,
		amarillo,
		verde,
		rojoamarillo
	};
	enum {
		pos_verizq=0,
		pos_verder,
		pos_horizq,
		pos_horder
	};
public:
	CSemaforo(void);
public:
	~CSemaforo(void);
	CRect GetCebra();
	void SetCebra(CRect cebra);
	void SetColor(int color);
	void SetTiempo(int rojo,int verde);
	void Draw(CDC *pDC);
	void MakeStep();
	int  GetColor();
	int	 GetPos();
	void SetPos(int pos);
	void AddAuto(int autos=1);
	int  GetTiempoActual();
	int  GetAutomoviles();
	void SetTiempoAmarillo(int tiempo);
	int  GetTiempoAmarillo();
	int  GetTiempoRojo();
	int  GetTiempoVerde();
};
