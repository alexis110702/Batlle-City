#pragma once
#include "Entidad.h"
#include "Proyectil.h"
#include "Comun.h"

namespace Battle {

	using namespace System;
	using namespace System::Drawing;

	/// <summary>
	/// Atributos y comportamiento comun a todos los tanques: direccion,
	/// velocidad, capacidad de disparo y vidas (req. 5).
	/// </summary>
	public ref class Tanque abstract : public Entidad {
	protected:
		Direccion direccion;

		int velocidadBase;
		int velocidadBonus;
		int framesVelocidadBonus;

		int vidas;

		int cooldownDisparo;      // frames restantes hasta poder disparar de nuevo
		int cooldownMaximo;
		int framesDisparoBonus;   // frames restantes de cadencia de disparo mejorada

		int framesEscudoBonus;    // frames restantes de resistencia/blindaje temporal

		static const int TAM = Constantes::TAM_CELDA - 4;

	public:
		Tanque(int posX, int posY, Direccion dir, int vel, int vidasIniciales)
			: Entidad(posX, posY), direccion(dir),
			velocidadBase(vel), velocidadBonus(0), framesVelocidadBonus(0),
			vidas(vidasIniciales),
			cooldownDisparo(0), cooldownMaximo(20), framesDisparoBonus(0),
			framesEscudoBonus(0) {
		}

		property Direccion Direc { Direccion get() { return direccion; } void set(Direccion d) { direccion = d; } }
		property int Vidas { int get() { return vidas; } }
		property int VelocidadActual { int get() { return velocidadBase + velocidadBonus; } }
		property bool TieneEscudo { bool get() { return framesEscudoBonus > 0; } }

		virtual Rectangle GetBounds() override {
			return Rectangle(x, y, TAM, TAM);
		}

		// Desplaza el tanque en la direccion indicada segun su velocidad actual
		virtual void Mover(Direccion dir) {
			direccion = dir;
			int vel = VelocidadActual;
			switch (dir) {
			case Direccion::Arriba: y -= vel; break;
			case Direccion::Abajo: y += vel; break;
			case Direccion::Izquierda: x -= vel; break;
			case Direccion::Derecha: x += vel; break;
			}
		}

		// Deshace el ultimo movimiento cuando el mapa detecta una colision (req. 10, 14)
		virtual void Retroceder(Direccion dir) {
			int vel = VelocidadActual;
			switch (dir) {
			case Direccion::Arriba: y += vel; break;
			case Direccion::Abajo: y -= vel; break;
			case Direccion::Izquierda: x += vel; break;
			case Direccion::Derecha: x -= vel; break;
			}
		}

		// Crea un proyectil frente al tanque si la cadencia de disparo lo permite (req. 9)
		virtual Proyectil^ Disparar(OrigenProyectil origen) {
			if (!activo || cooldownDisparo > 0) return nullptr;

			cooldownDisparo = (framesDisparoBonus > 0) ? cooldownMaximo / 2 : cooldownMaximo;

			int cx = x + TAM / 2 - Proyectil::TAMANO / 2;
			int cy = y + TAM / 2 - Proyectil::TAMANO / 2;
			int velProyectil = 6;

			switch (direccion) {
			case Direccion::Arriba: cy = y - Proyectil::TAMANO; break;
			case Direccion::Abajo: cy = y + TAM; break;
			case Direccion::Izquierda: cx = x - Proyectil::TAMANO; break;
			case Direccion::Derecha: cx = x + TAM; break;
			}

			return gcnew Proyectil(cx, cy, direccion, origen, velProyectil);
		}

		// Aplica el dano de un impacto salvo que el tanque tenga blindaje activo (req. 10, 11)
		virtual void RecibirImpacto(int dano) {
			if (framesEscudoBonus > 0) return;
			vidas -= dano;
			if (vidas <= 0) {
				vidas = 0;
				activo = false;
			}
		}

		// --- Efectos temporales otorgados por PowerUps (req. 18) ---
		void AplicarBonusVelocidad(int frames) { velocidadBonus = 2; framesVelocidadBonus = frames; }
		void AplicarBonusDisparo(int frames) { framesDisparoBonus = frames; }
		void AplicarEscudo(int frames) { framesEscudoBonus = frames; }
		void GanarVida() { vidas++; }

		virtual void Actualizar() override {
			if (cooldownDisparo > 0) cooldownDisparo--;

			if (framesVelocidadBonus > 0) {
				framesVelocidadBonus--;
				if (framesVelocidadBonus == 0) velocidadBonus = 0;
			}
			if (framesDisparoBonus > 0) framesDisparoBonus--;
			if (framesEscudoBonus > 0) framesEscudoBonus--;
		}

		// Dibujar(Graphics^) sigue sin implementarse: cada subclase de Tanque
		// (Jugador / Enemigo) define su propia apariencia.
	};
}
