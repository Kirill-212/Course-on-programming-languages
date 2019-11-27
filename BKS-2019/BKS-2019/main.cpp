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
		
	Lex::Tables Tables =Lex::Lex_analyz_new(in);
	int b = Tables.LexTable.table[0].sn;
	std::cout << std::endl;
	for (int i = 0; i < Tables.LexTable.size; i++) {
		if (i == 0) {
			std::cout << b<< "|";
		}
		if (b != Tables.LexTable.table[i].sn) {
			std::cout << std::endl;
			b = Tables.LexTable.table[i].sn;
			std::cout << b << "|";
		}
		std::cout << Tables.LexTable.table[i].lexema ;

	}
	cout << endl;
	for (int i = 0; i < Tables.idTable.size;i++) {
		cout << Tables.idTable.table[i].id <<"            "<< Tables.idTable.table[i].iddatatype << "            " << Tables.idTable.table[i].idtype<< endl;
	}
	///cout << Tables.idTable.table[0].id;



	//cout << endl;
	//	char* iddatatype;
	//	char* idtype;
	//	cout << "----------------------------------------------------------------------------------------------------" << endl;
	//	for (int i = 0; i < Tables.idTable.size; i++) {
	//		//cout << endl;
	//		switch (Tables.idTable.table[i].iddatatype) {
	//		case IT::INT: { iddatatype = (char*)"integer"; break; }
	//		case IT::STR: { iddatatype = (char*)"string";  break; }
	//		default: iddatatype = (char*)"none"; break;
	//		}
	//		switch (Tables.idTable.table[i].idtype) {
	//		case IT::F:{ idtype = (char*)"function"; break; }
	//		case IT::L:{ idtype = (char*)"Literal";  break; }
	//		case IT::P:{ idtype = (char*)"Parametr";  break; }
	//		case IT::V: { idtype = (char*)"Var    ";  break; }
	//		default: idtype = (char*)"none"; break;
	//		}
	//		    
	//		if (Tables.idTable.table[i].iddatatype == IT::INT || Tables.idTable.table[i].idtype == IT::F) {
	//			cout <<"|" <<Tables.idTable.table[i].id << "      \t" << iddatatype << "  \t\t" << idtype << "  \t\t" << Tables.idTable.table[i].value.vint << "                  \t\t" << Tables.idTable.table[i].idxfirstLE << endl;
	//		}
	//		else if (Tables.idTable.table[i].iddatatype == IT::STR) {
	//			cout << "|" << Tables.idTable.table[i].id << "      \t" << iddatatype << "  \t\t" << idtype << "  \t\t" << Tables.idTable.table[i].value.vstr.str << "                \t\t" << Tables.idTable.table[i].idxfirstLE << endl;
	//		}
	//	}
		


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



