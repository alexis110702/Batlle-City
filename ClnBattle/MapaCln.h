#pragma once
#include "Mapa.h"
// ============================================================
//  CAPA DE NEGOCIO (ClnBattle) - MapaCln.h
//  PASO 6: CMapaCln::CargarNivel(mapa, nivel): llena el CMapa con bloques
// ============================================================
// Regla de negocio: convertir la matriz numerica de un nivel en bloques del mapa
class CMapaCln {
public:
	static void CargarNivel(CMapa* mapa, int nivel);
private:
	static CBloque* CrearBloque(int codigo);
};

