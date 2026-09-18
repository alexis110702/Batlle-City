#include "Controladora.h"

using namespace Battle;
using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

Controladora::Controladora() {
	estado = gcnew EstadoJuego();
	mapa = gcnew Mapa(estado->Nivel);
}

// Inicializa una nueva partida: mapa limpio y estado en cero (req. 2)
void Controladora::Iniciar() {
	estado = gcnew EstadoJuego();
	mapa = gcnew Mapa(estado->Nivel);
}

// Ciclo principal del juego: actualiza entidades y verifica fin de partida (req. 2, 13, 20)
void Controladora::ActualizarCicloDeJuego() {
	if (estado->JuegoTerminado()) return;

	mapa->Actualizar(estado);

	if (!mapa->Jugador->Activo) {
		estado->DeclararDerrota();
		return;
	}

	if (mapa->VerificarVictoria()) {
		estado->DeclararVictoria();
	}
}

// Traduce las teclas del usuario en comandos de movimiento y disparo (req. 7)
void Controladora::ProcesarTecla(Keys tecla) {
	if (estado->JuegoTerminado()) return;

	switch (tecla) {
	case Keys::Up:    mapa->ProcesarMovimientoJugador(Direccion::Arriba); break;
	case Keys::Down:  mapa->ProcesarMovimientoJugador(Direccion::Abajo); break;
	case Keys::Left:  mapa->ProcesarMovimientoJugador(Direccion::Izquierda); break;
	case Keys::Right: mapa->ProcesarMovimientoJugador(Direccion::Derecha); break;
	case Keys::Space: mapa->ProcesarDisparoJugador(); break;
	}
}

void Controladora::Dibujar(Graphics^ g) {
	mapa->Dibujar(g);

	String^ textoNivel = "Nivel: " + estado->Nivel.ToString();
	String^ textoPuntos = "Puntos: " + estado->Puntuacion.ToString();
	String^ textoEnemigos = "Enemigos: " + mapa->Enemigos->Count.ToString() + " / " + mapa->EnemigosTotales.ToString();
	String^ textoVidas = "Vidas: " + mapa->Jugador->Vidas.ToString();
	String^ textoAyuda = "Flechas: mover   Espacio: disparar";

	Font^ fuente = gcnew Font("Consolas", 11);
	int panelX = Constantes::ANCHO_MAPA + 10;
	g->DrawString(textoNivel, fuente, Brushes::White, (float)panelX, 10.0f);
	g->DrawString(textoPuntos, fuente, Brushes::White, (float)panelX, 35.0f);
	g->DrawString(textoEnemigos, fuente, Brushes::White, (float)panelX, 60.0f);
	g->DrawString(textoVidas, fuente, Brushes::White, (float)panelX, 85.0f);
	g->DrawString(textoAyuda, gcnew Font("Consolas", 9), Brushes::Gray, 5.0f, (float)(Constantes::ALTO_MAPA + 2));

	if (estado->Resultado == ResultadoJuego::Victoria) {
		g->DrawString("VICTORIA", gcnew Font("Arial", 28, FontStyle::Bold), Brushes::LimeGreen, 60.0f, (float)(Constantes::ALTO_MAPA / 2 - 20));
	}
	else if (estado->Resultado == ResultadoJuego::Derrota) {
		g->DrawString("DERROTA", gcnew Font("Arial", 28, FontStyle::Bold), Brushes::Red, 70.0f, (float)(Constantes::ALTO_MAPA / 2 - 20));
	}

	if (estado->JuegoTerminado()) {
		g->DrawString("Presiona ENTER para reiniciar", gcnew Font("Consolas", 11), Brushes::White,
			40.0f, (float)(Constantes::ALTO_MAPA / 2 + 25));
	}
}

void Controladora::SubirDeNivel() {
	int siguienteNivel = estado->Nivel + 1;
	estado = gcnew EstadoJuego();
	estado->Nivel = siguienteNivel;
	mapa = gcnew Mapa(estado->Nivel);
}
