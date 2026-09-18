#pragma once
#include "Bloque.h"

namespace Battle {

	using namespace System;
	using namespace System::Drawing;

	// Muro de ladrillo: se va desgastando y termina destruyendose (req. 15)
	public ref class BloqueDestructible : public Bloque {
	private:
		int resistencia;

	public:
		BloqueDestructible(int posX, int posY, int resistenciaInicial)
			: Bloque(posX, posY, "Ladrillo"), resistencia(resistenciaInicial) {
		}

		virtual bool RecibirImpacto() override {
			resistencia--;
			if (resistencia <= 0) {
				activo = false;
				return true;
			}
			return false;
		}

		virtual void Dibujar(Graphics^ g) override {
			Brush^ pincel = (resistencia > 1) ? Brushes::Firebrick : Brushes::SaddleBrown;
			g->FillRectangle(pincel, x, y, Constantes::TAM_CELDA, Constantes::TAM_CELDA);
			g->DrawRectangle(Pens::Black, x, y, Constantes::TAM_CELDA, Constantes::TAM_CELDA);
		}
	};
}
