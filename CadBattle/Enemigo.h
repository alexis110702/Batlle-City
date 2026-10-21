#pragma once
#include "Tanque.h"
// ============================================================
//  CAPA DE DATOS (CadBattle) - Enemigo.h
//  PASO 3: enum ETipoTanque y clase CEnemigo : CTanque (tipo)
// ============================================================
enum ETipoTanque {
	tipo1,
	tipo2,
	tipo3,
	tipo4,
	tipo5
};

class CEnemigo : public CTanque {
	ETipoTanque tipo;
public:
	CEnemigo(short id, short tipo, int posx, int posy, int vidas);
	void setTipo(ETipoTanque tipo);
	ETipoTanque getTipo();
};
