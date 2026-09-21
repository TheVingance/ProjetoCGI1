//---------------------------------------------------------------------------

#ifndef uDisplayFileH
#define uDisplayFileH

#include "uPoligono.h"
#include "UJanela.h"
#include <vector>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class DisplayFile{
	public:
	  std::vector <Poligono> poligonos;

	  void desenha(TCanvas *canvas, Janela mundo,
				   Janela vp, int tipoReta);
	  void mostra(TListBox *listbox);

};

#endif
