#pragma once
#include "Tanque.h"

namespace Battle {

	using namespace System;
	using namespace System::Drawing;

	/// <summary>
	/// Tanque controlado por el sistema. Se mueve y dispara siguiendo
	/// reglas de comportamiento automatico (req. 6, 8).
	/// </summary>
	public ref class TanqueEnemigo : public Tanque {
	private:
		TipoEnemigo tipo;
		int contadorCambioDireccion;
		Random^ rnd;

		Direccion DireccionAleatoria() {
			switch (rnd->Next(4)) {
			case 0: return Direccion::Arriba;
			case 1: return Direccion::Abajo;
			case 2: return Direccion::Izquierda;
			default: return Direccion::Derecha;
			}
		}

	public:
		TanqueEnemigo(int posX, int posY, TipoEnemigo t)
			: Tanque(posX, posY, Direccion::Abajo,
				(t == TipoEnemigo::Rapido ? 3 : (t == TipoEnemigo::Blindado ? 1 : 2)),
				(t == TipoEnemigo::Blindado ? 3 : 1)),
			tipo(t), contadorCambioDireccion(0) {
			rnd = gcnew Random(Environment::TickCount ^ (posX * 397 + posY));
		}

		property TipoEnemigo Tipo { TipoEnemigo get() { return tipo; } }

		// Decide el rumbo del enemigo cada cierto numero de ciclos (req. 8)
		void ActualizarComportamiento() {
			if (!activo) return;
			contadorCambioDireccion--;
			if (contadorCambioDireccion <= 0) {
				Direc = DireccionAleatoria();
				contadorCambioDireccion = 20 + rnd->Next(40);
			}
		}

		// Con una probabilidad baja, el enemigo decide disparar en este ciclo (req. 8, 9)
		Proyectil^ IntentarDisparar() {
			if (!activo) return nullptr;
			if (rnd->Next(100) < 4) {
				return Disparar(OrigenProyectil::Enemigo);
			}
			return nullptr;
		}

		virtual void Dibujar(Graphics^ g) override {
			Brush^ pincel;
			switch (tipo) {
			case TipoEnemigo::Rapido: pincel = Brushes::DeepSkyBlue; break;
			case TipoEnemigo::Blindado: pincel = Brushes::Gray; break;
			default: pincel = Brushes::IndianRed; break;
			}
			g->FillRectangle(pincel, x, y, TAM, TAM);
			g->DrawRectangle(Pens::Black, x, y, TAM, TAM);
		}
	};
}
