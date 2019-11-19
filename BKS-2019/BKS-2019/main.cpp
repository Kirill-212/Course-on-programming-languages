#include <cwchar>
#include <iostream>
#include "Error.h"
#include "Parm.h"
#include "Log.h"
#include "In.h"
#include <stack>
#include"IT.h"
#include"LT.h"
#include"Lex.h"



using namespace std;


 int wmain(int argc, wchar_t* argv[]) {

	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INTLOG;
	try
	{

		//Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog((wchar_t *)L"C:\\ycheba\\main_kyrsovoi\\Course-on-programming-languages\\test_project\\log.log");
		//wcout << "-in:" << parm.in << ", -out" << parm.out << ", -log: " << parm.log << endl;
		In::IN in = In::getin((wchar_t *)L"C:\\ycheba\\main_kyrsovoi\\Course-on-programming-languages\\test_project\\test1.txt");

		cout << in.text << endl;
		
		 Lex::Lex_analyz_new(in);
		

		//Log::WriteLine(log, "Тест:", "без ошибок", "");
		//Log::WriteLog(log);
		//Log::WriteParm(log, parm);
		
		Log::WriteIn(log, in);
		Log::Close(log);

	}
	catch (Error::ERROR error) {

		cout << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line << ",позиция " << error.inext.col << std::endl;
		Log::WriteError(log, error);
		system("pause");
	}
	system("pause");
}



