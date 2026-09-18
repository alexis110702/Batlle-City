#pragma once
#include "Entidad.h"
#include "Comun.h"
#include "TanqueJugador.h"

namespace Battle {

	using namespace System;
	using namespace System::Drawing;

	/// <summary>
	/// Objeto especial que aparece en el mapa y otorga una ventaja temporal
	/// al tanque que lo recoge (req. 17, 18).
	/// </summary>
	public ref class PowerUp : public Entidad {
	private:
		TipoPowerUp tipo;
		int tiempoVidaRestante; // ciclos que permanece visible si nadie lo recoge
		static const int DURACION_EFECTO = 300; // ciclos que dura el efecto al recogerlo

	public:
		PowerUp(int posX, int posY, TipoPowerUp t)
			: Entidad(posX, posY), tipo(t), tiempoVidaRestante(400) {
		}

		property TipoPowerUp Tipo { TipoPowerUp get() { return tipo; } }

		virtual Rectangle GetBounds() override {
			return Rectangle(x, y, Constantes::TAM_CELDA, Constantes::TAM_CELDA);
		}

		virtual void Actualizar() override {
			tiempoVidaRestante--;
			if (tiempoVidaRestante <= 0) activo = false;
		}

		// Aplica el efecto temporal correspondiente al tanque que lo recoge (req. 17, 18)
		void AplicarEfecto(TanqueJugador^ tanque) {
			switch (tipo) {
			case TipoPowerUp::Velocidad: tanque->AplicarBonusVelocidad(DURACION_EFECTO); break;
			case TipoPowerUp::Blindaje: tanque->AplicarEscudo(DURACION_EFECTO); break;
			case TipoPowerUp::PoderDisparo: tanque->AplicarBonusDisparo(DURACION_EFECTO); break;
			case TipoPowerUp::VidaExtra: tanque->GanarVida(); break;
			}
			activo = false;
		}

		virtual void Dibujar(Graphics^ g) override {
			Brush^ pincel;
			switch (tipo) {
			case TipoPowerUp::Velocidad: pincel = Brushes::Cyan; break;
			case TipoPowerUp::Blindaje: pincel = Brushes::Gold; break;
			case TipoPowerUp::PoderDisparo: pincel = Brushes::OrangeRed; break;
			default: pincel = Brushes::Magenta; break;
			}
			g->FillEllipse(pincel, x + 4, y + 4, Constantes::TAM_CELDA - 8, Constantes::TAM_CELDA - 8);
			g->DrawEllipse(Pens::Black, x + 4, y + 4, Constantes::TAM_CELDA - 8, Constantes::TAM_CELDA - 8);
		}
	};
}
