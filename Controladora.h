#pragma once
#include "Mapa.h"
#include "EstadoJuego.h"

namespace Battle {

	using namespace System;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;

	/// <summary>
	/// Administra el ciclo principal del juego: inicializacion del mapa,
	/// actualizacion del estado de las entidades y verificacion de las
	/// condiciones de victoria o derrota (req. 2).
	/// </summary>
	public ref class Controladora {
	private:
		Mapa^ mapa;
		EstadoJuego^ estado;

	public:
		Controladora();

		property EstadoJuego^ Estado { EstadoJuego^ get() { return estado; } }
		property Mapa^ MapaActual { Mapa^ get() { return mapa; } }

		void Iniciar();
		void ActualizarCicloDeJuego();
		void ProcesarTecla(Keys tecla);
		void Dibujar(Graphics^ g);
		void SubirDeNivel();
	};
}
