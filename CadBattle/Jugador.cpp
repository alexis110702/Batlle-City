#include "Jugador.h"
// ============================================================
//  CAPA DE DATOS (CadBattle) - Jugador.cpp
//  PASO 3: implementacion de CJugador (constructor, setters y getters)
// ============================================================
CJugador::CJugador(short id, int posX, int posY, int vidas) : CTanque(id, posX, posY, vidas) {
	this->nombre = "";
	this->puntuacion = 0;
	this->setDireccion(EDireccion::arriba);
}

void CJugador::setNombre(std::string nombre) {
	this->nombre = nombre;
}
void CJugador::setPuntuacion(int puntuacion) {
	this->puntuacion = puntuacion;
}
std::string CJugador::getNombre() {
	return this->nombre;
}
int CJugador::getPuntuacion() {
	return this->puntuacion;
}
