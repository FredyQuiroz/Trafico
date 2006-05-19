// TraficoView.cpp: implementación de la clase CTraficoView
//

#include "stdafx.h"
#include "Trafico.h"
# include "mainfrm.h"

#include "TraficoDoc.h"
#include "TraficoView.h"
#include "Carretera.h"
#include "auto.h"
#include "nodo.h"
#include "semaforo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTraficoView

IMPLEMENT_DYNCREATE(CTraficoView, CView)

BEGIN_MESSAGE_MAP(CTraficoView, CView)
	// Comandos de impresión estándar
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// Construcción o destrucción de CTraficoView

CTraficoView::CTraficoView()
{
	m_nTotalC=0;
	m_nFinal=0;
}

CTraficoView::~CTraficoView()
{
	CCarretera *car;
	for( int i=0; i<m_pCarreteras.GetCount(); i++) {
        car= (CCarretera *)m_pCarreteras[i];
		delete car;
    }
	CAuto *Auto;
	for( int i=0; i<m_pAutos.GetCount(); i++) {
		Auto= (CAuto *)m_pAutos[i];
		delete Auto;
    }
	CSemaforo *sem;
	for( int i=0; i<m_pSemaforos.GetCount(); i++) {
		sem=(CSemaforo *) m_pSemaforos[i];
		delete sem;
	}
}

BOOL CTraficoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: modificar aquí la clase Window o los estilos cambiando
	//  CREATESTRUCT cs

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

	CCarretera *car;
	for( int i=0; i<m_pCarreteras.GetCount(); i++) {
        car= (CCarretera *)m_pCarreteras[i];
		car->Draw(&dcMem);
    }

	CAuto *Auto;
	for( int i=0; i<m_pAutos.GetCount(); i++) {
        Auto= (CAuto *)m_pAutos[i];
		Auto->Draw(&dcMem);
    }
	
	CSemaforo *sem;
	for( int i=0; i<m_pSemaforos.GetCount(); i++) {
		sem=(CSemaforo *) m_pSemaforos[i];
		sem->Draw(&dcMem);
	}

	CString texto;
	texto.Format("Faltan: %d", m_nFinal);
	dcMem.TextOut(5,5, texto);
	texto.Format("Llegaron: %d", m_nTotalC-m_nFinal);
	dcMem.TextOut(5,25, texto);

	//m_pRuta.Draw(&dcMem);

	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(),
		&dcMem, rect.left, rect.top, SRCCOPY);
	dcMem.SelectObject(oldbmp);
	// pDC->TextOut(100,100, "Hola mundo");
}


// Impresión de CTraficoView

BOOL CTraficoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Preparación predeterminada
	return DoPreparePrinting(pInfo);
}

void CTraficoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: agregar inicialización adicional antes de imprimir
}

void CTraficoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: agregar limpieza después de imprimir
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

	CWaitCursor wait;

	CCarretera *car;
	for( int i=1; i<4; i++) {
        
		car= new CCarretera(i*150,50,500, true, false);
		car->BuildNodos(&m_pRuta);
		m_pCarreteras.Add(car);

		car= new CCarretera(i*150+ANCHO_CARRETERA,50,500, false, false);
		car->BuildNodos(&m_pRuta);
		m_pCarreteras.Add(car);

		car= new CCarretera(50,i*150,500, false, true);
		car->BuildNodos(&m_pRuta);
		m_pCarreteras.Add(car);

		car= new CCarretera(50,i*150+ANCHO_CARRETERA,500, true, true);
		car->BuildNodos(&m_pRuta);
		m_pCarreteras.Add(car);
    }

	srand( (unsigned)time( NULL ) );
	
	int RANGE_MIN = 50;
	int RANGE_MAX =100;

	CSemaforo *sem;
	for( int i=1; i<4; i++) {
		for( int j=1; j<4; j++) {
			int inicial= (((double) rand() / (double) RAND_MAX) * RANGE_MAX + RANGE_MIN);
			int final= (((double) rand() / (double) RAND_MAX) * RANGE_MAX + RANGE_MIN);

			sem=new CSemaforo(CPoint(i*150+ANCHO_CARRETERA/2, j*150-ANCHO_CARRETERA/2), 
				CPoint(i*150+ANCHO_CARRETERA+ANCHO_CARRETERA/2,j*150+2*ANCHO_CARRETERA+ANCHO_CARRETERA/2), 
				CPoint(i*150+2*ANCHO_CARRETERA+ANCHO_CARRETERA/2, j*150+ANCHO_CARRETERA/2), 
				CPoint(i*150-ANCHO_CARRETERA/2,j*150+ANCHO_CARRETERA/2+ANCHO_CARRETERA), 
				inicial, final);
			m_pSemaforos.Add(sem);
		}
	}
	/*sem=new CSemaforo(CPoint(160, 140), CPoint(180, 200), CPoint(195, 160), CPoint(140, 180), 50, 100);
	m_pSemaforos.Add(sem);*/

	CRect rect= m_pRuta.GetLimites();
	// ARRIBA
	car= new CCarretera(rect.left-(ANCHO_CARRETERA/2),rect.top-(ANCHO_CARRETERA/2), rect.Width()+ANCHO_CARRETERA, true, true);
	car->BuildNodos(&m_pRuta, true);
	m_pCarreteras.Add(car);
	// izquierda
	car= new CCarretera(rect.left-(ANCHO_CARRETERA/2),rect.top, rect.Height(), false, false);
	car->BuildNodos(&m_pRuta, true);
	m_pCarreteras.Add(car);
	// derecha
	car= new CCarretera(rect.right-(ANCHO_CARRETERA/2),rect.top, rect.Height()+(ANCHO_CARRETERA/2), true, false);
	car->BuildNodos(&m_pRuta, true);
	m_pCarreteras.Add(car);
	// abajo
	car= new CCarretera(rect.left-(ANCHO_CARRETERA/2),rect.bottom-(ANCHO_CARRETERA/2), rect.Width()+(ANCHO_CARRETERA/2), false, true);
	car->BuildNodos(&m_pRuta, true);
	m_pCarreteras.Add(car);

	CNodo *nodo;
	if(nodo= m_pRuta.GetNodo(rect.left, rect.top)) 
		nodo->SetDireccion(DIRECCION_DERECHA);
	if(nodo= m_pRuta.GetNodo(rect.left, rect.bottom)) 
		nodo->SetDireccion(DIRECCION_ARRIBA);
	if(nodo= m_pRuta.GetNodo(rect.right, rect.top)) 
		nodo->SetDireccion(DIRECCION_ABAJO);
	if(nodo= m_pRuta.GetNodo(rect.right, rect.bottom)) 
		nodo->SetDireccion(DIRECCION_IZQUIERDA);

	m_nTotalC=m_nFinal=AfxGetApp()->GetProfileInt("control","carros", 500);

	RANGE_MIN = 0;
	RANGE_MAX = m_pRuta.m_nTamano-1;

	for( int i=0; i<m_nTotalC; i++) {

		int inicial= (((double) rand() / (double) RAND_MAX) * RANGE_MAX + RANGE_MIN);
		int final= (((double) rand() / (double) RAND_MAX) * RANGE_MAX + RANGE_MIN);
		nodo= (CNodo *)m_pRuta.m_pNodos[inicial];
		CAuto *Auto= new CAuto(nodo->m_pPunto.x, nodo->m_pPunto.y, ((CNodo *)m_pRuta.m_pNodos[final])->m_pPunto);
		m_pAutos.Add(Auto);
	}
	
	SetTimer(1, AfxGetApp()->GetProfileInt("control","actualizacion", 100), NULL);
}

void CTraficoView::OnTimer(UINT_PTR nIDEvent)
{
	if( nIDEvent==1) {

		CSemaforo *sem;
		for( int i=0; i<m_pSemaforos.GetCount(); i++) {
			sem=(CSemaforo *) m_pSemaforos[i];
			sem->NextStep(&m_pRuta);
		}
		
		CAuto *Auto;
		for( int i=0; i<m_pAutos.GetCount(); i++) {
			Auto= (CAuto *)m_pAutos[i];
			if(!Auto->NextStep(&m_pRuta)) {
				m_pAutos.RemoveAt(i);
				delete Auto;
				i--;
				m_nFinal--;
			}
		}
		Invalidate(false);
	}
	CView::OnTimer(nIDEvent);
}

void CTraficoView::OnDestroy()
{
	KillTimer(1);
	CView::OnDestroy();
}

void CTraficoView::OnMouseMove(UINT nFlags, CPoint point)
{
	CMainFrame *mainwnd=(CMainFrame *)AfxGetMainWnd();
	CString temp;
	temp.Format("%d - %d", point.x, point.y);
	mainwnd->m_wndStatusBar.SetWindowText(temp);
	CView::OnMouseMove(nFlags, point);
}
