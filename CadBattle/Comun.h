#pragma once
// ============================================================
//  CAPA DE DATOS (CadBattle) - Comun.h
//  PASO 1: constantes (filas, columnas, tamano de imagen) y enumeraciones
//           (ETipoBloque, EDireccion)
// ============================================================
#pragma once
#define MAX_FILAS 11
#define MAX_COLUMNAS 13
#define MAX_NIVELES 5

#define ANCHO_IMAGEN 64
#define ALTO_IMAGEN 64

enum ETipoBloque {
	piso = 1,
	destruible,
	noDestruible,
	agua,
	arbol,
	trofeo
};

enum EDireccion {
	ninguno,
	arriba,
	abajo,
	izquierda,
	derecha
};
