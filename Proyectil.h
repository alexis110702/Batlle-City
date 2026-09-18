#pragma once
#include "Entidad.h"
#include "Comun.h"

namespace Battle {

	using namespace System;
	using namespace System::Drawing;

	/// <summary>
	/// Proyectil que se desplaza en linea recta hasta chocar con otra entidad
	/// o salir de los limites del mapa (req. 9).
	/// </summary>
	public ref class Proyectil : public Entidad {
	private:
		Direccion direccion;
		int velocidad;
		int dano;
		OrigenProyectil origen;

	public:
		static const int TAMANO = 6;

		Proyectil(int posX, int posY, Direccion dir, OrigenProyectil org, int vel)
			: Entidad(posX, posY), direccion(dir), velocidad(vel), dano(1), origen(org) {
		}

		property Direccion Dir { Direccion get() { return direccion; } }
		property OrigenProyectil Origen { OrigenProyectil get() { return origen; } }
		property int Dano { int get() { return dano; } }

		virtual void Actualizar() override {
			switch (direccion) {
			case Direccion::Arriba: y -= velocidad; break;
			case Direccion::Abajo: y += velocidad; break;
			case Direccion::Izquierda: x -= velocidad; break;
			case Direccion::Derecha: x += velocidad; break;
			}

			// Si abandona los limites del escenario se desactiva (req. 9)
			if (x < 0 || y < 0 || x > Constantes::ANCHO_MAPA || y > Constantes::ALTO_MAPA) {
				activo = false;
			}
		}

		virtual Rectangle GetBounds() override {
			return Rectangle(x, y, TAMANO, TAMANO);
		}

		virtual void Dibujar(Graphics^ g) override {
			Brush^ pincel = (origen == OrigenProyectil::Jugador) ? Brushes::Yellow : Brushes::OrangeRed;
			g->FillRectangle(pincel, x, y, TAMANO, TAMANO);
		}
	};
}
