#pragma once
#include <string>
#include "Tanque.h"
// ============================================================
//  CAPA DE DATOS (CadBattle) - Jugador.h
//  PASO 3: clase CJugador : CTanque (nombre, puntuacion)
// ============================================================


class CJugador : public CTanque {
	std::string nombre;
	int puntuacion;
public:
	CJugador(short id, int posX, int posY, int vidas);
	void setNombre(std::string nombre);
	void setPuntuacion(int puntuacion);
	std::string getNombre();
	int getPuntuacion();
};