#pragma once
#include "Jugador.h"
#include "Enemigo.h"

using namespace System::Drawing;

// ============================================================
//  CAPA DE PRESENTACION (CpBattle) - DibujoTanques.h
//  PASO 9: CDibujoTanques: DibujarJugador y DibujarEnemigo con tanques.png
//           (PUNTOS c y d)
// ============================================================
class CDibujoTanques {
public:
	static void DibujarJugador(Graphics^ g, CJugador* jugador, Bitmap^ bmpTanques);
	static void DibujarEnemigo(Graphics^ g, CEnemigo* enemigo, Bitmap^ bmpTanques);
private:
	static int OrdenSprite(EDireccion direccion);
	static void DibujarSprite(Graphics^ g, Bitmap^ bmpTanques, int x, int y, int origenX, int origenY);
};