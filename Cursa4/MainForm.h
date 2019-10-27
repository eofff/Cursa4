#pragma once

#include <ctime>

#include "Utils.h"
#include <CL/cl.h>
#include <omp.h>

#define SEQUENTIAL_ITEM 0
#define OPENMP_ITEM 1

namespace Cursa4 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ image1Box;
	protected:

	protected:

	protected:
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ файлToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^ image2Box;










	private: System::Windows::Forms::Button^ processButton;





	private: System::Windows::Forms::ToolStripMenuItem^ loadMenuItem;

	private: System::Windows::Forms::OpenFileDialog^ loadImageDialog;
	private: System::Windows::Forms::SaveFileDialog^ saveImageDialog;
	private: System::Windows::Forms::ToolStripMenuItem^ saveMenuItem;
	private: System::Windows::Forms::NumericUpDown^ numericUpDown1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ComboBox^ methodComboBox;
	private: System::Windows::Forms::ToolStripMenuItem^ OpenCLMenu;

	private: System::Windows::Forms::ToolStripMenuItem^ DeviceInitMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ остановкаToolStripMenuItem;







	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->image1Box = (gcnew System::Windows::Forms::PictureBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->файлToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->OpenCLMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->DeviceInitMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->image2Box = (gcnew System::Windows::Forms::PictureBox());
			this->processButton = (gcnew System::Windows::Forms::Button());
			this->loadImageDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveImageDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->methodComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->остановкаToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->image1Box))->BeginInit();
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->image2Box))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			this->SuspendLayout();
			// 
			// image1Box
			// 
			this->image1Box->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->image1Box->Location = System::Drawing::Point(12, 27);
			this->image1Box->Name = L"image1Box";
			this->image1Box->Size = System::Drawing::Size(317, 211);
			this->image1Box->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->image1Box->TabIndex = 0;
			this->image1Box->TabStop = false;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->файлToolStripMenuItem,
					this->OpenCLMenu
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(729, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// файлToolStripMenuItem
			// 
			this->файлToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->loadMenuItem,
					this->saveMenuItem
			});
			this->файлToolStripMenuItem->Name = L"файлToolStripMenuItem";
			this->файлToolStripMenuItem->Size = System::Drawing::Size(50, 20);
			this->файлToolStripMenuItem->Text = L"Файл";
			// 
			// loadMenuItem
			// 
			this->loadMenuItem->Name = L"loadMenuItem";
			this->loadMenuItem->Size = System::Drawing::Size(135, 22);
			this->loadMenuItem->Text = L"Загрузить";
			this->loadMenuItem->Click += gcnew System::EventHandler(this, &MainForm::loadMenuItem_Click);
			// 
			// saveMenuItem
			// 
			this->saveMenuItem->Enabled = false;
			this->saveMenuItem->Name = L"saveMenuItem";
			this->saveMenuItem->Size = System::Drawing::Size(135, 22);
			this->saveMenuItem->Text = L"Сохранить";
			this->saveMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveMenuItem_Click);
			// 
			// OpenCLMenu
			// 
			this->OpenCLMenu->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->DeviceInitMenuItem,
					this->остановкаToolStripMenuItem
			});
			this->OpenCLMenu->Name = L"OpenCLMenu";
			this->OpenCLMenu->Size = System::Drawing::Size(62, 20);
			this->OpenCLMenu->Text = L"OpenCL";
			// 
			// DeviceInitMenuItem
			// 
			this->DeviceInitMenuItem->Name = L"DeviceInitMenuItem";
			this->DeviceInitMenuItem->Size = System::Drawing::Size(180, 22);
			this->DeviceInitMenuItem->Text = L"Инициализация";
			this->DeviceInitMenuItem->Click += gcnew System::EventHandler(this, &MainForm::DeviceInitMenuItem_Click);
			// 
			// image2Box
			// 
			this->image2Box->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->image2Box->Location = System::Drawing::Point(400, 27);
			this->image2Box->Name = L"image2Box";
			this->image2Box->Size = System::Drawing::Size(317, 211);
			this->image2Box->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->image2Box->TabIndex = 2;
			this->image2Box->TabStop = false;
			// 
			// processButton
			// 
			this->processButton->Location = System::Drawing::Point(307, 298);
			this->processButton->Name = L"processButton";
			this->processButton->Size = System::Drawing::Size(122, 23);
			this->processButton->TabIndex = 7;
			this->processButton->Text = L"Преобразовать";
			this->processButton->UseVisualStyleBackColor = true;
			this->processButton->Click += gcnew System::EventHandler(this, &MainForm::processButton_Click);
			// 
			// loadImageDialog
			// 
			this->loadImageDialog->FileName = L"openFileDialog1";
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(307, 271);
			this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(100, 22);
			this->numericUpDown1->TabIndex = 8;
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(413, 280);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(16, 13);
			this->label1->TabIndex = 9;
			this->label1->Text = L"%";
			// 
			// methodComboBox
			// 
			this->methodComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->methodComboBox->FormattingEnabled = true;
			this->methodComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Последовательно", L"OpenMP" });
			this->methodComboBox->Location = System::Drawing::Point(307, 244);
			this->methodComboBox->Name = L"methodComboBox";
			this->methodComboBox->Size = System::Drawing::Size(122, 21);
			this->methodComboBox->TabIndex = 10;
			// 
			// остановкаToolStripMenuItem
			// 
			this->остановкаToolStripMenuItem->Name = L"остановкаToolStripMenuItem";
			this->остановкаToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->остановкаToolStripMenuItem->Text = L"Остановка";
			this->остановкаToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::остановкаToolStripMenuItem_Click);
			// 
			// MainForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(729, 329);
			this->Controls->Add(this->methodComboBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->numericUpDown1);
			this->Controls->Add(this->processButton);
			this->Controls->Add(this->image2Box);
			this->Controls->Add(this->image1Box);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->image1Box))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->image2Box))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e);
		System::Void processButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void loadMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void saveMenuItem_Click(System::Object^ sender, System::EventArgs^ e);

		cl_device_id* devices;
		cl_uint numberOfDevices = 0;

		System::Void configureDevices();
		System::Void disposeDevices();
		System::Void DeviceInitMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void addDeviceListToList();
		System::Void остановкаToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
};
}
