#pragma once
#include "Comun.h"

namespace Battle {

	/// <summary>
	/// Celda de la cuadricula que compone el mapa (req. 1, 3). Se usa
	/// principalmente para calcular la posicion en pixeles de las
	/// entidades que se colocan al inicializar el mapa.
	/// </summary>
	public ref class Celda {
	private:
		int fila, columna;

	public:
		Celda(int f, int c) : fila(f), columna(c) {}

		property int Fila { int get() { return fila; } }
		property int Columna { int get() { return columna; } }
		property int PixelX { int get() { return columna * Constantes::TAM_CELDA; } }
		property int PixelY { int get() { return fila * Constantes::TAM_CELDA; } }
	};
}
