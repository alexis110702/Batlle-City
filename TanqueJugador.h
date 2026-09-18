#pragma once
#include "Tanque.h"

namespace Battle {

	using namespace System;
	using namespace System::Drawing;

	/// <summary>
	/// Tanque manejado por el usuario: responde a comandos de movimiento
	/// y disparo generados por sus acciones (req. 6, 7).
	/// </summary>
	public ref class TanqueJugador : public Tanque {
	public:
		TanqueJugador(int posX, int posY)
			: Tanque(posX, posY, Direccion::Arriba, 3, 3) {
		}

		// Traduce un comando de movimiento del usuario en un desplazamiento (req. 7)
		void ProcesarComandoMovimiento(Direccion dir) {
			if (!activo) return;
			Mover(dir);
		}

		// Traduce el comando de disparo del usuario en un nuevo proyectil (req. 7, 9)
		Proyectil^ ProcesarComandoDisparo() {
			if (!activo) return nullptr;
			return Disparar(OrigenProyectil::Jugador);
		}

		virtual void Dibujar(Graphics^ g) override {
			Brush^ pincel = TieneEscudo ? Brushes::Gold : Brushes::LightGreen;
			g->FillRectangle(pincel, x, y, TAM, TAM);
			g->DrawRectangle(Pens::Black, x, y, TAM, TAM);
			DibujarCanon(g);
		}

	private:
		void DibujarCanon(Graphics^ g) {
			int cx = x + TAM / 2, cy = y + TAM / 2;
			switch (direccion) {
			case Direccion::Arriba: g->DrawLine(Pens::Black, cx, cy, cx, y); break;
			case Direccion::Abajo: g->DrawLine(Pens::Black, cx, cy, cx, y + TAM); break;
			case Direccion::Izquierda: g->DrawLine(Pens::Black, cx, cy, x, cy); break;
			case Direccion::Derecha: g->DrawLine(Pens::Black, cx, cy, x + TAM, cy); break;
			}
		}
	};
}
