#pragma once
#include "Bloque.h"

namespace Battle {

	using namespace System;
	using namespace System::Drawing;

	// Muro de acero: permanece intacto sin importar los impactos (req. 16)
	public ref class BloqueIndestructible : public Bloque {
	public:
		BloqueIndestructible(int posX, int posY) : Bloque(posX, posY, "Acero") {}

		virtual bool RecibirImpacto() override {
			return false; // nunca se destruye
		}

		virtual void Dibujar(Graphics^ g) override {
			g->FillRectangle(Brushes::Silver, x, y, Constantes::TAM_CELDA, Constantes::TAM_CELDA);
			g->DrawRectangle(Pens::DarkSlateGray, x, y, Constantes::TAM_CELDA, Constantes::TAM_CELDA);
		}
	};
}
