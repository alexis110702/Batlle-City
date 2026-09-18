#pragma once
#include "Entidad.h"
#include "Comun.h"

namespace Battle {

	using namespace System;
	using namespace System::Drawing;

	/// <summary>
	/// Objetivo que el jugador debe proteger durante toda la partida (req. 12).
	/// Si es destruida por un proyectil o un tanque enemigo, la partida
	/// finaliza (req. 13).
	/// </summary>
	public ref class BaseJuego : public Entidad {
	private:
		bool destruida;

	public:
		BaseJuego(int posX, int posY) : Entidad(posX, posY), destruida(false) {}

		property bool Destruida { bool get() { return destruida; } }

		virtual Rectangle GetBounds() override {
			return Rectangle(x, y, Constantes::TAM_CELDA, Constantes::TAM_CELDA);
		}

		// Marca la base como destruida (req. 13)
		void RecibirImpacto() {
			destruida = true;
			activo = false;
		}

		virtual void Dibujar(Graphics^ g) override {
			Brush^ pincel = destruida ? Brushes::Black : Brushes::Yellow;
			g->FillRectangle(pincel, x, y, Constantes::TAM_CELDA, Constantes::TAM_CELDA);
			g->DrawRectangle(Pens::Red, x, y, Constantes::TAM_CELDA, Constantes::TAM_CELDA);
			if (!destruida) {
				g->DrawString("B", gcnew Font("Arial", 10, FontStyle::Bold), Brushes::Black, (float)(x + 8), (float)(y + 6));
			}
		}
	};
}
