#include "Controladora.h"
#include "MapaCln.h"
// ============================================================
//  CAPA DE NEGOCIO (ClnBattle) - Controladora.cpp
//  PASO 7: Inicializar(), CambiarNivel(n) y crearTanques(): aqui se CREAN el Jugador
//           y el Enemigo (PUNTO b)
// ============================================================

CControladora::CControladora() {
	mapa = new CMapa();
	jugador = nullptr;
	enemigo = nullptr;
}

CControladora::~CControladora() {
	delete mapa;
	delete jugador;
	delete enemigo;
}

void CControladora::Inicializar() {
	CambiarNivel(1);
}

void CControladora::CambiarNivel(int nivel) {
	CMapaCln::CargarNivel(mapa, nivel);
	crearTanques();
}

// PUNTO b: la Controladora crea el Jugador y UN Enemigo en sus posiciones iniciales
void CControladora::crearTanques() {
	delete jugador;
	delete enemigo;

	// Jugador: ultima fila, a la izquierda de la base (columna 4)
	jugador = new CJugador(1, 4 * ANCHO_IMAGEN, (MAX_FILAS - 1) * ALTO_IMAGEN, 3);
	// Enemigo tipo 1: esquina superior izquierda
	enemigo = new CEnemigo(1, static_cast<short>(ETipoTanque::tipo1), 0, 0, 1);
}

CMapa* CControladora::getMapa() {
	return mapa;
}

CJugador* CControladora::getJugador() {
	return jugador;
}

CEnemigo* CControladora::getEnemigo() {
	return enemigo;
}