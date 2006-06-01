#pragma once


# include "SemaforoInter.h"
#include "afxwin.h"

class CDlgSemaforos : public CDialog
{
	DECLARE_DYNAMIC(CDlgSemaforos)

public:
	CDlgSemaforos(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSemaforos();

// Dialog Data
	enum { IDD = IDD_DINTERSECCION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
public:
	CSemaforoInter *m_pActual;
	virtual BOOL OnInitDialog();
public:
	CEdit m_EVertical;
public:
	CEdit m_EHorizontal;
public:
	CEdit m_EAmarillo;
};
