#pragma once
#include "Comun.h"
// ============================================================
//  CAPA DE DATOS (CadBattle) - NivelCad.h
//  PASO 5: CNivelCad::Obtener(nivel, matriz): entrega la matriz numerica de un nivel (PUNTO a)
// ============================================================
// Origen de los datos de los niveles: las matrices de numeros
// 1 piso, 2 destruible, 3 no destruible, 4 agua, 5 arbol, 9 trofeo (base)
class CNivelCad {
public:
	static void Obtener(int nivel, int matriz[MAX_FILAS][MAX_COLUMNAS]);
};

