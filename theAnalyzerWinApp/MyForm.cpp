#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;


[STAThreadAttribute]
int main() {
	setlocale(LC_ALL, "rus");
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	theAnalyzerWinApp::MyForm form;
	Application::Run(% form);

	
}

