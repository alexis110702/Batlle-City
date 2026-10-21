#include "DibujoMapa.h"
// ============================================================
//  CAPA DE PRESENTACION (CpBattle) - DibujoMapa.cpp
//  PASO 8: recorre la matriz y dibuja cada bloque (incluye agua y arbol)
// ============================================================

void CDibujoMapa::Dibujar(Graphics^ g, CMapa* mapa, Bitmap^ bmpPiso, Bitmap^ bmpBloques, Bitmap^ bmpTrofeo) {
	if (mapa == nullptr) return;

	Rectangle rectPiso = Rectangle(0 * ANCHO_IMAGEN, 0 * ALTO_IMAGEN, ANCHO_IMAGEN, ALTO_IMAGEN);
	Rectangle rectDestruible = Rectangle(1 * ANCHO_IMAGEN, 0 * ALTO_IMAGEN, ANCHO_IMAGEN, ALTO_IMAGEN);
	Rectangle rectNoDestruible = Rectangle(0 * ANCHO_IMAGEN, 1 * ALTO_IMAGEN, ANCHO_IMAGEN, ALTO_IMAGEN);
	Rectangle rectAgua = Rectangle(2 * ANCHO_IMAGEN, 0 * ALTO_IMAGEN, ANCHO_IMAGEN, ALTO_IMAGEN);
	Rectangle rectArbol = Rectangle(1 * ANCHO_IMAGEN, 1 * ALTO_IMAGEN, ANCHO_IMAGEN, ALTO_IMAGEN);
	Rectangle rectTrofeo = Rectangle(0 * ANCHO_IMAGEN, 0 * ALTO_IMAGEN, ANCHO_IMAGEN, ALTO_IMAGEN);

	int X = 0, Y = 0;
	for (int i = 0; i < MAX_FILAS; i++) {
		X = 0;
		for (int j = 0; j < MAX_COLUMNAS; j++) {
			Rectangle destino = Rectangle(X, Y, ANCHO_IMAGEN, ALTO_IMAGEN);
			switch (mapa->getBloque(i, j)->getTipo()) {
			case ETipoBloque::piso:
				g->DrawImage(bmpPiso, destino, rectPiso, GraphicsUnit::Pixel);
				break;
			case ETipoBloque::destruible:
				g->DrawImage(bmpBloques, destino, rectDestruible, GraphicsUnit::Pixel);
				break;
			case ETipoBloque::noDestruible:
				g->DrawImage(bmpBloques, destino, rectNoDestruible, GraphicsUnit::Pixel);
				break;
			case ETipoBloque::agua:
				g->DrawImage(bmpBloques, destino, rectAgua, GraphicsUnit::Pixel);
				break;
			case ETipoBloque::arbol:
				// el arbol tiene fondo transparente: primero se dibuja el piso
				g->DrawImage(bmpPiso, destino, rectPiso, GraphicsUnit::Pixel);
				g->DrawImage(bmpBloques, destino, rectArbol, GraphicsUnit::Pixel);
				break;
			case ETipoBloque::trofeo:
				g->DrawImage(bmpTrofeo, destino, rectTrofeo, GraphicsUnit::Pixel);
				break;
			}
			X += ANCHO_IMAGEN;
		}
		Y += ALTO_IMAGEN;
	}
}
