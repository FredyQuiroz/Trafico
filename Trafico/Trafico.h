// Trafico.h: archivo de encabezado principal para la aplicación Trafico
//
#pragma once

#ifndef __AFXWIN_H__
	#error "incluir 'stdafx.h' antes de incluir este archivo para PCH"
#endif

#include "resource.h"       // Símbolos principales


// CTraficoApp:
// Consulte la sección Trafico.cpp para obtener información sobre la implementación de esta clase
//

class CTraficoApp : public CWinApp
{
public:
	CTraficoApp();


// Reemplazos
public:
	virtual BOOL InitInstance();

// Implementación
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTraficoApp theApp;