#pragma once
# include "ruta.h"
# include "nodo.h"

# define SEMAFORO_SIZE	10
class CSemaforo
{
	CPoint	m_pPointV1;
	CPoint	m_pPointV2;
	CPoint	m_pPointH1;
	CPoint	m_pPointH2;
	CRect	m_pRectV1;
	CRect	m_pRectV2;
	CRect	m_pRectH1;
	CRect	m_pRectH2;
	int		m_nVertical;
	int		m_nHorizontal;
	int		m_nEstado;
	CNodo	*m_pNodoV1;
	CNodo	*m_pNodoV2;
	CNodo	*m_pNodoH1;
	CNodo	*m_pNodoH2;
public:
	CSemaforo(CRect vS, CRect vI, CRect hD,CRect hI, int vertical, int horizontal);
	CSemaforo(CPoint vS, CPoint vI, CPoint hD,CPoint hI, int vertical, int horizontal);
public:
	~CSemaforo();
	void Draw(CDC *pDC);
	bool NextStep(CRuta *ruta);
};
