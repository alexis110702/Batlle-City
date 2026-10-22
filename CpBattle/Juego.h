#pragma once
#include "Controladora.h"
#include "DibujoMapa.h"
#include "DibujoTanques.h"
// ============================================================
//  CAPA DE PRESENTACION (CpBattle) - Juego.h
//  PASO 10: formulario: cargar imagenes (tanques.png...), crear la Controladora y
//            dibujar en cada tick del temporizador (PUNTO c)
// ============================================================

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
