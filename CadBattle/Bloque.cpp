#include "Bloque.h"
// ============================================================
//  CAPA DE DATOS (CadBattle) - Bloque.cpp
//  PASO 2: implementacion de CBloque
// ============================================================

CBloque::CBloque(ETipoBloque tipo, int durabilidad) {
	this->tipo = tipo;
	this->durabilidad = durabilidad;
}

CBloque::~CBloque() {}

ETipoBloque CBloque::getTipo() {
	return this->tipo;
}

void CBloque::setDurabilidad(short durabilidad) {
	this->durabilidad = durabilidad;
}

short CBloque::getDurabilidad() {
	return this->durabilidad;
}