#pragma once
#include "Mapa.h"

using namespace System::Drawing;

// ============================================================
//  CAPA DE PRESENTACION (CpBattle) - DibujoMapa.h
//  PASO 8: CDibujoMapa::Dibujar(g, mapa, bitmaps...): dibuja el mapa
// ============================================================

using namespace System::Drawing;

// Presentacion: dibuja el CMapa recortando los sprites de pisos.png, bloques.png y trofeo.png
class CDibujoMapa {
public:
	static void Dibujar(Graphics^ g, CMapa* mapa, Bitmap^ bmpPiso, Bitmap^ bmpBloques, Bitmap^ bmpTrofeo);
};