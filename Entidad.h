#pragma once
#include "Comun.h"

namespace Battle {

	using namespace System;
	using namespace System::Drawing;

	/// <summary>
	/// Toda entidad del juego (tanques, proyectiles, bloques, powerups, base)
	/// comparte posicion, estado activo y capacidad de interactuar (req. 4).
	/// </summary>
	public ref class Entidad abstract {
	protected:
		int x, y;
		bool activo;

	public:
		Entidad(int posX, int posY) : x(posX), y(posY), activo(true) {}

		property int X { int get() { return x; } void set(int v) { x = v; } }
		property int Y { int get() { return y; } void set(int v) { y = v; } }
		property bool Activo { bool get() { return activo; } void set(bool v) { activo = v; } }

		// Rectangulo de colision de la entidad dentro del mapa
		virtual Rectangle GetBounds() abstract;

		// Logica propia de cada ciclo de juego (por defecto no hace nada)
		virtual void Actualizar() { }

		// Representacion visual de la entidad
		virtual void Dibujar(Graphics^ g) abstract;

		// Capacidad basica de interactuar con otra entidad del mapa (req. 4)
		virtual bool Interactuar(Entidad^ otra) {
			if (otra == nullptr || !activo || !otra->Activo) return false;
			return GetBounds().IntersectsWith(otra->GetBounds());
		}
	};
}
