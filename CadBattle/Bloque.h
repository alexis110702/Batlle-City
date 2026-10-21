#pragma once
#include "Comun.h"
// ============================================================
//  CAPA DE DATOS (CadBattle) - Bloque.h
//  PASO 2: clase CBloque: una celda del mapa (tipo y durabilidad)
// ============================================================

class CBloque {
	ETipoBloque tipo;
	short durabilidad;

public:
	CBloque(ETipoBloque tipo, int durabilidad);
	~CBloque();

	ETipoBloque getTipo();
	void setDurabilidad(short durabilidad);
	short getDurabilidad();
};
