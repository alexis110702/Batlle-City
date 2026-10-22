#include "DibujoTanques.h"
// ============================================================
//  CAPA DE PRESENTACION (CpBattle) - DibujoTanques.cpp
//  PASO 9: elegir el recuadro de tanques.png segun direccion y tipo, y dibujarlo
// ============================================================
int CDibujoTanques::OrdenSprite(EDireccion direccion) {
	switch (direccion) {
	case EDireccion::arriba:
		return 0;
	case EDireccion::derecha:
		return 1;
	case EDireccion::abajo:
		return 2;
	case EDireccion::izquierda:
		return 3;
	default:
		return 0;
	}
}

// Dibuja en (x, y) el recuadro de 64x64 que empieza en (origenX, origenY) de tanques.png
void CDibujoTanques::DibujarSprite(Graphics^ g, Bitmap^ bmpTanques, int x, int y, int origenX, int origenY) {
	Rectangle origen = Rectangle(origenX, origenY, ANCHO_IMAGEN, ALTO_IMAGEN);
	Rectangle destino = Rectangle(x, y, ANCHO_IMAGEN, ALTO_IMAGEN);
	g->DrawImage(bmpTanques, destino, origen, GraphicsUnit::Pixel);
}

void CDibujoTanques::DibujarJugador(Graphics^ g, CJugador* jugador, Bitmap^ bmpTanques) {
	if (jugador == nullptr) return;
	// Tanque amarillo (primera columna): una fila por direccion
	static const int origenY[4] = { 0, 64, 128, 192 };
	DibujarSprite(g, bmpTanques, jugador->getX(), jugador->getY(), 0, origenY[OrdenSprite(jugador->getDireccion())]);
}

void CDibujoTanques::DibujarEnemigo(Graphics^ g, CEnemigo* enemigo, Bitmap^ bmpTanques) {
	if (enemigo == nullptr) return;
	// Los enemigos (primera columna) forman grupos de 4 filas (arriba, derecha, abajo, izquierda).
	// El primer grupo empieza en y = 508 y cada grupo siguiente esta 255 px mas abajo (uno por tipo).
	static const int desplazamientoY[4] = { 0, 64, 124, 191 };
	int grupo = static_cast<int>(enemigo->getTipo());
	if (grupo > 3) grupo = 3;   // la hoja trae 4 grupos: tipo5 reutiliza el ultimo
	int origenY = 508 + 255 * grupo + desplazamientoY[OrdenSprite(enemigo->getDireccion())];
	DibujarSprite(g, bmpTanques, enemigo->getX(), enemigo->getY(), 0, origenY);
}
