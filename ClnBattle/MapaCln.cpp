#include "MapaCln.h"
#include "NivelCad.h"
// ============================================================
//  CAPA DE NEGOCIO (ClnBattle) - MapaCln.cpp
//  PASO 6: pide la matriz a CNivelCad y crea un CBloque por cada numero (PUNTO a)
// ============================================================
CBloque* CMapaCln::CrearBloque(int codigo) {
	switch (codigo) {
	case 2:
		return new CBloque(ETipoBloque::destruible, 2);
	case 3:
		return new CBloque(ETipoBloque::noDestruible, -1);
	case 4:
		return new CBloque(ETipoBloque::agua, -1);
	case 5:
		return new CBloque(ETipoBloque::arbol, -1);
	case 9:
		return new CBloque(ETipoBloque::trofeo, 1);
	default:
		return new CBloque(ETipoBloque::piso, 0);
	}
}

void CMapaCln::CargarNivel(CMapa* mapa, int nivel) {
	int matriz[MAX_FILAS][MAX_COLUMNAS];
	CNivelCad::Obtener(nivel, matriz);

	for (int i = 0; i < MAX_FILAS; i++) {
		for (int j = 0; j < MAX_COLUMNAS; j++) {
			mapa->setBloque(i, j, CrearBloque(matriz[i][j]));
		}
	}
	mapa->setNivel(nivel);
}

