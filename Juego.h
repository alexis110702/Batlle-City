#pragma once
#include "Controladora.h"

namespace Battle {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Formulario principal del juego. Se encarga unicamente de la vista
	/// (dibujo) y de capturar la entrada del usuario; toda la logica del
	/// juego vive en Controladora (req. 2, 7).
	/// </summary>
	public ref class Juego : public System::Windows::Forms::Form
	{
	private:
		Controladora^ controladora;
		System::Windows::Forms::Timer^ temporizador;

		bool teclaArriba, teclaAbajo, teclaIzquierda, teclaDerecha, teclaDisparo;

	public:
		Juego(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//

			controladora = gcnew Controladora();

			this->DoubleBuffered = true;
			this->KeyPreview = true;
			this->ClientSize = System::Drawing::Size(
				Constantes::ANCHO_MAPA + 170,
				Constantes::ALTO_MAPA + 25);

			temporizador = gcnew System::Windows::Forms::Timer();
			temporizador->Interval = 40; // ~25 ciclos por segundo
			temporizador->Tick += gcnew EventHandler(this, &Juego::Temporizador_Tick);
			temporizador->Start();

			this->Paint += gcnew PaintEventHandler(this, &Juego::Juego_Paint);
			this->KeyDown += gcnew KeyEventHandler(this, &Juego::Juego_KeyDown);
			this->KeyUp += gcnew KeyEventHandler(this, &Juego::Juego_KeyUp);
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se están usando.
		/// </summary>
		/// 
		~Juego()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		// Ciclo principal del juego, disparado por el temporizador (req. 2)
		void Temporizador_Tick(Object^ sender, EventArgs^ e) {
			if (teclaArriba) controladora->ProcesarTecla(Keys::Up);
			else if (teclaAbajo) controladora->ProcesarTecla(Keys::Down);
			else if (teclaIzquierda) controladora->ProcesarTecla(Keys::Left);
			else if (teclaDerecha) controladora->ProcesarTecla(Keys::Right);

			if (teclaDisparo) controladora->ProcesarTecla(Keys::Space);

			controladora->ActualizarCicloDeJuego();
			this->Invalidate();
		}

		void Juego_Paint(Object^ sender, PaintEventArgs^ e) {
			controladora->Dibujar(e->Graphics);
		}

		// Captura los comandos de movimiento/disparo del usuario (req. 7)
		void Juego_KeyDown(Object^ sender, KeyEventArgs^ e) {
			switch (e->KeyCode) {
			case Keys::Up: teclaArriba = true; break;
			case Keys::Down: teclaAbajo = true; break;
			case Keys::Left: teclaIzquierda = true; break;
			case Keys::Right: teclaDerecha = true; break;
			case Keys::Space: teclaDisparo = true; break;
			case Keys::Enter:
				if (controladora->Estado->JuegoTerminado()) controladora->Iniciar();
				break;
			}
		}

		void Juego_KeyUp(Object^ sender, KeyEventArgs^ e) {
			switch (e->KeyCode) {
			case Keys::Up: teclaArriba = false; break;
			case Keys::Down: teclaAbajo = false; break;
			case Keys::Left: teclaIzquierda = false; break;
			case Keys::Right: teclaDerecha = false; break;
			case Keys::Space: teclaDisparo = false; break;
			}
		}

		System::ComponentModel::IContainer^ components;
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// Juego
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(387, 354);
			this->Name = L"Juego";
			this->Text = L"Battle Tanks";
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
