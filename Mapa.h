#pragma once
#include "Comun.h"
#include "Celda.h"
#include "Bloque.h"
#include "BloqueDestructible.h"
#include "BloqueIndestructible.h"
#include "TanqueJugador.h"
#include "TanqueEnemigo.h"
#include "Proyectil.h"
#include "PowerUp.h"
#include "BaseJuego.h"
#include "EstadoJuego.h"

namespace Battle {

	using namespace System;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Mapa bidimensional organizado en una cuadricula de celdas (req. 1, 3).
	/// Administra todas las entidades presentes (tanques, bloques,
	/// proyectiles, powerups y la base) y las colisiones entre ellas (req. 10).
	/// </summary>
	public ref class Mapa {
	private:
		int filas, columnas;
		array<Celda^, 2>^ celdas;

		TanqueJugador^ jugador;
		List<TanqueEnemigo^>^ enemigos;
		List<Bloque^>^ bloques;
		List<Proyectil^>^ proyectiles;
		List<PowerUp^>^ powerups;
		BaseJuego^ baseJuego;

		Random^ rnd;

		int enemigosGenerados;
		int enemigosTotales;
		int enemigosMaximosSimultaneos;
		int contadorGeneracion;
		int contadorPowerUp;

		array<int>^ columnasSpawnEnemigo;

	public:
		Mapa(int nivel) {
			filas = Constantes::FILAS;
			columnas = Constantes::COLUMNAS;
			celdas = gcnew array<Celda^, 2>(filas, columnas);

			enemigos = gcnew List<TanqueEnemigo^>();
			bloques = gcnew List<Bloque^>();
			proyectiles = gcnew List<Proyectil^>();
			powerups = gcnew List<PowerUp^>();

			rnd = gcnew Random();

			enemigosGenerados = 0;
			enemigosTotales = 6 + (nivel - 1) * 2;
			enemigosMaximosSimultaneos = (nivel > 2) ? 4 : 3;
			contadorGeneracion = 60;
			contadorPowerUp = 500;

			columnasSpawnEnemigo = gcnew array<int> { 1, 7, 13 };

			InicializarMapa();
		}

		property TanqueJugador^ Jugador { TanqueJugador^ get() { return jugador; } }
		property List<TanqueEnemigo^>^ Enemigos { List<TanqueEnemigo^>^ get() { return enemigos; } }
		property List<Bloque^>^ Bloques { List<Bloque^>^ get() { return bloques; } }
		property List<Proyectil^>^ Proyectiles { List<Proyectil^>^ get() { return proyectiles; } }
		property List<PowerUp^>^ PowerUps { List<PowerUp^>^ get() { return powerups; } }
		property BaseJuego^ Base { BaseJuego^ get() { return baseJuego; } }
		property int EnemigosGenerados { int get() { return enemigosGenerados; } }
		property int EnemigosTotales { int get() { return enemigosTotales; } }

		// Construye la disposicion inicial: celdas, bloques, base y jugador (req. 1, 3)
		void InicializarMapa() {
			for (int f = 0; f < filas; f++)
				for (int c = 0; c < columnas; c++)
					celdas[f, c] = gcnew Celda(f, c);

			int columnaBase = columnas / 2;
			baseJuego = gcnew BaseJuego(celdas[filas - 1, columnaBase]->PixelX, celdas[filas - 1, columnaBase]->PixelY);

			// Muros de ladrillo protegiendo la base
			bloques->Add(gcnew BloqueDestructible(celdas[filas - 2, columnaBase - 1]->PixelX, celdas[filas - 2, columnaBase - 1]->PixelY, 2));
			bloques->Add(gcnew BloqueDestructible(celdas[filas - 2, columnaBase]->PixelX, celdas[filas - 2, columnaBase]->PixelY, 2));
			bloques->Add(gcnew BloqueDestructible(celdas[filas - 2, columnaBase + 1]->PixelX, celdas[filas - 2, columnaBase + 1]->PixelY, 2));
			bloques->Add(gcnew BloqueDestructible(celdas[filas - 1, columnaBase - 1]->PixelX, celdas[filas - 1, columnaBase - 1]->PixelY, 2));
			bloques->Add(gcnew BloqueDestructible(celdas[filas - 1, columnaBase + 1]->PixelX, celdas[filas - 1, columnaBase + 1]->PixelY, 2));

			// Bloques de acero indestructibles dispersos (req. 16)
			for (int i = 0; i < columnas; i += 4) {
				bloques->Add(gcnew BloqueIndestructible(celdas[3, i]->PixelX, celdas[3, i]->PixelY));
				bloques->Add(gcnew BloqueIndestructible(celdas[9, (i + 2) % columnas]->PixelX, celdas[9, (i + 2) % columnas]->PixelY));
			}

			// Grupos de ladrillo destructible dispersos por el mapa (req. 15)
			for (int f = 5; f < filas - 4; f += 3) {
				for (int c = 2; c < columnas - 2; c += 5) {
					bloques->Add(gcnew BloqueDestructible(celdas[f, c]->PixelX, celdas[f, c]->PixelY, 1));
					bloques->Add(gcnew BloqueDestructible(celdas[f, c + 1]->PixelX, celdas[f, c + 1]->PixelY, 1));
				}
			}

			jugador = gcnew TanqueJugador(celdas[filas - 1, 1]->PixelX, celdas[filas - 1, 1]->PixelY);
		}

		bool DentroDeLimites(Rectangle zona) {
			return zona.X >= 0 && zona.Y >= 0 &&
				zona.X + zona.Width <= Constantes::ANCHO_MAPA &&
				zona.Y + zona.Height <= Constantes::ALTO_MAPA;
		}

		bool ColisionaConBloques(Rectangle zona) {
			for each (Bloque ^ b in bloques)
				if (b->Activo && b->GetBounds().IntersectsWith(zona)) return true;
			return false;
		}

		bool ColisionaConTanques(Rectangle zona, Object^ propio) {
			if (jugador->Activo && (Object^)jugador != propio && jugador->GetBounds().IntersectsWith(zona)) return true;
			for each (TanqueEnemigo ^ e in enemigos)
				if (e->Activo && (Object^)e != propio && e->GetBounds().IntersectsWith(zona)) return true;
			return false;
		}

		bool ColisionaConAlgo(Rectangle zona, Object^ propio) {
			if (baseJuego->Activo && baseJuego->GetBounds().IntersectsWith(zona)) return true;
			if (ColisionaConBloques(zona)) return true;
			if (ColisionaConTanques(zona, propio)) return true;
			return false;
		}

		// Intenta mover un tanque; si el destino colisiona, se revierte el movimiento (req. 10, 14)
		void IntentarMover(Tanque^ t, Direccion dir) {
			if (!t->Activo) return;
			t->Mover(dir);
			Rectangle destino = t->GetBounds();
			if (!DentroDeLimites(destino) || ColisionaConAlgo(destino, t)) {
				t->Retroceder(dir);
			}
		}

		void ProcesarMovimientoJugador(Direccion dir) {
			IntentarMover(jugador, dir);
		}

		void ProcesarDisparoJugador() {
			Proyectil^ p = jugador->ProcesarComandoDisparo();
			if (p != nullptr) proyectiles->Add(p);
		}

		// Genera tanques enemigos de forma progresiva hasta el limite total (req. 19)
		void GenerarEnemigoSiCorresponde() {
			if (enemigosGenerados >= enemigosTotales) return;

			int activos = 0;
			for each (TanqueEnemigo ^ e in enemigos) if (e->Activo) activos++;
			if (activos >= enemigosMaximosSimultaneos) return;

			contadorGeneracion--;
			if (contadorGeneracion > 0) return;
			contadorGeneracion = 90;

			int col = columnasSpawnEnemigo[rnd->Next(columnasSpawnEnemigo->Length)];
			int px = celdas[0, col]->PixelX;
			int py = celdas[0, col]->PixelY;

			TipoEnemigo tipo = TipoEnemigo::Basico;
			int n = rnd->Next(100);
			if (n < 15) tipo = TipoEnemigo::Blindado;
			else if (n < 45) tipo = TipoEnemigo::Rapido;

			TanqueEnemigo^ nuevo = gcnew TanqueEnemigo(px, py, tipo);
			if (!ColisionaConAlgo(nuevo->GetBounds(), nullptr)) {
				enemigos->Add(nuevo);
				enemigosGenerados++;
			}
		}

		// Genera powerups de forma ocasional en celdas libres (req. 17)
		void GenerarPowerUpSiCorresponde() {
			contadorPowerUp--;
			if (contadorPowerUp > 0) return;
			contadorPowerUp = 400 + rnd->Next(300);

			int f = rnd->Next(1, filas - 1);
			int c = rnd->Next(1, columnas - 1);
			int px = celdas[f, c]->PixelX;
			int py = celdas[f, c]->PixelY;
			Rectangle zona(px, py, Constantes::TAM_CELDA, Constantes::TAM_CELDA);
			if (ColisionaConAlgo(zona, nullptr)) return;

			array<TipoPowerUp>^ tipos = gcnew array<TipoPowerUp> {
				TipoPowerUp::Velocidad, TipoPowerUp::Blindaje, TipoPowerUp::PoderDisparo, TipoPowerUp::VidaExtra
			};
			TipoPowerUp tipo = tipos[rnd->Next(tipos->Length)];
			powerups->Add(gcnew PowerUp(px, py, tipo));
		}

		void LimpiarInactivos() {
			for (int i = proyectiles->Count - 1; i >= 0; i--)
				if (!proyectiles[i]->Activo) proyectiles->RemoveAt(i);

			for (int i = powerups->Count - 1; i >= 0; i--)
				if (!powerups[i]->Activo) powerups->RemoveAt(i);

			for (int i = bloques->Count - 1; i >= 0; i--)
				if (!bloques[i]->Activo) bloques->RemoveAt(i);

			for (int i = enemigos->Count - 1; i >= 0; i--)
				if (!enemigos[i]->Activo) enemigos->RemoveAt(i);
		}

		// Actualiza el estado de todas las entidades del mapa en cada ciclo (req. 2, 10, 11)
		void Actualizar(EstadoJuego^ estado) {
			if (jugador->Activo) jugador->Actualizar();

			// --- Tanques enemigos: movimiento automatico y disparo (req. 8) ---
			for each (TanqueEnemigo ^ e in enemigos) {
				if (!e->Activo) continue;
				e->Actualizar();
				e->ActualizarComportamiento();
				IntentarMover(e, e->Direc);

				// Un tanque enemigo que choca contra la base tambien la destruye (req. 13)
				if (baseJuego->Activo && e->Interactuar(baseJuego)) {
					baseJuego->RecibirImpacto();
					estado->DeclararDerrota();
				}

				Proyectil^ p = e->IntentarDisparar();
				if (p != nullptr) proyectiles->Add(p);
			}

			// --- Proyectiles: movimiento y colisiones (req. 9, 10, 11) ---
			for each (Proyectil ^ p in proyectiles) {
				if (!p->Activo) continue;
				p->Actualizar();
				if (!p->Activo) continue; // salio de los limites del mapa

				bool impacto = false;

				for each (Bloque ^ b in bloques) {
					if (b->Activo && p->Interactuar(b)) {
						b->RecibirImpacto();
						impacto = true;
						break;
					}
				}

				if (!impacto && baseJuego->Activo && p->Interactuar(baseJuego)) {
					baseJuego->RecibirImpacto();
					estado->DeclararDerrota();
					impacto = true;
				}

				if (!impacto && p->Origen == OrigenProyectil::Enemigo &&
					jugador->Activo && p->Interactuar(jugador)) {
					jugador->RecibirImpacto(p->Dano);
					impacto = true;
				}

				if (!impacto && p->Origen == OrigenProyectil::Jugador) {
					for each (TanqueEnemigo ^ e in enemigos) {
						if (e->Activo && p->Interactuar(e)) {
							e->RecibirImpacto(p->Dano);
							if (!e->Activo) estado->SumarPuntos(100);
							impacto = true;
							break;
						}
					}
				}

				if (impacto) p->Activo = false;
			}

			// --- PowerUps: recoleccion por el jugador (req. 17, 18) ---
			for each (PowerUp ^ pu in powerups) {
				if (!pu->Activo) continue;
				pu->Actualizar();
				if (pu->Activo && jugador->Activo && pu->Interactuar(jugador)) {
					pu->AplicarEfecto(jugador);
				}
			}

			GenerarEnemigoSiCorresponde();
			GenerarPowerUpSiCorresponde();
			LimpiarInactivos();
		}

		// Todos los enemigos destruidos y base intacta => victoria (req. 20)
		bool VerificarVictoria() {
			return baseJuego->Activo && enemigosGenerados >= enemigosTotales && enemigos->Count == 0;
		}

		void Dibujar(Graphics^ g) {
			g->Clear(Color::Black);
			for each (Bloque ^ b in bloques) b->Dibujar(g);
			if (baseJuego->Activo) baseJuego->Dibujar(g);
			for each (PowerUp ^ pu in powerups) pu->Dibujar(g);
			if (jugador->Activo) jugador->Dibujar(g);
			for each (TanqueEnemigo ^ e in enemigos) if (e->Activo) e->Dibujar(g);
			for each (Proyectil ^ p in proyectiles) if (p->Activo) p->Dibujar(g);
		}
	};
}
