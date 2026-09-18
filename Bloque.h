#pragma once
#include "Entidad.h"
#include "Comun.h"

namespace Battle {

	using namespace System;
	using namespace System::Drawing;

	/// <summary>
	/// Obstaculo que bloquea el movimiento de los tanques y el paso de
	/// los proyectiles (req. 14). Las subclases definen si se destruye
	/// o no al recibir impactos (req. 15, 16).
	/// </summary>
	public ref class Bloque abstract : public Entidad {
	protected:
		String^ tipo;

	public:
		Bloque(int posX, int posY, String^ t) : Entidad(posX, posY), tipo(t) {}

		property String^ Tipo { String^ get() { return tipo; } }

		virtual Rectangle GetBounds() override {
			return Rectangle(x, y, Constantes::TAM_CELDA, Constantes::TAM_CELDA);
		}

		// Devuelve true si el bloque quedo destruido tras el impacto (req. 11, 15, 16)
		virtual bool RecibirImpacto() abstract;
	};
}
