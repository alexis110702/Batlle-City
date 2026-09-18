#pragma once

namespace Battle {

	// Direccion de movimiento de tanques y proyectiles
	public enum class Direccion { Arriba, Abajo, Izquierda, Derecha };

	// Tipos de mejora que puede otorgar un PowerUp (req. 17, 18)
	public enum class TipoPowerUp { Velocidad, Blindaje, PoderDisparo, VidaExtra };

	// Tipos de tanque enemigo (afecta velocidad y vidas)
	public enum class TipoEnemigo { Basico, Rapido, Blindado };

	// Quien disparo el proyectil (para evitar fuego amigo)
	public enum class OrigenProyectil { Jugador, Enemigo };

	// Resultado de la partida (req. 13, 20)
	public enum class ResultadoJuego { EnCurso, Victoria, Derrota };

	// Clase estatica con las dimensiones del mapa (cuadricula de celdas, req. 1)
	public ref class Constantes abstract sealed {
	public:
		static const int TAM_CELDA = 32;
		static const int COLUMNAS = 15;
		static const int FILAS = 15;
		static const int ANCHO_MAPA = COLUMNAS * TAM_CELDA;
		static const int ALTO_MAPA = FILAS * TAM_CELDA;
	};
}
