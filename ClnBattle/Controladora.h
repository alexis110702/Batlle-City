#pragma once
#include "Mapa.h"
#include "Jugador.h"
#include "Enemigo.h"
// ============================================================
//  CAPA DE NEGOCIO (ClnBattle) - Controladora.h
//  PASO 7: CControladora: tiene el CMapa, el CJugador y el CEnemigo (PUNTO b)
// ============================================================

class CControladora {
private:
	CMapa* mapa;
	CJugador* jugador;
	CEnemigo* enemigo;
	void crearTanques();
public:
	CControladora();
	~CControladora();

	void Inicializar();
	void CambiarNivel(int nivel);

	CMapa* getMapa();
	CJugador* getJugador();
	CEnemigo* getEnemigo();
};
