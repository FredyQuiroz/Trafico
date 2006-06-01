// TraficoView.cpp: implementación de la clase CTraficoView
//

#include "stdafx.h"
#include "Trafico.h"

#include "TraficoDoc.h"
#include "TraficoView.h"
# include "carretera.h"
# include "interseccion.h"
# include "startpoint.h"
# include "semaforointer.h"
# include "DlgSemaforos.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTraficoView

IMPLEMENT_DYNCREATE(CTraficoView, CView)

BEGIN_MESSAGE_MAP(CTraficoView, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// Construcción o destrucción de CTraficoView

CTraficoView::CTraficoView()
{
	m_nTiempo=0;
}

CTraficoView::~CTraficoView()
{
	Clean();
}

void CTraficoView::Clean() {

	CCarretera	*car;
	for( int i=0; i<m_pCarreteras.GetCount(); i++) {
		car= (CCarretera *)m_pCarreteras[i];
		delete car;
	}
	m_pCarreteras.RemoveAll();

	CInterseccion *info;
	for( int i=0; i<m_pIntersecciones.GetCount(); i++) {
		info= (CInterseccion *)m_pIntersecciones[i];
		delete info;
	}
	m_pIntersecciones.RemoveAll();

	CAutomovil	*autom;
	for( int i=0; i<m_pAutos.GetCount(); i++) {
		autom= (CAutomovil	*)m_pAutos[i];
		delete autom;
	}
	m_pAutos.RemoveAll();

	CStartPoint	*punto;
	for( int i=0; i<m_pInicio.GetCount(); i++) {
		punto= (CStartPoint *)m_pInicio[i];
		delete punto;
	}
	m_pInicio.RemoveAll();

	CSemaforoInter *sem;
	for( int i=0; i<m_pSemaforos.GetCount(); i++) {
		sem= (CSemaforoInter *)m_pSemaforos[i];
		delete sem;
	}
	m_pSemaforos.RemoveAll();

	m_nTiempo=0;
}

BOOL CTraficoView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

// Dibujo de CTraficoView
void CTraficoView::OnDraw(CDC* pDC)
{
	CTraficoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	GetClientRect(rect);

	CDC dcMem;
	VERIFY( dcMem.CreateCompatibleDC(pDC));
	CBitmap  m_bitmap;
	m_bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	CBitmap *oldbmp= dcMem.SelectObject(&m_bitmap);
	CBrush brush(RGB(255,255,255));
	dcMem.FillRect(rect, &brush);

	CCarretera	*car;
	for( int i=0; i<m_pCarreteras.GetCount(); i++) {
		car= (CCarretera *)m_pCarreteras[i];
		car->Draw(&dcMem);
	}

	CInterseccion *info;
	for( int i=0; i<m_pIntersecciones.GetCount(); i++) {
		info= (CInterseccion *)m_pIntersecciones[i];
		info->Draw(&dcMem);
	}

	CSemaforoInter *sem;
	for( int i=0; i<m_pSemaforos.GetCount(); i++) {
		sem= (CSemaforoInter *)m_pSemaforos[i];
		sem->Draw(&dcMem);
	}

	CAutomovil	*autom;
	for( int i=0; i<m_pAutos.GetCount(); i++) {
		autom= (CAutomovil	*)m_pAutos[i];
		autom->Draw(&dcMem);
	}

	CString texto;
	texto.Format("%d Automoviles", m_pAutos.GetCount());
	dcMem.TextOut(0,0,texto);
	CTimeSpan span(0,0,0,m_nTiempo);
	texto= span.Format("%H:%M:%S");
	dcMem.TextOut(0,20, texto);

	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(),
		&dcMem, rect.left, rect.top, SRCCOPY);
	dcMem.SelectObject(oldbmp);
}


// Impresión de CTraficoView

BOOL CTraficoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CTraficoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CTraficoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{	
}


// Diagnósticos de CTraficoView

#ifdef _DEBUG
void CTraficoView::AssertValid() const
{
	CView::AssertValid();
}

void CTraficoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTraficoDoc* CTraficoView::GetDocument() const // La versión de no depuración es en línea
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTraficoDoc)));
	return (CTraficoDoc*)m_pDocument;
}
#endif //_DEBUG


// Controladores de mensaje de CTraficoView

void CTraficoView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	srand( (unsigned)time( NULL ) );
	Clean();

	CCarretera *car;
	
	car= new CCarretera();
	CRect rect,rectotro,recthorizontal;
	GetClientRect(rect);
	rectotro=rect;
	rectotro.top= rectotro.Height()/2-ANCHO_CARRETERA;
	rectotro.bottom= rectotro.top+2*ANCHO_CARRETERA;
	car->SetRect(rectotro); // horizontal
	recthorizontal= rectotro;
	m_pCarreteras.Add(car);
	// punto de inicio
	m_pInicio.Add(new CStartPoint(rectotro.left, rectotro.top+ANCHO_CARRETERA+BORDE_AUTO, true, true));
	m_pInicio.Add(new CStartPoint(rectotro.right-ANCHO_CARRETERA, rectotro.top+BORDE_AUTO, true, false));

	// vertical izquierda
	int bloque= rect.Width()/7;
	car= new CCarretera();
	rectotro=rect;
	rectotro.left= bloque*1;
	rectotro.right=rectotro.left+2*ANCHO_CARRETERA;
	car->SetRect(rectotro);
	m_pCarreteras.Add(car);
	// punto de inicio
	m_pInicio.Add(new CStartPoint(rectotro.left+BORDE_AUTO, rectotro.top, false, true));
	m_pInicio.Add(new CStartPoint(rectotro.right-ANCHO_CARRETERA+BORDE_AUTO, rectotro.bottom-ANCHO_CARRETERA, false, false));
	// interseccion
	CInterseccion *info= new CInterseccion();
	VERIFY(rectotro.IntersectRect(rectotro, recthorizontal));
	info->SetRect(rectotro);
	m_pIntersecciones.Add(info);
	m_pSemaforos.Add(new CSemaforoInter(rectotro, 50, 30));

	// vertical central
	car= new CCarretera();
	rectotro=rect;
	rectotro.left= bloque*3;
	rectotro.right=rectotro.left+2*ANCHO_CARRETERA;
	car->SetRect(rectotro);
	m_pCarreteras.Add(car);
	// punto de inicio
	m_pInicio.Add(new CStartPoint(rectotro.left+BORDE_AUTO, rectotro.top, false, true));
	m_pInicio.Add(new CStartPoint(rectotro.right-ANCHO_CARRETERA+BORDE_AUTO, rectotro.bottom-ANCHO_CARRETERA, false, false));
	// interseccion
	info= new CInterseccion();
	VERIFY(rectotro.IntersectRect(rectotro, recthorizontal));
	info->SetRect(rectotro);
	m_pIntersecciones.Add(info);
	m_pSemaforos.Add(new CSemaforoInter(rectotro, 80, 30));

	// vertical derecha
	car= new CCarretera();
	rectotro=rect;
	rectotro.left= bloque*5;
	rectotro.right=rectotro.left+2*ANCHO_CARRETERA;
	car->SetRect(rectotro);
	m_pCarreteras.Add(car);
	// punto de inicio
	m_pInicio.Add(new CStartPoint(rectotro.left+BORDE_AUTO, rectotro.top, false, true));
	m_pInicio.Add(new CStartPoint(rectotro.right-ANCHO_CARRETERA+BORDE_AUTO, rectotro.bottom-ANCHO_CARRETERA, false, false));
	// interseccion
	info= new CInterseccion();
	VERIFY(rectotro.IntersectRect(rectotro, recthorizontal));
	info->SetRect(rectotro);
	m_pIntersecciones.Add(info);
	m_pSemaforos.Add(new CSemaforoInter(rectotro, 70, 40));

	CStartPoint *punto;

	for( int i=0; i<m_pInicio.GetCount(); i++) {
		punto= (CStartPoint *)m_pInicio[i];
		m_pAutos.Add(punto->GetCar());
	}
	SetTimer(1, 100, NULL);
	SetTimer(2,1000, NULL);
}

bool CTraficoView::MakeStep(CAutomovil *autom, CRect rect) {
	
	CRect temp;

	CSemaforoInter *sem;
	for( int i=0; i<m_pSemaforos.GetCount(); i++) {
		sem= (CSemaforoInter *)m_pSemaforos[i];
		if( !sem->ValidateStep(rect, autom))
			return false;
	}
	CAutomovil *movil;
	rect.InflateRect(SEPARACION_AUTOS,SEPARACION_AUTOS);

	for( int i=0; i<m_pAutos.GetCount(); i++) {
		movil= (CAutomovil	*)m_pAutos[i];
		if( movil==autom)
			continue;
		if( temp.IntersectRect(rect, movil->GetRect()))
			return false;
	}
	rect.DeflateRect(SEPARACION_AUTOS,SEPARACION_AUTOS);
	autom->SetRect(rect);
	return true;
}

void CTraficoView::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==1) {

		m_nTiempo++;

		CSemaforoInter *sem;
		for( int i=0; i<m_pSemaforos.GetCount(); i++) {
			sem= (CSemaforoInter *)m_pSemaforos[i];
			sem->MakeStep();
		}

		CAutomovil	*autom;
		CRect rect;
		GetClientRect(rect);

		for( int i=0; i<m_pAutos.GetCount(); i++) {
			autom= (CAutomovil	*)m_pAutos[i];
			if( !autom->IsValidRect(rect)) {
				m_pAutos.RemoveAt(i);
				delete autom;
				i--;
			}
			MakeStep(autom,autom->MakeStep());
		}
		Invalidate(false);
	} else if(nIDEvent==2) {
		int  pos = (((double) rand() / (double) RAND_MAX) * m_pInicio.GetCount());
		CAutomovil *autom= ((CStartPoint *) m_pInicio[pos])->GetCar();
		if( MakeStep(autom, autom->GetRect()))
			m_pAutos.Add(autom);
		else delete autom;
	}
	CView::OnTimer(nIDEvent);
}

void CTraficoView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	
	CSemaforoInter *sem;
	CRect rect;
	for( int i=0; i<m_pSemaforos.GetCount(); i++) {
		sem= (CSemaforoInter *)m_pSemaforos[i];
		rect= sem->GetInterseccion();
		if( rect.PtInRect(point)) {
			CDlgSemaforos dlg;
			dlg.m_pActual= sem;
			dlg.DoModal();
			break;
		}
	}
	CView::OnLButtonDblClk(nFlags, point);
}
