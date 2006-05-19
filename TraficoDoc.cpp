// TraficoDoc.cpp: implementación de la clase CTraficoDoc
//

#include "stdafx.h"
#include "Trafico.h"

#include "TraficoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTraficoDoc

IMPLEMENT_DYNCREATE(CTraficoDoc, CDocument)

BEGIN_MESSAGE_MAP(CTraficoDoc, CDocument)
END_MESSAGE_MAP()


// Construcción o destrucción de CTraficoDoc

CTraficoDoc::CTraficoDoc()
{
	// TODO: agregar aquí el código de construcción único

}

CTraficoDoc::~CTraficoDoc()
{
}

BOOL CTraficoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: agregar aquí código de reinicio
	// (los documentos SDI volverán a utilizar este documento)

	return TRUE;
}




// Serialización de CTraficoDoc

void CTraficoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: agregar aquí el código de almacenamiento
	}
	else
	{
		// TODO: agregar aquí el código de carga
	}
}


// Diagnósticos de CTraficoDoc

#ifdef _DEBUG
void CTraficoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTraficoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Comandos de CTraficoDoc
