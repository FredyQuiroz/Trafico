// DlgSemaforos.cpp : implementation file
//

#include "stdafx.h"
#include "Trafico.h"
#include "DlgSemaforos.h"


// CDlgSemaforos dialog

IMPLEMENT_DYNAMIC(CDlgSemaforos, CDialog)

CDlgSemaforos::CDlgSemaforos(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSemaforos::IDD, pParent)
{
	m_pActual=NULL;
}

CDlgSemaforos::~CDlgSemaforos()
{
}

void CDlgSemaforos::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EVERTICAL, m_EVertical);
	DDX_Control(pDX, IDC_EHORIZONTAL, m_EHorizontal);
	DDX_Control(pDX, IDC_EAMARILLO, m_EAmarillo);
}


BEGIN_MESSAGE_MAP(CDlgSemaforos, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgSemaforos::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgSemaforos message handlers

void CDlgSemaforos::OnBnClickedOk()
{
	int vert, hori, amar;
	CString texto;
	m_EAmarillo.GetWindowText(texto);
	amar= atoi(texto);
	m_EVertical.GetWindowText(texto);
	vert= atoi(texto);
	m_EHorizontal.GetWindowText(texto);
	hori= atoi(texto);
	m_pActual->SetTiempo(vert,hori, amar);
	OnOK();
}

BOOL CDlgSemaforos::OnInitDialog()
{
	CDialog::OnInitDialog();
	ASSERT(m_pActual);
	CString texto;

	int tiempo= m_pActual->GetTiempoAmarillo();
	texto.Format("%d" , tiempo);
	m_EAmarillo.SetWindowText(texto);
	
	tiempo= m_pActual->GetTiempoRojoH();
	texto.Format("%d" , tiempo);
	m_EHorizontal.SetWindowText(texto);

	tiempo= m_pActual->GetTiempoRojoV();
	texto.Format("%d" , tiempo);
	m_EVertical.SetWindowText(texto);

	return TRUE;
}
