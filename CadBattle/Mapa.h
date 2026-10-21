#pragma once
#include "Bloque.h"

// ============================================================
//  CAPA DE DATOS (CadBattle) - Mapa.h
//  PASO 4: clase CMapa: matriz de CBloque* y el numero de nivel (solo datos)
// ============================================================
class CMapa {
	CBloque* mapa[MAX_FILAS][MAX_COLUMNAS];
	int nivel;
public:
	CMapa();
	~CMapa();
	void setNivel(int nivel);
	int getNivel();
	CBloque* getBloque(int i, int j);
	void setBloque(int i, int j, CBloque* bloque);
};

