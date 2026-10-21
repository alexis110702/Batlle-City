# Battle City en 3 capas: guia paso a paso

Esta guia te lleva a resolver las tareas del docente (a, b, c, d) en tu proyecto de 3 capas. Abre la solucion **vacia** (`Battle3Capas_vacio.zip`). Cada archivo trae un comentario `// PASO N` que indica que escribir. La carpeta `Battle3Capas_resuelto.zip` es solo para comparar.

## Las tareas del docente

- **a)** Crear los niveles 2, 3, 4 y 5 (segun `imagenes/nivel-2..5.png`).
- **b)** Crear el Jugador y el Enemigo en la clase Controladora.
- **c)** Cargar y dibujar el Jugador y UN Enemigo en el mapa con `tanques.png`.
- **d)** Separar la funcionalidad de (c) en sus clases (responsabilidades).

## Donde va cada cosa (resumen)

| Punto | Capa | Archivos |
|---|---|---|
| a) Niveles 2 a 5 | Cad (datos) + Cln (logica) | `CadBattle/NivelCad.*` (matrices), `ClnBattle/MapaCln.*` (cargar), `CadBattle/Mapa.*` |
| b) Jugador y Enemigo en Controladora | Cad (clases) + Cln | `CadBattle/Tanque|Jugador|Enemigo.*`, `ClnBattle/Controladora.*` |
| c) Cargar y dibujar tanques | Cp (presentacion) | `CpBattle/Juego.h`, `DibujoTanques.*` |
| d) Responsabilidades | las 3 capas | datos en Cad, reglas en Cln, dibujo en Cp (nada de `Graphics` fuera de Cp) |

**Regla de oro:** Cad solo guarda datos, Cln decide la logica, Cp dibuja. Por eso el dibujo (`Graphics^`, `Bitmap^`) esta solo en CpBattle.

## Antes de empezar

1. Abre `Battle.sln` en Visual Studio 2026. Compila una vez: debe compilar vacio sin errores.
2. Orden de compilacion: CadBattle, ClnBattle, CpBattle (la solucion ya tiene las dependencias).
3. La carpeta `CpBattle/imagenes` ya trae los PNG del docente; un post-build la copia junto al .exe.

## Paso 1: Comun.h

**Capa:** CadBattle | **Que hace:** Constantes compartidas (tamano de bloque, filas/columnas, niveles) | **Corresponde a:** Base de a, b y c

**`CadBattle/Comun.h`**

```cpp
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
```

Compila (Ctrl+Shift+B) antes de pasar al siguiente paso.

## Paso 2: Bloque

**Capa:** CadBattle | **Que hace:** Clase CBloque (tipo, durabilidad, posicion) | **Corresponde a:** Base de a

**`CadBattle/Bloque.h`**

```cpp
#pragma once
#include "Comun.h"

class CBloque {
	ETipoBloque tipo;
	short durabilidad;

public:
	CBloque(ETipoBloque tipo, int durabilidad);
	~CBloque();

	ETipoBloque getTipo();
	void setDurabilidad(short durabilidad);
	short getDurabilidad();
};
```

**`CadBattle/Bloque.cpp`**

```cpp
#include "Bloque.h"

CBloque::CBloque(ETipoBloque tipo, int durabilidad) {
	this->tipo = tipo;
	this->durabilidad = durabilidad;
}

CBloque::~CBloque() {}

ETipoBloque CBloque::getTipo() {
	return this->tipo;
}

void CBloque::setDurabilidad(short durabilidad) {
	this->durabilidad = durabilidad;
}

short CBloque::getDurabilidad() {
	return this->durabilidad;
}
```

Compila (Ctrl+Shift+B) antes de pasar al siguiente paso.

## Paso 3: Tanque, Jugador, Enemigo

**Capa:** CadBattle | **Que hace:** Solo DATOS de los tanques: posicion, direccion, tipo | **Corresponde a:** Punto b (clases) y base de c

**`CadBattle/Tanque.h`**

```cpp
#pragma once
#include "Comun.h"

class CTanque {
	short id;
	short vidas;
	EDireccion direccion;
	short velocidad;
	int posX;
	int posY;
public:
	CTanque(short id, int posX, int posY, int vidas);
	~CTanque();
	void setId(short id);
	void setVidas(short vidas);
	void setDireccion(EDireccion direccion);
	void setVelocidad(short velocidad);
	void setX(int posX);
	void setY(int posY);

	short getId();
	short getVidas();
	EDireccion getDireccion();
	short getVelocidad();
	int getX();
	int getY();
};
```

**`CadBattle/Tanque.cpp`**

```cpp
#include "Tanque.h"

CTanque::CTanque(short id, int posX, int posY, int vidas) {
	this->id = id;
	this->vidas = vidas;
	this->direccion = EDireccion::arriba;
	this->velocidad = 10;
	this->posX = posX;
	this->posY = posY;
}

CTanque::~CTanque() {}

void CTanque::setId(short id) {
	this->id = id;
}
void CTanque::setVidas(short vidas) {
	this->vidas = vidas;
}
void CTanque::setDireccion(EDireccion direccion) {
	this->direccion = direccion;
}
void CTanque::setVelocidad(short velocidad) {
	this->velocidad = velocidad;
}
void CTanque::setX(int posX) {
	this->posX = posX;
}
void CTanque::setY(int posY) {
	this->posY = posY;
}

short CTanque::getId() {
	return this->id;
}
short CTanque::getVidas() {
	return this->vidas;
}
EDireccion CTanque::getDireccion() {
	return this->direccion;
}
short CTanque::getVelocidad() {
	return this->velocidad;
}
int CTanque::getX() {
	return this->posX;
}
int CTanque::getY() {
	return this->posY;
}
```

**`CadBattle/Jugador.h`**

```cpp
#pragma once
#include <string>
#include "Tanque.h"

class CJugador: public CTanque {
	std::string nombre;
	int puntuacion;
public:
	CJugador(short id, int posX, int posY, int vidas);
	void setNombre(std::string nombre);
	void setPuntuacion(int puntuacion);
	std::string getNombre();
	int getPuntuacion();
};
```

**`CadBattle/Jugador.cpp`**

```cpp
#include "Jugador.h"

CJugador::CJugador(short id, int posX, int posY, int vidas) : CTanque(id, posX, posY, vidas) {
	this->nombre = "";
	this->puntuacion = 0;
	this->setDireccion(EDireccion::arriba);
}

void CJugador::setNombre(std::string nombre) {
	this->nombre = nombre;
}
void CJugador::setPuntuacion(int puntuacion) {
	this->puntuacion = puntuacion;
}
std::string CJugador::getNombre() {
	return this->nombre;
}
int CJugador::getPuntuacion() {
	return this->puntuacion;
}
```

**`CadBattle/Enemigo.h`**

```cpp
#pragma once
#include "Tanque.h"

enum ETipoTanque {
	tipo1,
	tipo2,
	tipo3,
	tipo4,
	tipo5
};

class CEnemigo: public CTanque {
	ETipoTanque tipo;
public:
	CEnemigo(short id, short tipo, int posx, int posy, int vidas);
	void setTipo(ETipoTanque tipo);
	ETipoTanque getTipo();
};
```

**`CadBattle/Enemigo.cpp`**

```cpp
#include "Enemigo.h"

CEnemigo::CEnemigo(short id, short tipo, int posx, int posy, int vidas) : CTanque(id, posx, posy, vidas) {
	this->tipo = static_cast<ETipoTanque>(tipo);
	this->setDireccion(EDireccion::abajo);
}

void CEnemigo::setTipo(ETipoTanque tipo) {
	this->tipo = tipo;
}
ETipoTanque CEnemigo::getTipo() {
	return this->tipo;
}
```

Compila (Ctrl+Shift+B) antes de pasar al siguiente paso.

## Paso 4: Mapa

**Capa:** CadBattle | **Que hace:** CMapa: matriz de CBloque* con setBloque/getBloque | **Corresponde a:** Base de a

**`CadBattle/Mapa.h`**

```cpp
#pragma once
#include "Bloque.h"

class CMapa {
	CBloque* mapa[MAX_FILAS][MAX_COLUMNAS];
	int nivel;
public:
	CMapa();
	~CMapa();
	void setNivel(int nivel);
	int getNivel();
	CBloque* getBloque(int i, int j);
	void setBloque(int i, int j, CBloque* bloque);
};
```

**`CadBattle/Mapa.cpp`**

```cpp
#include "Mapa.h"

CMapa::CMapa() {
	for (int i = 0; i < MAX_FILAS; i++) {
		for (int j = 0; j < MAX_COLUMNAS; j++) {
			mapa[i][j] = nullptr;
		}
	}
	this->nivel = 1;
}

CMapa::~CMapa() {
	for (int i = 0; i < MAX_FILAS; i++) {
		for (int j = 0; j < MAX_COLUMNAS; j++) {
			delete mapa[i][j];
		}
	}
}

void CMapa::setNivel(int nivel) {
	this->nivel = nivel;
}

int CMapa::getNivel() {
	return this->nivel;
}

CBloque* CMapa::getBloque(int i, int j) {
	return mapa[i][j];
}

// Guarda un bloque en la celda (i, j); si ya habia uno (de otro nivel) lo libera
void CMapa::setBloque(int i, int j, CBloque* bloque) {
	delete mapa[i][j];
	mapa[i][j] = bloque;
}
```

Compila (Ctrl+Shift+B) antes de pasar al siguiente paso.

## Paso 5: NivelCad (matrices de los 5 niveles)

**Capa:** CadBattle | **Que hace:** Los datos de los niveles 1 a 5 (11 filas x 13 columnas) | **Corresponde a:** PUNTO a (datos)

**`CadBattle/NivelCad.h`**

```cpp
#pragma once
#include "Comun.h"

// Origen de los datos de los niveles: las matrices de numeros
// 1 piso, 2 destruible, 3 no destruible, 4 agua, 5 arbol, 9 trofeo (base)
class CNivelCad {
public:
	static void Obtener(int nivel, int matriz[MAX_FILAS][MAX_COLUMNAS]);
};
```

**`CadBattle/NivelCad.cpp`**

```cpp
#include "NivelCad.h"

void CNivelCad::Obtener(int nivel, int matriz[MAX_FILAS][MAX_COLUMNAS]) {
	// Nivel 1: el del docente. Niveles 2 a 5: tomados de imagenes/nivel-2.png ... nivel-5.png
	static const int niveles[MAX_NIVELES][MAX_FILAS][MAX_COLUMNAS] = {
		// Nivel 1
		{
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 2, 1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1 },
			{ 1, 2, 1, 2, 1, 3, 1, 2, 1, 2, 1, 2, 1 },
			{ 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1 },
			{ 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1 },
			{ 1, 1, 2, 2, 2, 1, 2, 1, 1, 1, 1, 2, 1 },
			{ 1, 1, 3, 1, 1, 1, 2, 1, 1, 2, 1, 3, 1 },
			{ 1, 1, 2, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 2, 2, 2, 1, 3, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 2, 9, 2, 1, 1, 1, 1, 1 }
		},
		// Nivel 2
		{
			{ 1, 1, 2, 1, 2, 3, 1, 1, 3, 3, 3, 1, 1 },
			{ 3, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1 },
			{ 2, 1, 2, 2, 2, 1, 2, 2, 1, 4, 4, 1, 4 },
			{ 1, 1, 2, 1, 4, 4, 1, 4, 4, 4, 1, 2, 2 },
			{ 2, 2, 1, 1, 4, 2, 1, 2, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 3, 3, 1 },
			{ 4, 4, 4, 1, 4, 1, 3, 1, 2, 1, 3, 1, 1 },
			{ 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 3, 2, 2 },
			{ 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1 },
			{ 2, 2, 1, 1, 1, 2, 2, 2, 1, 1, 2, 1, 1 },
			{ 1, 1, 1, 1, 1, 2, 9, 2, 1, 1, 1, 1, 1 }
		},
		// Nivel 3
		{
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1 },
			{ 5, 5, 1, 1, 1, 2, 2, 2, 1, 1, 1, 5, 5 },
			{ 5, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 5 },
			{ 1, 1, 1, 2, 2, 5, 2, 5, 2, 2, 1, 1, 1 },
			{ 1, 1, 1, 2, 5, 5, 2, 5, 5, 2, 1, 1, 1 },
			{ 5, 1, 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 5 },
			{ 5, 5, 1, 1, 2, 5, 2, 5, 2, 1, 1, 5, 5 },
			{ 4, 4, 4, 1, 2, 2, 2, 2, 2, 1, 4, 4, 4 },
			{ 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3 },
			{ 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1 },
			{ 3, 3, 3, 3, 1, 2, 9, 2, 1, 3, 3, 3, 3 }
		},
		// Nivel 4
		{
			{ 1, 5, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 5 },
			{ 5, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 3 },
			{ 3, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1 },
			{ 4, 1, 1, 1, 3, 1, 3, 1, 2, 1, 1, 1, 1 },
			{ 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 4, 4 },
			{ 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1 },
			{ 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1 },
			{ 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1 },
			{ 1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 5 },
			{ 5, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 5, 5 },
			{ 3, 5, 1, 1, 1, 2, 9, 2, 1, 1, 5, 5, 3 }
		},
		// Nivel 5
		{
			{ 1, 2, 2, 1, 1, 1, 2, 2, 2, 2, 1, 1, 2 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1 },
			{ 1, 4, 4, 2, 2, 4, 4, 4, 4, 3, 3, 4, 4 },
			{ 1, 4, 4, 2, 2, 4, 4, 4, 4, 3, 3, 4, 4 },
			{ 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1 },
			{ 1, 2, 1, 2, 2, 1, 1, 1, 2, 2, 2, 2, 2 },
			{ 1, 2, 1, 2, 2, 2, 1, 1, 2, 1, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 2, 2, 2 },
			{ 1, 2, 2, 2, 3, 1, 1, 2, 2, 1, 2, 2, 3 },
			{ 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 2, 1, 1 },
			{ 1, 1, 2, 1, 1, 2, 9, 2, 1, 1, 2, 1, 1 }
		}
	};

	if (nivel < 1 || nivel > MAX_NIVELES) nivel = 1;
	for (int i = 0; i < MAX_FILAS; i++) {
		for (int j = 0; j < MAX_COLUMNAS; j++) {
			matriz[i][j] = niveles[nivel - 1][i][j];
		}
	}
}
```

Compila (Ctrl+Shift+B) antes de pasar al siguiente paso.

## Paso 6: MapaCln (cargar nivel)

**Capa:** ClnBattle | **Que hace:** Convierte la matriz de codigos en bloques del CMapa | **Corresponde a:** PUNTO a (logica)

**`ClnBattle/MapaCln.h`**

```cpp
#pragma once
#include "Mapa.h"

// Regla de negocio: convertir la matriz numerica de un nivel en bloques del mapa
class CMapaCln {
public:
	static void CargarNivel(CMapa* mapa, int nivel);
private:
	static CBloque* CrearBloque(int codigo);
};
```

**`ClnBattle/MapaCln.cpp`**

```cpp
#include "MapaCln.h"
#include "NivelCad.h"

CBloque* CMapaCln::CrearBloque(int codigo) {
	switch (codigo) {
	case 2:
		return new CBloque(ETipoBloque::destruible, 2);
	case 3:
		return new CBloque(ETipoBloque::noDestruible, -1);
	case 4:
		return new CBloque(ETipoBloque::agua, -1);
	case 5:
		return new CBloque(ETipoBloque::arbol, -1);
	case 9:
		return new CBloque(ETipoBloque::trofeo, 1);
	default:
		return new CBloque(ETipoBloque::piso, 0);
	}
}

void CMapaCln::CargarNivel(CMapa* mapa, int nivel) {
	int matriz[MAX_FILAS][MAX_COLUMNAS];
	CNivelCad::Obtener(nivel, matriz);

	for (int i = 0; i < MAX_FILAS; i++) {
		for (int j = 0; j < MAX_COLUMNAS; j++) {
			mapa->setBloque(i, j, CrearBloque(matriz[i][j]));
		}
	}
	mapa->setNivel(nivel);
}
```

Compila (Ctrl+Shift+B) antes de pasar al siguiente paso.

## Paso 7: Controladora

**Capa:** ClnBattle | **Que hace:** Crea CMapa, CJugador y CEnemigo y permite CambiarNivel | **Corresponde a:** PUNTO b

**`ClnBattle/Controladora.h`**

```cpp
#pragma once
#include "Mapa.h"
#include "Jugador.h"
#include "Enemigo.h"

class CControladora {
private:
	CMapa* mapa;
	CJugador* jugador;
	CEnemigo* enemigo;
	void crearTanques();
public:
	CControladora();
	~CControladora();

	void Inicializar();
	void CambiarNivel(int nivel);

	CMapa* getMapa();
	CJugador* getJugador();
	CEnemigo* getEnemigo();
};
```

**`ClnBattle/Controladora.cpp`**

```cpp
#include "Controladora.h"
#include "MapaCln.h"

CControladora::CControladora() {
	mapa = new CMapa();
	jugador = nullptr;
	enemigo = nullptr;
}

CControladora::~CControladora() {
	delete mapa;
	delete jugador;
	delete enemigo;
}

void CControladora::Inicializar() {
	CambiarNivel(1);
}

void CControladora::CambiarNivel(int nivel) {
	CMapaCln::CargarNivel(mapa, nivel);
	crearTanques();
}

// PUNTO b: la Controladora crea el Jugador y UN Enemigo en sus posiciones iniciales
void CControladora::crearTanques() {
	delete jugador;
	delete enemigo;

	// Jugador: ultima fila, a la izquierda de la base (columna 4)
	jugador = new CJugador(1, 4 * ANCHO_IMAGEN, (MAX_FILAS - 1) * ALTO_IMAGEN, 3);
	// Enemigo tipo 1: esquina superior izquierda
	enemigo = new CEnemigo(1, static_cast<short>(ETipoTanque::tipo1), 0, 0, 1);
}

CMapa* CControladora::getMapa() {
	return mapa;
}

CJugador* CControladora::getJugador() {
	return jugador;
}

CEnemigo* CControladora::getEnemigo() {
	return enemigo;
}
```

Compila (Ctrl+Shift+B) antes de pasar al siguiente paso.

## Paso 8: DibujoMapa

**Capa:** CpBattle | **Que hace:** Dibuja piso, bloques y trofeo recortando los PNG | **Corresponde a:** PUNTO c (mapa) y d

**`CpBattle/DibujoMapa.h`**

```cpp
#pragma once
#include "Mapa.h"

using namespace System::Drawing;

// Presentacion: dibuja el CMapa recortando los sprites de pisos.png, bloques.png y trofeo.png
class CDibujoMapa {
public:
	static void Dibujar(Graphics^ g, CMapa* mapa, Bitmap^ bmpPiso, Bitmap^ bmpBloques, Bitmap^ bmpTrofeo);
};
```

**`CpBattle/DibujoMapa.cpp`**

```cpp
#include "DibujoMapa.h"

void CDibujoMapa::Dibujar(Graphics^ g, CMapa* mapa, Bitmap^ bmpPiso, Bitmap^ bmpBloques, Bitmap^ bmpTrofeo) {
	if (mapa == nullptr) return;

	Rectangle rectPiso = Rectangle(0 * ANCHO_IMAGEN, 0 * ALTO_IMAGEN, ANCHO_IMAGEN, ALTO_IMAGEN);
	Rectangle rectDestruible = Rectangle(1 * ANCHO_IMAGEN, 0 * ALTO_IMAGEN, ANCHO_IMAGEN, ALTO_IMAGEN);
	Rectangle rectNoDestruible = Rectangle(0 * ANCHO_IMAGEN, 1 * ALTO_IMAGEN, ANCHO_IMAGEN, ALTO_IMAGEN);
	Rectangle rectAgua = Rectangle(2 * ANCHO_IMAGEN, 0 * ALTO_IMAGEN, ANCHO_IMAGEN, ALTO_IMAGEN);
	Rectangle rectArbol = Rectangle(1 * ANCHO_IMAGEN, 1 * ALTO_IMAGEN, ANCHO_IMAGEN, ALTO_IMAGEN);
	Rectangle rectTrofeo = Rectangle(0 * ANCHO_IMAGEN, 0 * ALTO_IMAGEN, ANCHO_IMAGEN, ALTO_IMAGEN);

	int X = 0, Y = 0;
	for (int i = 0; i < MAX_FILAS; i++) {
		X = 0;
		for (int j = 0; j < MAX_COLUMNAS; j++) {
			Rectangle destino = Rectangle(X, Y, ANCHO_IMAGEN, ALTO_IMAGEN);
			switch (mapa->getBloque(i, j)->getTipo()) {
			case ETipoBloque::piso:
				g->DrawImage(bmpPiso, destino, rectPiso, GraphicsUnit::Pixel);
				break;
			case ETipoBloque::destruible:
				g->DrawImage(bmpBloques, destino, rectDestruible, GraphicsUnit::Pixel);
				break;
			case ETipoBloque::noDestruible:
				g->DrawImage(bmpBloques, destino, rectNoDestruible, GraphicsUnit::Pixel);
				break;
			case ETipoBloque::agua:
				g->DrawImage(bmpBloques, destino, rectAgua, GraphicsUnit::Pixel);
				break;
			case ETipoBloque::arbol:
				// el arbol tiene fondo transparente: primero se dibuja el piso
				g->DrawImage(bmpPiso, destino, rectPiso, GraphicsUnit::Pixel);
				g->DrawImage(bmpBloques, destino, rectArbol, GraphicsUnit::Pixel);
				break;
			case ETipoBloque::trofeo:
				g->DrawImage(bmpTrofeo, destino, rectTrofeo, GraphicsUnit::Pixel);
				break;
			}
			X += ANCHO_IMAGEN;
		}
		Y += ALTO_IMAGEN;
	}
}
```

Compila (Ctrl+Shift+B) antes de pasar al siguiente paso.

## Paso 9: DibujoTanques

**Capa:** CpBattle | **Que hace:** Dibuja Jugador y UN Enemigo recortando tanques.png | **Corresponde a:** PUNTO c y d (responsabilidades)

**`CpBattle/DibujoTanques.h`**

```cpp
#pragma once
#include "Jugador.h"
#include "Enemigo.h"

using namespace System::Drawing;

// Presentacion: dibuja los tanques con los sprites de tanques.png
class CDibujoTanques {
public:
	static void DibujarJugador(Graphics^ g, CJugador* jugador, Bitmap^ bmpTanques);
	static void DibujarEnemigo(Graphics^ g, CEnemigo* enemigo, Bitmap^ bmpTanques);
private:
	static int OrdenSprite(EDireccion direccion);
	static void DibujarSprite(Graphics^ g, Bitmap^ bmpTanques, int x, int y, int origenX, int origenY);
};
```

**`CpBattle/DibujoTanques.cpp`**

```cpp
#include "DibujoTanques.h"

// En tanques.png cada tanque tiene una fila por direccion, en este orden:
// arriba, derecha, abajo, izquierda
int CDibujoTanques::OrdenSprite(EDireccion direccion) {
	switch (direccion) {
	case EDireccion::arriba:
		return 0;
	case EDireccion::derecha:
		return 1;
	case EDireccion::abajo:
		return 2;
	case EDireccion::izquierda:
		return 3;
	default:
		return 0;
	}
}

// Dibuja en (x, y) el recuadro de 64x64 que empieza en (origenX, origenY) de tanques.png
void CDibujoTanques::DibujarSprite(Graphics^ g, Bitmap^ bmpTanques, int x, int y, int origenX, int origenY) {
	Rectangle origen = Rectangle(origenX, origenY, ANCHO_IMAGEN, ALTO_IMAGEN);
	Rectangle destino = Rectangle(x, y, ANCHO_IMAGEN, ALTO_IMAGEN);
	g->DrawImage(bmpTanques, destino, origen, GraphicsUnit::Pixel);
}

void CDibujoTanques::DibujarJugador(Graphics^ g, CJugador* jugador, Bitmap^ bmpTanques) {
	if (jugador == nullptr) return;
	// Tanque amarillo (primera columna): una fila por direccion
	static const int origenY[4] = { 0, 64, 128, 192 };
	DibujarSprite(g, bmpTanques, jugador->getX(), jugador->getY(), 0, origenY[OrdenSprite(jugador->getDireccion())]);
}

void CDibujoTanques::DibujarEnemigo(Graphics^ g, CEnemigo* enemigo, Bitmap^ bmpTanques) {
	if (enemigo == nullptr) return;
	// Los enemigos (primera columna) forman grupos de 4 filas (arriba, derecha, abajo, izquierda).
	// El primer grupo empieza en y = 508 y cada grupo siguiente esta 255 px mas abajo (uno por tipo).
	static const int desplazamientoY[4] = { 0, 64, 124, 191 };
	int grupo = static_cast<int>(enemigo->getTipo());
	if (grupo > 3) grupo = 3;   // la hoja trae 4 grupos: tipo5 reutiliza el ultimo
	int origenY = 508 + 255 * grupo + desplazamientoY[OrdenSprite(enemigo->getDireccion())];
	DibujarSprite(g, bmpTanques, enemigo->getX(), enemigo->getY(), 0, origenY);
}
```

Compila (Ctrl+Shift+B) antes de pasar al siguiente paso.

## Paso 10: Juego.h (formulario)

**Capa:** CpBattle | **Que hace:** Carga los bitmaps, crea la Controladora, Tick dibuja, teclas 1-5 | **Corresponde a:** PUNTO c (carga y dibujo)

**`CpBattle/Juego.h`**

```cpp
#pragma once
#include "Controladora.h"
#include "DibujoMapa.h"
#include "DibujoTanques.h"

namespace CpBattle {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Juego : public System::Windows::Forms::Form
	{
	public:
		CControladora* controladora = new CControladora();
		Bitmap^ bmpPiso = gcnew Bitmap("imagenes\\pisos.png");
		Bitmap^ bmpBloques = gcnew Bitmap("imagenes\\bloques.png");
		Bitmap^ bmpTrofeo = gcnew Bitmap("imagenes\\trofeo.png");
		Bitmap^ bmpTanques = gcnew Bitmap("imagenes\\tanques.png");

		Juego(void)
		{
			InitializeComponent();
			// fondo amarillo de tanques.png
			bmpTanques->MakeTransparent(bmpTanques->GetPixel(0, 0));
			// fondo rosado del arbol en bloques.png
			bmpBloques->MakeTransparent(Color::FromArgb(255, 81, 241));
		}

	protected:
		~Juego()
		{
			if (components)
			{
				delete components;
			}
			delete controladora;
		}
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 30;
			this->timer1->Tick += gcnew System::EventHandler(this, &Juego::timer1_Tick);
			// 
			// Juego
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Black;
			this->ClientSize = System::Drawing::Size(832, 704);
			this->DoubleBuffered = true;
			this->Name = L"Juego";
			this->Text = L"Battle City";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &Juego::Juego_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Juego::Juego_KeyDown);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		Graphics^ g = this->CreateGraphics();
		BufferedGraphicsContext^ espacio = BufferedGraphicsManager::Current;
		BufferedGraphics^ buffer = espacio->Allocate(g, this->ClientRectangle);

		CDibujoMapa::Dibujar(buffer->Graphics, controladora->getMapa(), bmpPiso, bmpBloques, bmpTrofeo);
		CDibujoTanques::DibujarJugador(buffer->Graphics, controladora->getJugador(), bmpTanques);
		CDibujoTanques::DibujarEnemigo(buffer->Graphics, controladora->getEnemigo(), bmpTanques);

		buffer->Render(g);

		delete buffer;
		delete g;
	}
	private: System::Void Juego_Load(System::Object^ sender, System::EventArgs^ e) {
		controladora->Inicializar();
	}
	private: System::Void Juego_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode) {
		case Keys::D1: case Keys::NumPad1:
			controladora->CambiarNivel(1);
			break;
		case Keys::D2: case Keys::NumPad2:
			controladora->CambiarNivel(2);
			break;
		case Keys::D3: case Keys::NumPad3:
			controladora->CambiarNivel(3);
			break;
		case Keys::D4: case Keys::NumPad4:
			controladora->CambiarNivel(4);
			break;
		case Keys::D5: case Keys::NumPad5:
			controladora->CambiarNivel(5);
			break;
		default:
			break;
		}
	}
	};
}
```

Compila (Ctrl+Shift+B) antes de pasar al siguiente paso.

## Comprobacion final

Ejecuta el juego: se ve el mapa del nivel 1, el Jugador (amarillo, abajo) y un Enemigo en la esquina superior izquierda. Con las teclas 1 a 5 cambias de nivel.

## Notas
- Los niveles 2 a 5 tienen 11 filas x 13 columnas (el `MAX_FILAS` del docente); se ajustaron las imagenes de 13x13 quitando las 2 filas mas vacias y agregando la base.
- Codigos de bloque: 1 piso, 2 ladrillo (durabilidad 2), 3 acero, 4 agua, 5 arbol, 9 trofeo.
- El sprite del tanque es una ventana de 64x64 en `tanques.png`; el Jugador empieza arriba (fila de sprites 0) y los enemigos usan una banda de 255 px por tipo.
- No pude compilar en Visual Studio desde aqui: las capas nativas y el dibujo se probaron con g++ y un Graphics simulado. Si algo no compila, mandame el mensaje de error.
