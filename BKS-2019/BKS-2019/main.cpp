#include <cwchar>
#include <iostream>
#include "Error.h"
#include "Parm.h"
#include "Log.h"
#include "In.h"
#include "FST.h"
#include "LT.h"
#include "LEX.h"
#include <stack>
#include"GRB.h"
#include"MFST.h"
#include"PN.h"
#include"GEN.h"

using namespace std;



int wmain(int argc, wchar_t* argv[]) {

	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INTLOG;
	try
	{

		
		
	 Parm::PARM parm = Parm::getparm(argc, argv);
		In::IN fg = In::getin(parm.in);
		log = Log::getlog((wchar_t *)L"C:\\ycheba\\main_kyrsovoi\\Course-on-programming-languages\\test_project\\log.log");
		wcout << "-in:" << parm.in << ", -out" << parm.out << ", -log: " << parm.log << endl;
		//In::IN in = In::getin((wchar_t *)L"C:\\ycheba\\main_kyrsovoi\\Course-on-programming-languages\\test_project\\test1.txt");

		//cout << in.text << endl;

		Lex::Tables Tables = Lex::Lex_analyz_new(fg);

		int b = Tables.LexTable.table[0].sn;
		std::cout << std::endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		for (int i = 0; i < Tables.LexTable.size; i++) {
			if (i == 0) {
				std::cout << b << "\t|";
			}
			if (b != Tables.LexTable.table[i].sn) {
				std::cout << std::endl;
				b = Tables.LexTable.table[i].sn;
				std::cout << b << "\t|";
			}
			std::cout << Tables.LexTable.table[i].lexema;

		}
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;









		for (int i = 0; i < Tables.idTable.size; i++) {
			cout << Tables.idTable.table[i].id << "            " << Tables.idTable.table[i].iddatatype << "            " << Tables.idTable.table[i].idtype << "        " << endl;
		}

		cout << endl;
		cout << endl;
	MFST_TRACE_START//отладка
		MFST::Mfst mfst(Tables, GRB::getGreibach());
	if (!mfst.start()) {
		throw Error::geterrorin(600, 0, 0);
	}
	//mfst.start();//анализ1
	mfst.printrules();

	Lex::Sem_analiz(Tables);

	


	PN::polish_notation(Tables);



	b = Tables.LexTable.table[0].sn;
	cout << std::endl;
	for (int i = 0; i < Tables.LexTable.size; i++) {
		if (i == 0) {
			std::cout << b << "|";
		}
		if (b != Tables.LexTable.table[i].sn) {
			std::cout << std::endl;
			b = Tables.LexTable.table[i].sn;
			std::cout << b << "|";
		}
		if (Tables.LexTable.table[i].lexema == 'v') {
			cout << Tables.LexTable.table[i].value;
		}
		else {
			cout << Tables.LexTable.table[i].lexema ;
		}
		

	}
	b = Tables.LexTable.table[0].sn;

	cout << endl;
	for (int i = 0; i < Tables.LexTable.size; i++) {
		if (i == 0) {
			std::cout << b << "|";
		}
		if (b != Tables.LexTable.table[i].sn) {
			std::cout << std::endl;
			b = Tables.LexTable.table[i].sn;
			std::cout << b << "|";
		}
		cout << Tables.LexTable.table[i].lexema << "[" << Tables.LexTable.table[i].idxTI << "]";

	}
	GEN::FixID(Tables);
	cout << endl;
	cout << endl;
	cout << endl;
	for (int i = 0; i < Tables.idTable.size; i++) {
		cout << Tables.idTable.table[i].id << "            " << Tables.idTable.table[i].iddatatype << "            " << Tables.idTable.table[i].idtype << "        " << endl;
	}
	char* idtype=new char[256];
	char* iddatatype = new char[256];
	char* value = new char[256];
	cout << endl;
	cout << endl;
	for (int i = 0; i < Tables.idTable.size; i++)
	{
		switch (Tables.idTable.table[i].idtype)
		{
		case 1:idtype = (char*)"VARIABLE"; break;
		case 2:idtype = (char*)"FUNCTION"; break;
		case 3:idtype = (char*)"PARAMETR"; break;
		case 4: idtype = (char*)"LITERAL"; break;
		default:break;
		}
		switch (Tables.idTable.table[i].iddatatype)
		{
		case 1:
			iddatatype = (char*)"INT";
			/*itoa(Tables.idTable.table[i].value.vint, value, 10);*/
			//value = (char*)"0";
			break;
		case 2:
			iddatatype = (char*)"STR";
			//value = Tables.idTable.table[i].value.vstr.str;
			break;
		case 3:
			iddatatype = (char*)"BOOL";
			if (Tables.idTable.table[i].value.T_F) value = (char*)"true";
			else value = (char*)"false";
			break;
		default:break;
		}

		Log::WriteLine(log, iddatatype, "\t\t", idtype, "\t\t", "\t\t", Tables.idTable.table[i].id, "\n", ""); /*"\t\t", indLT, "\n", "");*/
	}

		
	GEN::GetGeN((wchar_t *)L"C:\\ycheba\\main_kyrsovoi\\Course-on-programming-languages\\BKS-2019\\main_asm\\asm\\asm\\Project.asm", Tables);

		Log::WriteLine(log, "Тест:", "без ошибок", "");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		//Log::WriteLine(log, "privet");
		
		Log::Close(log);

	}
	catch (Error::ERROR error) {

		cout << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line << ",позиция " << error.inext.col << std::endl;
		Log::WriteError(log, error);
		system("pause");
	}
	system("pause");
}


