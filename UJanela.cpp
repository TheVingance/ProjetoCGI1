//---------------------------------------------------------------------------

#pragma hdrstop

#include "UJanela.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
// Construtor da Janela: define os limites minimos e maximos dos eixos X e Y
Janela::Janela(double nxMin, double nyMin, double nxMax, double nyMax){

	xMin = nxMin;
	yMin = nyMin;
	xMax = nxMax;
	yMax = nyMax;

}