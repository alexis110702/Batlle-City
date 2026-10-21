#include "Tanque.h"
// ============================================================
//  CAPA DE DATOS (CadBattle) - Tanque.cpp
//  PASO 3: implementacion de CTanque (constructor, setters y getters)
// ============================================================

CTanque::CTanque(short id, int posX, int posY, int vidas) {
	this->id = id;
	this->vidas = vidas;
	this->direccion = EDireccion::arriba;
	this->velocidad = 10;
	this->posX = posX;
	this->posY = posY;
}

CTanque::~CTanque() {}

void CTanque::setId(short id) {
	this->id = id;
}
void CTanque::setVidas(short vidas) {
	this->vidas = vidas;
}
void CTanque::setDireccion(EDireccion direccion) {
	this->direccion = direccion;
}
void CTanque::setVelocidad(short velocidad) {
	this->velocidad = velocidad;
}
void CTanque::setX(int posX) {
	this->posX = posX;
}
void CTanque::setY(int posY) {
	this->posY = posY;
}

short CTanque::getId() {
	return this->id;
}
short CTanque::getVidas() {
	return this->vidas;
}
EDireccion CTanque::getDireccion() {
	return this->direccion;
}
short CTanque::getVelocidad() {
	return this->velocidad;
}
int CTanque::getX() {
	return this->posX;
}
int CTanque::getY() {
	return this->posY;
}
