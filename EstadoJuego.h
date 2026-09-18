#pragma once
#include "Comun.h"

namespace Battle {

	/// <summary>
	/// Informacion global de la partida: nivel actual, puntuacion
	/// acumulada y resultado (victoria/derrota/en curso).
	/// </summary>
	public ref class EstadoJuego {
	private:
		int nivel;
		int puntuacion;
		ResultadoJuego resultado;

	public:
		EstadoJuego() : nivel(1), puntuacion(0), resultado(ResultadoJuego::EnCurso) {}

		property int Nivel { int get() { return nivel; } void set(int v) { nivel = v; } }
		property int Puntuacion { int get() { return puntuacion; } }
		property ResultadoJuego Resultado { ResultadoJuego get() { return resultado; } }

		void SumarPuntos(int puntos) { puntuacion += puntos; }

		// El juego finaliza con victoria si se destruyen todos los enemigos
		// y la base permanece intacta (req. 20)
		void DeclararVictoria() { if (resultado == ResultadoJuego::EnCurso) resultado = ResultadoJuego::Victoria; }

		// El juego finaliza si la base es destruida o el jugador pierde todas sus vidas (req. 13)
		void DeclararDerrota() { resultado = ResultadoJuego::Derrota; }

		bool JuegoTerminado() { return resultado != ResultadoJuego::EnCurso; }
	};
}
