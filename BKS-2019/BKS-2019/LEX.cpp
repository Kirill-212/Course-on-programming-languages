#include <iostream>
#include "FST.h"
#include "Lex.h"
#include "In.h"
#include "Parm.h"
#include "Log.h"
#include <stack>
#include <queue>

using namespace std;



Lex::Word_array Lex::Create_word(const char* s) {

	Lex::Word_array array = {};

	int j = 0;
	int k = 0;
	int i = 0;
	if (s[i] == ' ') i++;
	int nwords = 0;

	// подсчет слов входной строки.
	for (int x = i; x <= strlen(s); x++) {
		if (s[x] == '+' || s[x] == '-' || s[x] == '*' || s[x] == '/' || s[x] == '(' || s[x] == ')' || s[x] == '{' || s[x] == '}' || s[x] == ',' || s[x] == ';' || s[x] == '+' || s[x] == '=') {
			if (s[x - 1] != '+' && s[x - 1] != '-' && s[x - 1] != '*' && s[x - 1] != '/' && s[x - 1] != '(' && s[x - 1] != ')' && s[x - 1] != '{' && s[x - 1] != '}' && s[x - 1] != ',' && s[x - 1] != ' ' && s[x - 1] != '\n' && s[x - 1] != ';' && s[x - 1] != '=')
				nwords += 2;
			else nwords++;
		}

		else if ((s[x] == ' ' || s[x] == '\n') && s[x + 1] != '\0')
		{
			if (s[x - 1] != '+' && s[x - 1] != '-' && s[x - 1] != '*' && s[x - 1] != '/' && s[x - 1] != '(' && s[x - 1] != ')' && s[x - 1] != '{' && s[x - 1] != '}' && s[x - 1] != ',' && s[x - 1] != ' ' && s[x - 1] != '\n' && s[x - 1] != ';' && s[x - 1] != '=')
				nwords += 1;
		}
		else if (s[x] == '\'') {
			x++;

			while (s[x] != '\'') x++;
		}
		else if (s[x] == '\0') {
			if (s[x - 1] != '+' && s[x - 1] != '-' && s[x - 1] != '*' && s[x - 1] != '/' && s[x - 1] != '(' && s[x - 1] != ')' && s[x - 1] != '{' && s[x - 1] != '}' && s[x - 1] != ',' && s[x - 1] != ' ' && s[x - 1] != '\n' && s[x - 1] != ';' && s[x - 1] != '=')
				nwords += 1;
			break;
		}
	}

	// подсчет символов в каждом слове.
	int *letters = new int[nwords];
	int count = 0;
	int index = 0;
	for (int x = i; x < strlen(s) + 1; x++) {
		count++;
		if (s[x] == '+' || s[x] == '+' || s[x] == '-' || s[x] == '*' || s[x] == '/' || s[x] == '(' || s[x] == ')' || s[x] == '{' || s[x] == '}' || s[x] == ',' || s[x] == '=') {
			letters[index] = count - 1;
			count = 0;
			index++;
			letters[index] = 1;
			index++;
		}

		if (s[x] == ' ' || s[x] == '\0') {
			letters[index] = count - 1;
			count = 0;
			index++;
		}

		if (s[x] == '\'') {
			count = 1;
			x++;
			while (s[x] != '\'') {
				count++;
				x++;
			}
			letters[index] = count;
			count = 0;
			index++;
		}

	}

	array.sn = new int[nwords]; // номера строк каждого слова

	// выделение памяти под массив слов
	char ** word_array = new char *[nwords];
	for (int z = 0; z < nwords; z++)
		word_array[z] = new char(letters[z] + 1);

	int ns = 1; // номер строки

	// заполнение массива слов
	for (i; i <= strlen(s); i++) {

		if (s[i] == '\'') {
			word_array[k][j] = s[i];
			j++;
			i++;
			while (s[i] != '\'') {
				word_array[k][j] = s[i];
				j++;
				i++;
			}
			word_array[k][j++] = s[i];
			word_array[k][j] = '\0';
		}

		else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '(' || s[i] == ')' || s[i] == '{' || s[i] == '}' || s[i] == ',' || s[i] == ';' || s[i] == '=') {
			if (s[i - 1] != '+' && s[i - 1] != '-' && s[i - 1] != '*' && s[i - 1] != '/' && s[i - 1] != '(' && s[i - 1] != ')' && s[i - 1] != '{' && s[i - 1] != '}' && s[i - 1] != ',' && s[i - 1] != ';' && s[i - 1] != '\n' && s[i - 1] != ' ' && s[i - 1] != '=') {
				array.sn[k] = ns;
				word_array[k][j] = '\0';
				k++;
			}

			j = 0;
			array.sn[k] = ns;
			word_array[k][j] = s[i];
			word_array[k][j + 1] = '\0';
			k++;
		}
		else if (s[i] == ' ') {
			if (s[i - 1] != '+' && s[i - 1] != '-' && s[i - 1] != '*' && s[i - 1] != '/' && s[i - 1] != '(' && s[i - 1] != ')' && s[i - 1] != '{' && s[i - 1] != '}' && s[i - 1] != ',' && s[i - 1] != ';' && s[i - 1] != '\n' && s[i - 1] != ' ' && s[i - 1] != '=') {
				array.sn[k] = ns;
				word_array[k][j] = '\0';
				k++;
			}

			j = 0;
		}
		else if (s[i] == '\n') {
			if (s[i - 1] != '+' && s[i - 1] != '-' && s[i - 1] != '*' && s[i - 1] != '/' && s[i - 1] != '(' && s[i - 1] != ')' && s[i - 1] != '{' && s[i - 1] != '}' && s[i - 1] != ',' && s[i - 1] != ';' && s[i - 1] != '\n' && s[i - 1] != ' ' && s[i - 1] != '=') {
				array.sn[k] = ns;
				word_array[k][j] = '\0';
				k++;
			}
			ns++;
			j = 0;
		}
		else if (s[i] == '\0') {
			if (s[i - 1] != '+' && s[i - 1] != '-' && s[i - 1] != '*' && s[i - 1] != '/' && s[i - 1] != '(' && s[i - 1] != ')' && s[i - 1] != '{' && s[i - 1] != '}' && s[i - 1] != ',' && s[i - 1] != ';' && s[i - 1] != '\n' && s[i - 1] != ' ' && s[i - 1] != '=') {
				array.sn[k] = ns;
				word_array[k][j] = '\0';
				k++;
			}
			j = 0;
		}
		else {
			word_array[k][j] = s[i];
			j++;
		}

	}


	array.array = word_array;
	array.n = nwords;

	for (int e = 0; e < nwords; e++) {
		word_array[i] = nullptr;
		delete[] word_array[i];
	}
	word_array = nullptr;
	delete[] word_array;


	return array;
}

const char*  Lex::del_probel(const char* s) {


	char* text = new char[strlen(s) + 1];
	int j = 0;
	for (int i = 0; i <= strlen(s); i++) {

		if (s[i] == ' ') {
			while (s[i] == ' ') i++;
			if (s[i] != '\n' && s[i] != '\0') text[j++] = s[i - 1];
		}

		if (s[i] == '\n' && s[i + 1] == '\0') i++;

		if (s[i] == '\n' && (s[i + 1] == ' ' || s[i + 1] == '\n')) {
			text[j++] = s[i];
			i++;
			while (s[i] == ' ' || s[i] == '\n') i++;
		}
		text[j] = s[i];
		j++;
	}
	text[j] = '\0';
	return text;
}



Lex::Tables Lex::Lex_analyz(const char *s) {

	char LibFunc[2][225] = { "substr", "strlen" };
	const char* text = Lex::del_probel(s);
	Lex::Word_array word_array = Lex::Create_word(text);
	char ** words = word_array.array;
	int nwords = word_array.n;



	LT::LexTable LexTable = LT::Create();
	IT::IdTable  IdTable = IT::Create();
	Tables Tables = {};
	Lex::Machines machines[21] = {

		{LEX_INTEGER   , FST::FST GRAPH_integer        },
		{LEX_STRING    , FST::FST GRAPH_string         },
		{LEX_PRINT     , FST::FST GRAPH_print          },
		{LEX_FUNCTION  , FST::FST GRAPH_function       },
		{LEX_DECLARE   , FST::FST GRAPH_declare        },
		{LEX_MAIN      , FST::FST GRAPH_main           },
		{LEX_RETURN    , FST::FST GRAPH_return         },
		{LEX_COMMA     , FST::FST GRAPH_COMMA          },
		{LEX_LEFTHESIS , FST::FST GRAPH_LEFTHESIS      },
		{LEX_RIGHTHESIS, FST::FST GRAPH_RIGHTHESIS     },
		{LEX_LEFTBRACE , FST::FST GRAPH_LEFTBRCE       },
		{LEX_BRACELET  , FST::FST GRAPH_BRACELET       },
		{LEX_DIRSLASH  , FST::FST GRAPH_DIRSLASH       },
		{LEX_MINUS     , FST::FST GRAPH_MINUS          },
		{LEX_PLUS      , FST::FST GRAPH_PLUS           },
		{LEX_SEMICOLON , FST::FST GRAPH_SEMICOLON      },
		{LEX_STAR      , FST::FST GRAPH_START          },
		{LEX_EQUAL     , FST::FST GRAPH_EQUAL          },
		{LEX_ID		   , FST::FST GRAPH_id             },
		{LEX_LITERAL   , FST::FST GRAPH_integer_literal},
		{LEX_LITERAL   , FST::FST GRAPH_string_literal },

	};

	int indexLT = 0;

	bool flag = 0;
	char* index_L_ = (char*)"";

	int indexIT = 0;
	IT::IDDATATYPE iddatatype;
	IT::IDTYPE idtype = IT::V;
	bool parflag = 0;
	bool functionflag = 0;
	char * prefix = (char *)"";
	char * id;
	stack<char*> visibl;

	for (int i = 0; i < nwords; i++) {
		flag = 0;

		for (int j = 0; j < 21; j++) {
			if (FST::execute(machines[j].machine, words[i])) {
				indexLT++;
				flag = 1;

				// добавить в таблицу лексем.
				if (machines[j].lexema == '+' || machines[j].lexema == '-' || machines[j].lexema == '*' || machines[j].lexema == '/') {
					LT::Entry lt = { 'v' , word_array.sn[i], indexLT,machines[j].lexema };
					LT::Add(LexTable, lt);

				}
				else {
					LT::Entry lt = { machines[j].lexema , word_array.sn[i], indexLT };
					LT::Add(LexTable, lt);

				}





				if (strcmp(words[i], "string") == 0) iddatatype = IT::STR;
				else if (strcmp(words[i], "integer") == 0) iddatatype = IT::INT;

				else if (strcmp(words[i], "(") == 0 && functionflag) {
					parflag = 1;
					visibl.emplace(prefix);
				}
				else if (strcmp(words[i], ")") == 0) {
					parflag = 0;
					if (visibl.size() > 1) {
						visibl.pop();
					}

				}
				else if (strcmp(words[i], "}") == 0) {
					visibl.pop();
					prefix = (char *)"";
					functionflag = 0;

				}
				else if (strcmp(words[i], "main") == 0) {
					prefix = words[i];
					visibl.emplace(prefix);
				}


				else if (machines[j].lexema == 'i') {

					// проверка на функцию стандартной библиотеки
					bool libflug = 0;
					for (int k = 0; k < LIBFUNCTIONS; k++) {
						if (strcmp(words[i], LibFunc[k]) == 0) {
							if (!(IT::IsId(IdTable, words[i]))) {

								indexIT++;
								IT::Entry it = { indexLT, words[i], iddatatype, IT::F , 0 };
								IT::Add(IdTable, it);
								prefix = words[i];
								libflug = 1;
								break;
							}
							else {
								prefix = words[i];
								libflug = 1;
								break;
							}
						}
					}
					if (libflug)break;


					if (parflag) idtype = IT::P;
					else if ((strcmp(words[i - 1], "function") == 0) || (strcmp(words[i + 1], "(") == 0)) {
						idtype = IT::F;
						prefix = words[i];
						functionflag = 1;
					}
					else idtype = IT::V;

					id = words[i];
					if (idtype != IT::F) {
						strcat(id, "_");
						strcat(id, visibl.top());
					}

					if (!(IT::IsId(IdTable, id))) {
						// добавить в таблицу индентификаторов
						indexIT++;
						int value;

						IT::Entry it = { indexLT, id , iddatatype, idtype, 0 };

						if (iddatatype == IT::INT) it.value.vint = 0;
						else if (iddatatype == IT::STR) it.value.vstr = { 0, (char *)" " };



						if (strcmp(words[i + 1], "=") == 0 && idtype != IT::F) {
							if (iddatatype == IT::INT) it.value.vint = atoi(words[i + 2]);
							else if (iddatatype == IT::STR) it.value.vstr = { (int)strlen(words[i + 2]) , words[i + 2] };
						}

						IT::Add(IdTable, it);
					}
				}
				else if (machines[j].lexema == 'l') {
					indexIT++;

					if (j == 19) iddatatype = IT::INT;
					else iddatatype = IT::STR;
					//strcat(index_L_, "L");

					IT::Entry it = { indexLT, (char*)"Lit" , iddatatype, IT::L, 0 };
					if (iddatatype == IT::INT) it.value.vint = atoi(words[i]);
					else if (iddatatype == IT::STR) it.value.vstr = { (int)strlen(words[i]) , words[i] };

					IT::Add(IdTable, it);
				}
				break;
			}

		}
		if (flag == 0) {
			//выдать ошибку

			Error::ERROR error = Error::geterrorin(113, word_array.sn[i], -1);
			throw error;

			break;
		}
	}
	Tables.LexTable = LexTable;
	Tables.idTable = IdTable;

	// удалить массив строк
	for (int i = 0; i < nwords; i++) {
		word_array.array[i] = nullptr;
		delete[] word_array.array[i];
	}
	word_array.array = nullptr;
	delete[] word_array.array;




	return Tables;


}

int GetPrior(char s) {
	if (s == '*' || s == '/')return 3;
	else if (s == '-' || s == '+')return 2;
	else if (s == '(')return 1;
	else if (s == ')') return -1;
	else {
		return 0;
	}
}

bool Lex::PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable) {
	stack<LT::Entry> st;
	int getprior;
	bool flag = false;
	int cobaka = 0;
	queue<LT::Entry> myQueue;
	int end;
	for (int i = lextable_pos; i < lextable.size; i++) {
		if (lextable.table[i].lexema == 'i'&&lextable.table[i + 1].lexema == '(') {
			i++;
			flag = true;
		}
		if (lextable.table[i].lexema == ';') {
			end = i;
			break;
		}
		if (lextable.table[i].lexema != ',') {

			getprior = GetPrior(lextable.table[i].lexema);
			if (getprior == 0) {
				myQueue.push(lextable.table[i]);
			}
			if (getprior == 1) {
				st.push(lextable.table[i]);
			}

			if (getprior > 1) {

				while (!st.empty()) {
					if (GetPrior(st.top().lexema) >= getprior) {
						myQueue.push(st.top());
						st.pop();
					}
					else { break; }

				}
				st.push(lextable.table[i]);
			}

			if (getprior == -1) {

				while (GetPrior(st.top().lexema) != 1) {
					myQueue.push(st.top());
					st.pop();
				}
				st.pop();
				if (flag) {
					cout << cobaka + 1 << endl;
					myQueue.push({ '@',myQueue.front().sn,cobaka + 1 });
					cobaka = 0;

					flag = false;
				}
			}

		}
		else {
			cobaka++;
		}


	}
	while (!st.empty()) {
		myQueue.push(st.top());
		st.pop();

	}
	for (int i = lextable_pos; i < end; i++) {
		while (!myQueue.empty()) {
			lextable.table[i] = myQueue.front();
			myQueue.pop();
			i++;
		}
		lextable.table[i].idxTI = i;
		lextable.table[i].lexema = '~';
	}
	return 1;
}





//void Lex::polish_notation(Lex::Tables td)
//{
//
//	int i = 0;
//	for (i; i < td.LexTable.size; i++) {
//		if (td.LexTable.table[i].lexema == (char)'=') {
//
//
//			for (int q = i + 1; q < td.LexTable.size; q++) {
//
//				cout << td.LexTable.table[q].lexema;
//
//
//
//				if (td.LexTable.table[q].lexema == (char)';') {
//					cout << endl;
//					i = q;
//					break;
//				}
//
//
//
//
//
//
//
//
//				// cout << td.LexTable.table[i].lexema << "нахуй" <<"    "<<num<< "    "<< td.LexTable.table[i].sn << endl;
//				// num++;
//			}
//
//
//		}
//	}
//}
