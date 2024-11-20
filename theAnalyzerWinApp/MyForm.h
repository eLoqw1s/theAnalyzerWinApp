#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <msclr/marshal_cppstd.h>

#include "Data.h"

namespace theAnalyzerWinApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
		public:
			MyForm(void)
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
			~MyForm()
			{
				if (components)
				{
					delete components;
				}
			}

		private: System::Windows::Forms::Button^ button_Scaner;
		protected:

		protected:



		private: System::Windows::Forms::Label^ errorPos;

		private: System::Windows::Forms::Label^ label1;
		private: System::Windows::Forms::Label^ label2;
		private: System::Windows::Forms::Label^ sostError;
		private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
		private: System::Windows::Forms::RichTextBox^ inputCode;
		private: System::Windows::Forms::Button^ loadFile;
		private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
		private: System::Windows::Forms::RichTextBox^ outputTokens;
		private: System::Windows::Forms::Button^ btnLoadXmlClick;
		private: System::Windows::Forms::Button^ btnSutClick;
		private: System::Windows::Forms::RichTextBox^ memDataText;
		private: System::Windows::Forms::Label^ label3;
		private: System::Windows::Forms::OpenFileDialog^ openFileDialog2;






		private:


		private: System::ComponentModel::IContainer^ components;



		private:
			/// <summary>
			/// Обязательная переменная конструктора.
			/// </summary>


	#pragma region Windows Form Designer generated code
			/// <summary>
			/// Требуемый метод для поддержки конструктора — не изменяйте 
			/// содержимое этого метода с помощью редактора кода.
			/// </summary>
			void InitializeComponent(void)
			{
				this->components = (gcnew System::ComponentModel::Container());
				this->button_Scaner = (gcnew System::Windows::Forms::Button());
				this->errorPos = (gcnew System::Windows::Forms::Label());
				this->label1 = (gcnew System::Windows::Forms::Label());
				this->label2 = (gcnew System::Windows::Forms::Label());
				this->sostError = (gcnew System::Windows::Forms::Label());
				this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
				this->inputCode = (gcnew System::Windows::Forms::RichTextBox());
				this->loadFile = (gcnew System::Windows::Forms::Button());
				this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
				this->outputTokens = (gcnew System::Windows::Forms::RichTextBox());
				this->btnLoadXmlClick = (gcnew System::Windows::Forms::Button());
				this->btnSutClick = (gcnew System::Windows::Forms::Button());
				this->memDataText = (gcnew System::Windows::Forms::RichTextBox());
				this->label3 = (gcnew System::Windows::Forms::Label());
				this->openFileDialog2 = (gcnew System::Windows::Forms::OpenFileDialog());
				this->SuspendLayout();
				// 
				// button_Scaner
				// 
				this->button_Scaner->Location = System::Drawing::Point(655, 12);
				this->button_Scaner->Name = L"button_Scaner";
				this->button_Scaner->Size = System::Drawing::Size(96, 34);
				this->button_Scaner->TabIndex = 2;
				this->button_Scaner->Text = L"Сканер";
				this->button_Scaner->UseVisualStyleBackColor = true;
				this->button_Scaner->Click += gcnew System::EventHandler(this, &MyForm::button_Scaner_Click);
				// 
				// errorPos
				// 
				this->errorPos->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				this->errorPos->Location = System::Drawing::Point(32, 571);
				this->errorPos->Name = L"errorPos";
				this->errorPos->Size = System::Drawing::Size(515, 30);
				this->errorPos->TabIndex = 4;
				this->errorPos->Text = L"Позиция ошибок";
				// 
				// label1
				// 
				this->label1->AutoSize = true;
				this->label1->Location = System::Drawing::Point(29, 610);
				this->label1->Name = L"label1";
				this->label1->Size = System::Drawing::Size(158, 16);
				this->label1->TabIndex = 5;
				this->label1->Text = L"Обнаруженные ошибки";
				// 
				// label2
				// 
				this->label2->AutoSize = true;
				this->label2->Location = System::Drawing::Point(29, 30);
				this->label2->Name = L"label2";
				this->label2->Size = System::Drawing::Size(185, 16);
				this->label2->TabIndex = 6;
				this->label2->Text = L"Текст тестовой программы";
				// 
				// sostError
				// 
				this->sostError->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				this->sostError->Location = System::Drawing::Point(32, 626);
				this->sostError->Name = L"sostError";
				this->sostError->Size = System::Drawing::Size(515, 96);
				this->sostError->TabIndex = 7;
				// 
				// contextMenuStrip1
				// 
				this->contextMenuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
				this->contextMenuStrip1->Name = L"contextMenuStrip1";
				this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
				// 
				// inputCode
				// 
				this->inputCode->Location = System::Drawing::Point(32, 64);
				this->inputCode->Name = L"inputCode";
				this->inputCode->Size = System::Drawing::Size(515, 504);
				this->inputCode->TabIndex = 8;
				this->inputCode->Text = L"";
				// 
				// loadFile
				// 
				this->loadFile->Location = System::Drawing::Point(553, 64);
				this->loadFile->Name = L"loadFile";
				this->loadFile->Size = System::Drawing::Size(96, 34);
				this->loadFile->TabIndex = 9;
				this->loadFile->Text = L"Загрузить";
				this->loadFile->UseVisualStyleBackColor = true;
				this->loadFile->Click += gcnew System::EventHandler(this, &MyForm::loadFile_Click);
				// 
				// openFileDialog1
				// 
				this->openFileDialog1->FileName = L"openFileDialog1";
				// 
				// outputTokens
				// 
				this->outputTokens->BackColor = System::Drawing::SystemColors::Window;
				this->outputTokens->Location = System::Drawing::Point(655, 64);
				this->outputTokens->Name = L"outputTokens";
				this->outputTokens->ReadOnly = true;
				this->outputTokens->Size = System::Drawing::Size(344, 652);
				this->outputTokens->TabIndex = 10;
				this->outputTokens->Text = L"";
				// 
				// btnLoadXmlClick
				// 
				this->btnLoadXmlClick->Location = System::Drawing::Point(1016, 12);
				this->btnLoadXmlClick->Name = L"btnLoadXmlClick";
				this->btnLoadXmlClick->Size = System::Drawing::Size(107, 34);
				this->btnLoadXmlClick->TabIndex = 11;
				this->btnLoadXmlClick->Text = L"LR-таблица";
				this->btnLoadXmlClick->UseVisualStyleBackColor = true;
				this->btnLoadXmlClick->Click += gcnew System::EventHandler(this, &MyForm::btnLoadXmlClick_Click);
				// 
				// btnSutClick
				// 
				this->btnSutClick->Location = System::Drawing::Point(1129, 12);
				this->btnSutClick->Name = L"btnSutClick";
				this->btnSutClick->Size = System::Drawing::Size(83, 34);
				this->btnSutClick->TabIndex = 12;
				this->btnSutClick->Text = L"СУТ";
				this->btnSutClick->UseVisualStyleBackColor = true;
				this->btnSutClick->Click += gcnew System::EventHandler(this, &MyForm::btnSutClick_Click);
				// 
				// memDataText
				// 
				this->memDataText->BackColor = System::Drawing::SystemColors::Window;
				this->memDataText->Location = System::Drawing::Point(1016, 64);
				this->memDataText->Name = L"memDataText";
				this->memDataText->Size = System::Drawing::Size(435, 652);
				this->memDataText->TabIndex = 13;
				this->memDataText->Text = L"";
				// 
				// label3
				// 
				this->label3->AutoSize = true;
				this->label3->Location = System::Drawing::Point(1218, 30);
				this->label3->Name = L"label3";
				this->label3->Size = System::Drawing::Size(211, 16);
				this->label3->TabIndex = 14;
				this->label3->Text = L"Распределение памяти данных";
				// 
				// openFileDialog2
				// 
				this->openFileDialog2->FileName = L"openFileDialog2";
				// 
				// MyForm
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = System::Drawing::Size(1463, 745);
				this->Controls->Add(this->label3);
				this->Controls->Add(this->memDataText);
				this->Controls->Add(this->btnSutClick);
				this->Controls->Add(this->btnLoadXmlClick);
				this->Controls->Add(this->outputTokens);
				this->Controls->Add(this->loadFile);
				this->Controls->Add(this->inputCode);
				this->Controls->Add(this->sostError);
				this->Controls->Add(this->label2);
				this->Controls->Add(this->label1);
				this->Controls->Add(this->errorPos);
				this->Controls->Add(this->button_Scaner);
				this->Name = L"MyForm";
				this->Text = L"Лексический анализатор";
				this->ResumeLayout(false);
				this->PerformLayout();

			}
	#pragma endregion
		private: System::Void button_Scaner_Click(System::Object^ sender, System::EventArgs^ e) {
		
			initDataType();

			inputCode->SelectionStart = colorErrorPos;
			inputCode->SelectionLength = 1;
			inputCode->SelectionBackColor = Color::White;

			StrProg = msclr::interop::marshal_as<std::string >(inputCode->Text);

			if (!String::IsNullOrEmpty(inputCode->Text)) {

				int occurrences = std::count(StrProg.begin(), StrProg.end(), '#');
				if (occurrences % 2 != 0) {
					errorPos->Text = "Error";
					sostError->Text = "Не закрытый комментарий!";
					outputTokens->Text = "";
					return;
				}

				while (StrProg[StrProg.length() - 1] == ' ' 
					|| StrProg[StrProg.length() - 1] == '\n') 
				{
					StrProg.erase(StrProg.length() - 1, 1);
				}

				while (f < StrProg.length()) {
					Scaner();
				}


				if (errorPositionInLine != "Ошибок не обнаружено") {
					colorErrorPos = r;
					if (StrProg[colorErrorPos - 1] == '&' && StrProg[colorErrorPos - 2] != '&'
						|| StrProg[colorErrorPos - 1] == '|' && StrProg[colorErrorPos - 2] != '|')
					{
						colorErrorPos = r - 1;

						countChar--;
						errorPositionInLine = "Номер строки: " + std::to_string(countLines) +
							"   Номер символа в строке: " + std::to_string(countChar);
					}
					inputCode->SelectionStart = colorErrorPos;
					inputCode->SelectionLength = 1;
					inputCode->SelectionBackColor = Color::Red;
				}

				outputTokens->Text = gcnew String(tokenLine.c_str());
				sostError->Text = (gcnew String(errorSost.c_str()))->Replace("&", "&&");
				errorPos->Text = gcnew String(errorPositionInLine.c_str());

				f = 0;
				r = 0;
				tokenLine = "";
				errorSost = "Анализ успешно завершен";
				errorPositionInLine = "Ошибок не обнаружено";
				countLines = 1;
				countChar = 1;
			}
			else {
				MessageBox::Show("Загрузите или впишите текст кода!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
		}
		private: System::Void loadFile_Click(System::Object^ sender, System::EventArgs^ e) {
			if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK
				&& openFileDialog1->FileName->Length > 0)
			{
				try {
					System::IO::Stream^ myStream;
					if ((myStream = openFileDialog1->OpenFile()) != nullptr) {
						myStream->Close();
						inputCode->LoadFile(openFileDialog1->FileName, RichTextBoxStreamType::PlainText);
					}
				}
				catch (...) {
					MessageBox::Show("Не могу открыть файл " + System::IO::Path::GetFileName(openFileDialog1->FileName) +
						"\nПроверьте его имя, права доступа и формат (нужен RTF)", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
					return;
				}
			}
		}

		private: System::Void btnSutClick_Click(System::Object^ sender, System::EventArgs^ e) {
			memDataText->Text = "";

			StrProg = msclr::interop::marshal_as<std::string >(inputCode->Text);

			int occurrences = std::count(StrProg.begin(), StrProg.end(), '#');
			if (occurrences % 2 != 0) {
				errorPos->Text = "Error";
				sostError->Text = "Не закрытый комментарий!";
				outputTokens->Text = "";
				return;
			}

			if (SUT_LR())
			{
				memDataText->Text = gcnew String(memory.c_str());
			}
			sostError->Text = (gcnew String(errorSost.c_str()));
			errorSost = "Анализ успешно завершен";
			memory = "";
			NextAddr = 0;
		}

		private: System::Void btnLoadXmlClick_Click(System::Object^ sender, System::EventArgs^ e) {
			if (openFileDialog2->ShowDialog() == System::Windows::Forms::DialogResult::OK
				)
			{
				try {
					System::IO::Stream^ myStream;
					if ((myStream = openFileDialog2->OpenFile()) != nullptr) {
						XmlDocument^ xmlDoc = gcnew XmlDocument();
						xmlDoc->Load(openFileDialog2->FileName);

						// Получение корневого узла
						XmlNode^ RootNode = xmlDoc->DocumentElement;

						// Загрузка нетерминалов
						XmlNode^ ColsNode = RootNode->SelectSingleNode("Columns");
						XmlNode^ DataNode = ColsNode->SelectSingleNode("Neterms");


						for (int i = 0; i < DataNode->ChildNodes->Count; i++) {
							XmlNode^ TmpNode = DataNode->ChildNodes[i];

							String^ AttrStr = TmpNode->Attributes["ColNum"]->Value;
							NumColLR = Convert::ToInt32(AttrStr); // номер столбца LR-таблицы разбора

							AttrStr = TmpNode->Attributes["Lexeme"]->Value;
							SymsLR[NumColLR] = msclr::interop::marshal_as<std::string>(AttrStr);
						}

						NumNeTerm = NumColLR;

						// Загрузка терминалов
						DataNode = ColsNode->SelectSingleNode("Terms");
						for (int i = 0; i < DataNode->ChildNodes->Count; i++) {
							XmlNode^ TmpNode = DataNode->ChildNodes[i];

							String^ AttrStr = TmpNode->Attributes["ColNum"]->Value;
							NumColLR = Convert::ToInt32(AttrStr); // номер столбца LR-таблицы разбора

							AttrStr = TmpNode->Attributes["Lexeme"]->Value;
							SymsLR[NumColLR] = msclr::interop::marshal_as<std::string>(AttrStr);

							// Поиск лексемы терминала и установка номера столбца в ТР для него
							int Lex = (int)tLexCode::lcAnd;
							int LexHigh = (int)tLexCode::lcErr;
							while (Lex <= LexHigh) {
								if (LexClass[Lex].LexName == msclr::interop::marshal_as<std::string>(AttrStr)) {
									break;
								}
								Lex++;
							}

							if (Lex > LexHigh) { // не найдена
								MessageBox::Show("В списке лексических классов не найдено обозначение лексического класса «" +
									AttrStr + "»!", "Предупреждение", MessageBoxButtons::OK, MessageBoxIcon::Hand);
								return;
							}
							else {
								LexCodeLR[LexClass[Lex].LexCode] = NumColLR;
							}
						}

						// Загрузка таблицы разбора
						for (int i = 1; i < RootNode->ChildNodes->Count; i++) {
							DataNode = RootNode->ChildNodes[i];

							String^ AttrStr = DataNode->Attributes["NSost"]->Value;
							int State = Convert::ToInt32(AttrStr);

							for (int j = 0; j < DataNode->ChildNodes->Count; j++) {
								XmlNode^ TmpNode = DataNode->ChildNodes[j];

								AttrStr = TmpNode->Attributes["ColNum"]->Value;
								int TmpInt = Convert::ToInt32(AttrStr); // столбец в ТР

								AttrStr = TmpNode->Attributes["ElType"]->Value;
								LRTbl[State][TmpInt].ElType = Convert::ToInt32(AttrStr);

								AttrStr = TmpNode->Attributes["ElPar"]->Value;
								LRTbl[State][TmpInt].ElPar = Convert::ToInt32(AttrStr);

								AttrStr = TmpNode->Attributes["Left"]->Value;
								int k = (AttrStr != "") ? 1 : 0;
								if (AttrStr != "") {
									while (SymsLR[k] != msclr::interop::marshal_as<std::string>(AttrStr)) {
										k++;
									}
								}
								LRTbl[State][TmpInt].Left = k;

								AttrStr = TmpNode->Attributes["Act"]->Value;
								if (AttrStr != "") {
									AttrStr = AttrStr->Substring(1); // Удаление первого символа
									LRTbl[State][TmpInt].Act = Convert::ToInt32(AttrStr);
								}
								else {
									LRTbl[State][TmpInt].Act = 0;
								}
							}
						}
						myStream->Close();
					}
				}
				catch (...) {
					MessageBox::Show("Не могу открыть файл " + System::IO::Path::GetFileName(openFileDialog2->FileName) +
						"\nПроверьте его имя, права доступа и формат (нужен RTF)", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
					return;
				}
			}
		}
	};
}
