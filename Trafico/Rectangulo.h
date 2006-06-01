#pragma once

class CRectangulo
{
protected:
	CRect		m_pRect;
	COLORREF	m_dwColor;
	int			m_nBordes;
	COLORREF	m_dwBorderColor;
public:
	CRectangulo(void);
	~CRectangulo(void);
	CRect GetRect();
	void SetRect(CRect rect);
	void SetBkColor(COLORREF color);
	void Draw(CDC *pDC);
};
