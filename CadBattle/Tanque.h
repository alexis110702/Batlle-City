#pragma once
#include "Comun.h"
// ============================================================
//  CAPA DE DATOS (CadBattle) - Tanque.h
//  PASO 3: clase base CTanque (id, vidas, direccion, velocidad, posX, posY)
//           SOLO datos: aqui NO se dibuja nada
// ============================================================
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
