#include "Enemigo.h"
// ============================================================
//  CAPA DE DATOS (CadBattle) - Enemigo.cpp
//  PASO 3: implementacion de CEnemigo (constructor, setTipo, getTipo)
// ============================================================
CEnemigo::CEnemigo(short id, short tipo, int posx, int posy, int vidas) : CTanque(id, posx, posy, vidas) {
	this->tipo = static_cast<ETipoTanque>(tipo);
	this->setDireccion(EDireccion::abajo);
}

void CEnemigo::setTipo(ETipoTanque tipo) {
	this->tipo = tipo;
}
ETipoTanque CEnemigo::getTipo() {
	return this->tipo;
}
