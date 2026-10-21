#include "Mapa.h"
// ============================================================
//  CAPA DE DATOS (CadBattle) - Mapa.cpp
//  PASO 4: implementacion de CMapa (constructor, destructor, getBloque, setBloque)
// ============================================================
CMapa::CMapa() {
	for (int i = 0; i < MAX_FILAS; i++) {
		for (int j = 0; j < MAX_COLUMNAS; j++) {
			mapa[i][j] = nullptr;
		}
	}
	this->nivel = 1;
}

CMapa::~CMapa() {
	for (int i = 0; i < MAX_FILAS; i++) {
		for (int j = 0; j < MAX_COLUMNAS; j++) {
			delete mapa[i][j];
		}
	}
}

void CMapa::setNivel(int nivel) {
	this->nivel = nivel;
}

int CMapa::getNivel() {
	return this->nivel;
}

CBloque* CMapa::getBloque(int i, int j) {
	return mapa[i][j];
}
// Guarda un bloque en la celda (i, j); si ya habia uno (de otro nivel) lo libera
void CMapa::setBloque(int i, int j, CBloque* bloque) {
	delete mapa[i][j];
	mapa[i][j] = bloque;
}

