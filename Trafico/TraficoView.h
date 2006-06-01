// TraficoView.h: interfaz de la clase CTraficoView
//


#pragma once
# include "automovil.h"

class CTraficoView : public CView
{
protected: // Crear sólo a partir de serialización
	CTraficoView();
	DECLARE_DYNCREATE(CTraficoView)
	int		m_nTiempo;

// Atributos
public:
	CTraficoDoc* GetDocument() const;
	CPtrArray		m_pCarreteras;
	CPtrArray		m_pIntersecciones;
	CPtrArray		m_pAutos;
	CPtrArray		m_pInicio;
	CPtrArray		m_pSemaforos;
	void Clean();
// Operaciones
public:

// Reemplazos
public:
	virtual void OnDraw(CDC* pDC);  // Reemplazado para dibujar esta vista
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	bool	MakeStep(CAutomovil *autom, CRect rect);

// Implementación
public:
	virtual ~CTraficoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Funciones de asignación de mensajes generadas
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // Versión de depuración en TraficoView.cpp
inline CTraficoDoc* CTraficoView::GetDocument() const
   { return reinterpret_cast<CTraficoDoc*>(m_pDocument); }
#endif

