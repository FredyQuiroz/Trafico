#include "StdAfx.h"
#include "Nodo.h"

CNodo::CNodo(int direccion,CPoint punto)
{
	m_pAuto=NULL;
	m_pPunto= punto;
	m_nDireccion=direccion;
	m_bSemaforo=false;
}
CNodo::CNodo(int direccion,int x, int y) {
	m_pAuto=NULL;
	m_pPunto= CPoint(x, y);
	m_nDireccion=direccion;
	m_bSemaforo=false;
}

CNodo::~CNodo(void)
{
}

int CNodo::GetDireccion() {
	return m_nDireccion;
}
void CNodo::SetDireccion(int direccion) {
	m_nDireccion= direccion;
}
bool CNodo::SetAuto(CAuto *Auto) {
	if(Auto) {
		if( m_pAuto)
			return false;
		if( m_bSemaforo)
			return false;
	}
	m_pAuto=Auto;
	return true;
}

void CNodo::SetRed(bool red) {
	m_bSemaforo=red;
}

CAuto *CNodo::GetAuto() {
	return m_pAuto;
}