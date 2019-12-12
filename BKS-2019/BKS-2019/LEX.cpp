#include <iostream>
#include "FST.h"
#include "Lex.h"
#include "In.h"
#include "Parm.h"
#include "Log.h"
#include <stack>
#include <queue>
#include <vector>

using namespace std;



//Lex::Word_array Lex::Create_word(const char* s) {
//
//	Lex::Word_array array = {};
//
//	int j = 0;
//	int k = 0;
//	int i = 0;
//	if (s[i] == ' ') i++;
//	int nwords = 0;
//
//	// подсчет слов входной строки.
//	for (int x = i; x <= strlen(s); x++) {
//		if (s[x] == '+' || s[x] == '-' || s[x] == '*' || s[x] == '/' || s[x] == '(' || s[x] == ')' || s[x] == '{' || s[x] == '}' || s[x] == ',' || s[x] == ';' || s[x] == '+' || s[x] == '=') {
//			if (s[x - 1] != '+' && s[x - 1] != '-' && s[x - 1] != '*' && s[x - 1] != '/' && s[x - 1] != '(' && s[x - 1] != ')' && s[x - 1] != '{' && s[x - 1] != '}' && s[x - 1] != ',' && s[x - 1] != ' ' && s[x - 1] != '\n' && s[x - 1] != ';' && s[x - 1] != '=')
//				nwords += 2;
//			else nwords++;
//		}
//
//		else if ((s[x] == ' ' || s[x] == '\n') && s[x + 1] != '\0')
//		{
//			if (s[x - 1] != '+' && s[x - 1] != '-' && s[x - 1] != '*' && s[x - 1] != '/' && s[x - 1] != '(' && s[x - 1] != ')' && s[x - 1] != '{' && s[x - 1] != '}' && s[x - 1] != ',' && s[x - 1] != ' ' && s[x - 1] != '\n' && s[x - 1] != ';' && s[x - 1] != '=')
//				nwords += 1;
//		}
//		else if (s[x] == '\'') {
//			x++;
//
//			while (s[x] != '\'') x++;
//		}
//		else if (s[x] == '\0') {
//			if (s[x - 1] != '+' && s[x - 1] != '-' && s[x - 1] != '*' && s[x - 1] != '/' && s[x - 1] != '(' && s[x - 1] != ')' && s[x - 1] != '{' && s[x - 1] != '}' && s[x - 1] != ',' && s[x - 1] != ' ' && s[x - 1] != '\n' && s[x - 1] != ';' && s[x - 1] != '=')
//				nwords += 1;
//			break;
//		}
//	}
//
//	// подсчет символов в каждом слове.
//	int *letters = new int[nwords];
//	int count = 0;
//	int index = 0;
//	for (int x = i; x < strlen(s) + 1; x++) {
//		count++;
//		if (s[x] == '+' || s[x] == '+' || s[x] == '-' || s[x] == '*' || s[x] == '/' || s[x] == '(' || s[x] == ')' || s[x] == '{' || s[x] == '}' || s[x] == ',' || s[x] == '=') {
//			letters[index] = count - 1;
//			count = 0;
//			index++;
//			letters[index] = 1;
//			index++;
//		}
//
//		if (s[x] == ' ' || s[x] == '\0') {
//			letters[index] = count - 1;
//			count = 0;
//			index++;
//		}
//
//		if (s[x] == '\'') {
//			count = 1;
//			x++;
//			while (s[x] != '\'') {
//				count++;
//				x++;
//			}
//			letters[index] = count;
//			count = 0;
//			index++;
//		}
//
//	}
//
//	array.sn = new int[nwords]; // номера строк каждого слова
//
//	// выделение пам€ти под массив слов
//	char ** word_array = new char *[nwords];
//	for (int z = 0; z < nwords; z++)
//		word_array[z] = new char(letters[z] + 1);
//
//	int ns = 1; // номер строки
//
//	// заполнение массива слов
//	for (i; i <= strlen(s); i++) {
//
//		if (s[i] == '\'') {
//			word_array[k][j] = s[i];
//			j++;
//			i++;
//			while (s[i] != '\'') {
//				word_array[k][j] = s[i];
//				j++;
//				i++;
//			}
//			word_array[k][j++] = s[i];
//			word_array[k][j] = '\0';
//		}
//
//		else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '(' || s[i] == ')' || s[i] == '{' || s[i] == '}' || s[i] == ',' || s[i] == ';' || s[i] == '=') {
//			if (s[i - 1] != '+' && s[i - 1] != '-' && s[i - 1] != '*' && s[i - 1] != '/' && s[i - 1] != '(' && s[i - 1] != ')' && s[i - 1] != '{' && s[i - 1] != '}' && s[i - 1] != ',' && s[i - 1] != ';' && s[i - 1] != '\n' && s[i - 1] != ' ' && s[i - 1] != '=') {
//				array.sn[k] = ns;
//				word_array[k][j] = '\0';
//				k++;
//			}
//
//			j = 0;
//			array.sn[k] = ns;
//			word_array[k][j] = s[i];
//			word_array[k][j + 1] = '\0';
//			k++;
//		}
//		else if (s[i] == ' ') {
//			if (s[i - 1] != '+' && s[i - 1] != '-' && s[i - 1] != '*' && s[i - 1] != '/' && s[i - 1] != '(' && s[i - 1] != ')' && s[i - 1] != '{' && s[i - 1] != '}' && s[i - 1] != ',' && s[i - 1] != ';' && s[i - 1] != '\n' && s[i - 1] != ' ' && s[i - 1] != '=') {
//				array.sn[k] = ns;
//				word_array[k][j] = '\0';
//				k++;
//			}
//
//			j = 0;
//		}
//		else if (s[i] == '\n') {
//			if (s[i - 1] != '+' && s[i - 1] != '-' && s[i - 1] != '*' && s[i - 1] != '/' && s[i - 1] != '(' && s[i - 1] != ')' && s[i - 1] != '{' && s[i - 1] != '}' && s[i - 1] != ',' && s[i - 1] != ';' && s[i - 1] != '\n' && s[i - 1] != ' ' && s[i - 1] != '=') {
//				array.sn[k] = ns;
//				word_array[k][j] = '\0';
//				k++;
//			}
//			ns++;
//			j = 0;
//		}
//		else if (s[i] == '\0') {
//			if (s[i - 1] != '+' && s[i - 1] != '-' && s[i - 1] != '*' && s[i - 1] != '/' && s[i - 1] != '(' && s[i - 1] != ')' && s[i - 1] != '{' && s[i - 1] != '}' && s[i - 1] != ',' && s[i - 1] != ';' && s[i - 1] != '\n' && s[i - 1] != ' ' && s[i - 1] != '=') {
//				array.sn[k] = ns;
//				word_array[k][j] = '\0';
//				k++;
//			}
//			j = 0;
//		}
//		else {
//			word_array[k][j] = s[i];
//			j++;
//		}
//
//	}
//
//
//	array.array = word_array;
//	array.n = nwords;
//
//	for (int e = 0; e < nwords; e++) {
//		word_array[i] = nullptr;
//		delete[] word_array[i];
//	}
//	word_array = nullptr;
//	delete[] word_array;
//
//
//	return array;
//}
//const char*  Lex::del_probel(const char* s) {
//
//
//	char* text = new char[strlen(s) + 1];
//	int j = 0;
//	for (int i = 0; i <= strlen(s); i++) {
//
//		if (s[i] == ' ') {
//			while (s[i] == ' ') i++;
//			if (s[i] != '\n' && s[i] != '\0') text[j++] = s[i - 1];
//		}
//
//		if (s[i] == '\n' && s[i + 1] == '\0') i++;
//
//		if (s[i] == '\n' && (s[i + 1] == ' ' || s[i + 1] == '\n')) {
//			text[j++] = s[i];
//			i++;
//			while (s[i] == ' ' || s[i] == '\n') i++;
//		}
//		text[j] = s[i];
//		j++;
//	}
//	text[j] = '\0';
//	return text;
//}


//
//Lex::Tables Lex::Lex_analyz(const char *s) {
//
//	char LibFunc[2][225] = { "substr", "strlen" };
//	const char* text = Lex::del_probel(s);
//	Lex::Word_array word_array = Lex::Create_word(text);
//	char ** words = word_array.array;
//	int nwords = word_array.n;
//
//
//
//	LT::LexTable LexTable = LT::Create();
//	IT::IdTable  IdTable = IT::Create();
//	Tables Tables = {};
//	/*Lex::Machines machines[21] = {
//
//		{LEX_INTEGER   , FST::FST GRAPH_integer        },
//		{LEX_STRING    , FST::FST GRAPH_string         },
//		{LEX_PRINT     , FST::FST GRAPH_print          },
//		{LEX_FUNCTION  , FST::FST GRAPH_function       },
//		{LEX_DECLARE   , FST::FST GRAPH_declare        },
//		{LEX_MAIN      , FST::FST GRAPH_main           },
//		{LEX_RETURN    , FST::FST GRAPH_return         },
//		{LEX_COMMA     , FST::FST GRAPH_COMMA          },
//		{LEX_LEFTHESIS , FST::FST GRAPH_LEFTHESIS      },
//		{LEX_RIGHTHESIS, FST::FST GRAPH_RIGHTHESIS     },
//		{LEX_LEFTBRACE , FST::FST GRAPH_LEFTBRCE       },
//		{LEX_BRACELET  , FST::FST GRAPH_BRACELET       },
//		{LEX_DIRSLASH  , FST::FST GRAPH_DIRSLASH       },
//		{LEX_MINUS     , FST::FST GRAPH_MINUS          },
//		{LEX_PLUS      , FST::FST GRAPH_PLUS           },
//		{LEX_SEMICOLON , FST::FST GRAPH_SEMICOLON      },
//		{LEX_STAR      , FST::FST GRAPH_START          },
//		{LEX_EQUAL     , FST::FST GRAPH_EQUAL          },
//		{LEX_ID		   , FST::FST GRAPH_id             },
//		{LEX_LITERAL   , FST::FST GRAPH_integer_literal},
//		{LEX_LITERAL   , FST::FST GRAPH_string_literal },
//
//	};*/
//
//	int indexLT = 0;
//
//	bool flag = 0;
//	char* index_L_ = (char*)"";
//
//	int indexIT = 0;
//	IT::IDDATATYPE iddatatype;
//	IT::IDTYPE idtype = IT::V;
//	bool parflag = 0;
//	bool functionflag = 0;
//	char * prefix = (char *)"";
//	char * id;
//	stack<char*> visibl;
//
//	for (int i = 0; i < nwords; i++) {
//		flag = 0;
//
//		for (int j = 0; j < 21; j++) {
//			if (FST::execute(machines[j].machine, words[i])) {
//				indexLT++;
//				flag = 1;
//
//				// добавить в таблицу лексем.
//				if (machines[j].lexema == '+' || machines[j].lexema == '-' || machines[j].lexema == '*' || machines[j].lexema == '/') {
//					LT::Entry lt = { 'v' , word_array.sn[i], indexLT,machines[j].lexema };
//					LT::Add(LexTable, lt);
//
//				}
//				else {
//					LT::Entry lt = { machines[j].lexema , word_array.sn[i], indexLT };
//					LT::Add(LexTable, lt);
//
//				}
//
//
//
//
//
//				if (strcmp(words[i], "string") == 0) iddatatype = IT::STR;
//				else if (strcmp(words[i], "integer") == 0) iddatatype = IT::INT;
//
//				else if (strcmp(words[i], "(") == 0 && functionflag) {
//					parflag = 1;
//					visibl.emplace(prefix);
//				}
//				else if (strcmp(words[i], ")") == 0) {
//					parflag = 0;
//					if (visibl.size() > 1) {
//						visibl.pop();
//					}
//
//				}
//				else if (strcmp(words[i], "}") == 0) {
//					visibl.pop();
//					prefix = (char *)"";
//					functionflag = 0;
//
//				}
//				else if (strcmp(words[i], "main") == 0) {
//					prefix = words[i];
//					visibl.emplace(prefix);
//				}
//
//
//				else if (machines[j].lexema == 'i') {
//
//					// проверка на функцию стандартной библиотеки
//					bool libflug = 0;
//					for (int k = 0; k < LIBFUNCTIONS; k++) {
//						if (strcmp(words[i], LibFunc[k]) == 0) {
//							if (!(IT::IsId(IdTable, words[i]))) {
//
//								indexIT++;
//								IT::Entry it = { indexLT, words[i], iddatatype, IT::F , 0 };
//								IT::Add(IdTable, it);
//								prefix = words[i];
//								libflug = 1;
//								break;
//							}
//							else {
//								prefix = words[i];
//								libflug = 1;
//								break;
//							}
//						}
//					}
//					if (libflug)break;
//
//
//					if (parflag) idtype = IT::P;
//					else if ((strcmp(words[i - 1], "function") == 0) || (strcmp(words[i + 1], "(") == 0)) {
//						idtype = IT::F;
//						prefix = words[i];
//						functionflag = 1;
//					}
//					else idtype = IT::V;
//
//					id = words[i];
//					if (idtype != IT::F) {
//						strcat(id, "_");
//						strcat(id, visibl.top());
//					}
//
//					if (!(IT::IsId(IdTable, id))) {
//						// добавить в таблицу индентификаторов
//						indexIT++;
//						int value;
//
//						IT::Entry it = { indexLT, id , iddatatype, idtype, 0 };
//
//						if (iddatatype == IT::INT) it.value.vint = 0;
//						else if (iddatatype == IT::STR) it.value.vstr = { 0, (char *)" " };
//
//
//
//						if (strcmp(words[i + 1], "=") == 0 && idtype != IT::F) {
//							if (iddatatype == IT::INT) it.value.vint = atoi(words[i + 2]);
//							else if (iddatatype == IT::STR) it.value.vstr = { (int)strlen(words[i + 2]) , words[i + 2] };
//						}
//
//						IT::Add(IdTable, it);
//					}
//				}
//				else if (machines[j].lexema == 'l') {
//					indexIT++;
//
//					if (j == 19) iddatatype = IT::INT;
//					else iddatatype = IT::STR;
//					//strcat(index_L_, "L");
//
//					IT::Entry it = { indexLT, (char*)"Lit" , iddatatype, IT::L, 0 };
//					if (iddatatype == IT::INT) it.value.vint = atoi(words[i]);
//					else if (iddatatype == IT::STR) it.value.vstr = { (int)strlen(words[i]) , words[i] };
//
//					IT::Add(IdTable, it);
//				}
//				break;
//			}
//
//		}
//		if (flag == 0) {
//			//выдать ошибку
//
//			Error::ERROR error = Error::geterrorin(113, word_array.sn[i], -1);
//			throw error;
//
//			break;
//		}
//	}
//	Tables.LexTable = LexTable;
//	Tables.idTable = IdTable;
//
//	// удалить массив строк
//	for (int i = 0; i < nwords; i++) {
//		word_array.array[i] = nullptr;
//		delete[] word_array.array[i];
//	}
//	word_array.array = nullptr;
//	delete[] word_array.array;
//
//
//
//
//	return Tables;
//
//
//}

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

int Lex::ret_index_for_expression(int pos, std::vector<Lex::Par_function> par_func) {
	//cout <<pos << "  ff     позици€" << endl;
	for (int i = 0; i < par_func.size(); i++) {
		//cout << par_func[i].indxLT << "       позици€"<<endl;
		if (pos == par_func[i].indxLT) {
			return pos;
		}
	}
	return -1;
	
}

void Lex::Sem_analiz(Lex::Tables table) {
	Lex::Par_function par_function;
	std::vector<Lex::Par_function> par_func;
	int pos_in_vector = 0;
	int pos_expression = 0;
	int par_vs_funcr = 0;
	int index = 0;
	int pos_function_for_return = 0;
	int pos_function_for_r_i = 0;
	bool flagfunction = false;
	bool flag_par_function = false;
	bool flag_expression = false;
	int m;
	int q;
	int count = 0;
	for (int i = 0; i < table.LexTable.size; i++) {

		if (table.LexTable.table[i].lexema == 'f') {
			flagfunction = true;
			pos_function_for_return = i + 1;
		}
		else if (flag_expression && table.LexTable.table[i].lexema == ';') {
			flag_expression = false;
		}
		else if (table.LexTable.table[i].lexema == '?') {//проверка на типы if

			if (table.idTable.table[table.LexTable.table[i + 4].idxTI].iddatatype != IT::INT || table.idTable.table[table.LexTable.table[i + 2].idxTI].iddatatype != IT::INT) {
				if (table.LexTable.table[i+2].lexema != 'T' || table.LexTable.table[i+2].lexema != 'F') {
					if (table.idTable.table[table.LexTable.table[i + 2].idxTI].iddatatype != IT::BOOL) {
					Error::ERROR error = Error::geterrorin(119, table.LexTable.table[i].sn + 1, table.LexTable.table[i].indexLT);
					throw error;
					}
				}
				
			}
			

			
		}
		else if (flag_expression && table.LexTable.table[i].lexema == 'i' && table.LexTable.table[i + 1].lexema == '(') {

			m = 0;
			if (strcmp(table.idTable.table[table.LexTable.table[i].idxTI].id , "stringtoint")==0 || strcmp(table.idTable.table[table.LexTable.table[i].idxTI].id, "strlen")==0 ) {

				
				if (table.idTable.table[table.LexTable.table[pos_expression].idxTI].iddatatype != IT::INT) {
					Error::ERROR error = Error::geterrorin(118, table.LexTable.table[i].sn + 1, table.LexTable.table[i].indexLT);
					throw error;
				}
				if (table.idTable.table[table.LexTable.table[i + 2].idxTI].iddatatype != IT::STR ) {
					Error::ERROR error = Error::geterrorin(118, table.LexTable.table[i].sn + 1, table.LexTable.table[i].indexLT);
					throw error;
				}
				if (table.LexTable.table[i + 3].lexema != ')') {
					Error::ERROR error = Error::geterrorin(118, table.LexTable.table[i].sn + 1, table.LexTable.table[i].indexLT);
					throw error;
				}
				i = i + 3;
			}
			else {
				pos_in_vector = ret_index_for_expression(table.LexTable.table[i].idxTI, par_func);
				//	cout << table.idTable.table[table.LexTable.table[pos_expression].idxTI].id << endl;
					//cout << table.idTable.table[pos_in_vector].id << endl;
				if (table.idTable.table[table.LexTable.table[pos_expression].idxTI].iddatatype != table.idTable.table[pos_in_vector].iddatatype) {
					Error::ERROR error = Error::geterrorin(117, table.LexTable.table[i].sn + 1, table.LexTable.table[i].indexLT);
					throw error;
				}

				for (; m < par_func.size(); m++) {
					if (pos_in_vector == par_func[m].indxLT) {
						break;
					}
				}
				for (q = i + 1; i < table.LexTable.size; q++) {
					if (par_func[m].type.size() < par_vs_funcr) {

						Error::ERROR error = Error::geterrorin(118, table.LexTable.table[i].sn + 1, table.LexTable.table[i].indexLT);
						throw error;
					}
					if (table.LexTable.table[q].lexema == 'i') {
						if (par_func[m].type.size() == par_vs_funcr) {

							Error::ERROR error = Error::geterrorin(118, table.LexTable.table[q].sn + 1, table.LexTable.table[q].indexLT);
							throw error;
						}
						if (table.idTable.table[table.LexTable.table[q].idxTI].iddatatype != par_func[m].type[par_vs_funcr]) {//
							Error::ERROR error = Error::geterrorin(118, table.LexTable.table[q].sn + 1, table.LexTable.table[q].indexLT);
							throw error;
						}
						else {
							par_vs_funcr++;
						}
					}
					else if (table.LexTable.table[q].lexema == 'l' || table.LexTable.table[q].lexema == 'T' || table.LexTable.table[q].lexema == 'F') {
						if (par_func[m].type.size() == par_vs_funcr) {

							Error::ERROR error = Error::geterrorin(118, table.LexTable.table[q].sn + 1, table.LexTable.table[q].indexLT);
							throw error;
						}
						if (table.idTable.table[table.LexTable.table[q].idxTI].iddatatype != par_func[m].type[par_vs_funcr]) {
							Error::ERROR error = Error::geterrorin(118, table.LexTable.table[q].sn + 1, table.LexTable.table[q].indexLT);
							throw error;
						}
						else {
							par_vs_funcr++;
						}
					}
					else if (table.LexTable.table[q].lexema == ')') {
						if (par_func[m].type.size() > par_vs_funcr) {

							Error::ERROR error = Error::geterrorin(118, table.LexTable.table[q].sn + 1, table.LexTable.table[q].indexLT);
							throw error;
						}
						break;
					}
					//par_vs_funcr++;
				}

				i = q;
			}
				par_vs_funcr = 0;
			
		}
		else if (flag_expression && table.LexTable.table[i].lexema == 'i' &&table.LexTable.table[i+1].lexema == 'v') {
			for (q = i + 1; i < table.LexTable.size; q++) {
				if (table.idTable.table[table.LexTable.table[q].idxTI].iddatatype != IT::INT) {
					Error::ERROR error = Error::geterrorin(129, table.LexTable.table[q].sn + 1, table.LexTable.table[q].indexLT);
					throw error;
				}
				else if (table.LexTable.table[q].lexema == ';') {
					break;
				}
			}
			i = q;
		}
		else if (flag_expression && (table.LexTable.table[i].lexema == 'i'|| table.LexTable.table[i].lexema == 'T'|| table.LexTable.table[i].lexema == 'F'|| table.LexTable.table[i].lexema == 'l')) {
			if (table.LexTable.table[i].lexema == 'F' || table.LexTable.table[i].lexema == 'T') {
				if (table.idTable.table[table.LexTable.table[pos_expression].idxTI].iddatatype != IT::BOOL) {
					Error::ERROR error = Error::geterrorin(117, table.LexTable.table[i].sn + 1, table.LexTable.table[i].indexLT);
					throw error;
				}
			}
			else if (table.idTable.table[table.LexTable.table[pos_expression].idxTI].iddatatype != table.idTable.table[table.LexTable.table[i].idxTI].iddatatype) {
				Error::ERROR error = Error::geterrorin(117, table.LexTable.table[i].sn + 1, table.LexTable.table[i].indexLT);
				throw error;
			}
		}
		else if (table.LexTable.table[i].lexema == '(' && table.LexTable.table[i - 1].lexema == 'i'&&table.LexTable.table[i - 2].lexema == 'f') {
			flag_par_function = true;
			par_function.indxLT = table.LexTable.table[i-1].idxTI;
		}
		
		else if (flag_par_function && table.LexTable.table[i].lexema == ')') {
			par_func.push_back(par_function);
			par_function = {};
			flag_par_function = false;
		}
		else if (flag_par_function &&table.LexTable.table[i].lexema == 'i') {			
			par_function.type.push_back(table.idTable.table[table.LexTable.table[i].idxTI].iddatatype);
		}

		else if (!flag_par_function &&table.LexTable.table[i].lexema == 'i' &&table.LexTable.table[i + 1].lexema == '=') {
			pos_expression = i;
			flag_expression = true;
		}

		else if (table.LexTable.table[i].lexema == '}' && flagfunction) {
			flagfunction = false;
		}
		else if (table.LexTable.table[i].lexema == 'r') {
			pos_function_for_r_i = i + 1;
			 if (table.LexTable.table[pos_function_for_r_i].lexema == 'T') {
				if (table.idTable.table[table.LexTable.table[pos_function_for_return].idxTI].iddatatype != IT::BOOL) {
					Error::ERROR error = Error::geterrorin(116, table.LexTable.table[pos_function_for_r_i].sn+1, table.LexTable.table[pos_function_for_r_i].indexLT);
					throw error;
				}
			}

			else if (table.LexTable.table[pos_function_for_r_i].lexema == 'F') {
				if (table.idTable.table[table.LexTable.table[pos_function_for_return].idxTI].iddatatype != IT::BOOL) {

					Error::ERROR error = Error::geterrorin(116, table.LexTable.table[pos_function_for_r_i].sn+1, table.LexTable.table[pos_function_for_r_i].indexLT);
					throw error;
				
				}
			}

			else if (table.idTable.table[table.LexTable.table[pos_function_for_return].idxTI].iddatatype != table.idTable.table[table.LexTable.table[pos_function_for_r_i].idxTI].iddatatype) {
				
				Error::ERROR error = Error::geterrorin(116, table.LexTable.table[pos_function_for_r_i].sn+1, table.LexTable.table[pos_function_for_r_i].indexLT);
				throw error;
			}
			


		}




	}








}


Lex::Tables Lex::Lex_analyz_new(In::IN in) {
	char LibFunc[2][225] = { "stringtoint", "strlen" };
	bool libflag = 0;
	int m = 0;
	LT::LexTable LexTable = LT::Create();
	IT::IdTable  IdTable = IT::Create();
	Tables Tables = {};
	Lex::Machines machines[N_GRAPHS] = {

		{LEX_INT            , FST::FST GRAPH_int						 },//1типы int
		{LEX_STRING         , FST::FST GRAPH_string						 },//2 string
		{LEX_BOOL           , FST::FST GRAPH_bool						 },//3 bool
		{LEX_FUNCTION       , FST::FST GRAPH_function				     },//4
		{LEX_PRINT            , FST::FST GRAPH_print				     },//5
		{LEX_IF            , FST::FST GRAPH_if							 },//6
		{LEX_MAIN            , FST::FST GRAPH_main						 },//8
		{LEX_DEC            , FST::FST GRAPH_dec						 },//9
		{LEX_RETURN            , FST::FST GRAPH_return			         },//10
		{LEX_TRUE         , FST::FST GRAPH_true						     },//11
		{LEX_FALSE            , FST::FST GRAPH_false				     },//12	
		{LEX_EQUAL_IF            , FST::FST GRAPH_EQUAL_IF				 },//7		
		{LEX_SEMICOLON            , FST::FST GRAPH_SEMICOLON			 },//17
		{LEX_COMMA            , FST::FST GRAPH_COMMA					 },//18
		{LEX_LEFTBRACE            , FST::FST GRAPH_LEFTBRCE			     },//19
		{LEX_BRACELET           , FST::FST GRAPH_BRACELET				 },//20
		{LEX_LEFTHESIS            , FST::FST GRAPH_LEFTHESIS			 },//21
		{LEX_RIGHTHESIS           , FST::FST GRAPH_RIGHTHESIS		     },//22
		{LEX_PLUS         , FST::FST GRAPH_PLUS						     },//23
		{LEX_MINUS           , FST::FST GRAPH_MINUS					     },//24
		{LEX_STAR           , FST::FST GRAPH_START						 },//25
		{LEX_DIRSLASH           , FST::FST GRAPH_DIRSLASH			     },//26
		{LEX_EQUAL         , FST::FST GRAPH_EQUAL					     },//27
		{LEX_PERSENT           , FST::FST GRAPH_PERSENT				     },//28		
		{LEX_LITERAL            , FST::FST GRAPH_integer_literal10       },//13
		{LEX_LITERAL         , FST::FST GRAPH_integer_literal8           },//14
		{LEX_LITERAL        , FST::FST GRAPH_string_literal				 },//16
		{LEX_ID           , FST::FST GRAPH_id							 },//15	

	};
	int sn = 0;
	int pos_LT = 0;
	int indexLT = 0;
	char* word = new char[256];
	char* id = new char[256];
	int word_it = 0;
	int i = 0;
	bool flag_in_word = false;
	bool flag_error = false;
	int  vs_func = 0;
	//
	
	int index_lit = 0;
	int indexIT = -1;
	IT::IDDATATYPE iddatatype = IT::NODEF;
	IT::IDTYPE idtype = IT::V;
	bool parflag = 0;
	bool functionflag = 0;
	
	bool flag_main = false;
	//дл€ выражений
	bool Pflag = 0;
	int pos = 0;
	char * prefix = (char *)"";
	//char * id;
	stack <char*> st;

	






	while (in.text[i] != '\0')
	{
		word_it = 0;
		if (in.text[i] == '\n') {
			i++;
			indexLT++;	//номер строки
			pos_LT = 0;
			flag_error = true;
		}
		else if (in.code[in.text[i]] == in.P) {
			i++;
			flag_error = true;
		}
		else if (in.text[i] == '\'') {
			word[word_it] = in.text[i];
			word_it++;
			i++;
			if (in.text[i] == '\'') {
				word[word_it] = in.text[i];
				word_it++;
				//i++;
				pos_LT++;
			}
			else {
				while (in.text[i] != '\'')
				{
					word[word_it] = in.text[i];
					word_it++;
					i++;
					if (in.text[i] == '\'') {
						word[word_it] = in.text[i];
						word_it++;

					}

				}
			}
			word[word_it] = '\0';
			//	cout << word << "|";
			i++;
			flag_in_word = true;
			sn++;
		}//
		else if (in.code[in.text[i]] == in.S) {

				if(in.text[i]=='-' && (machines[m].lexema=='='|| machines[m].lexema == '-' || machines[m].lexema == '+' || machines[m].lexema == '*' || machines[m].lexema == '=' || machines[m].lexema == '/' || machines[m].lexema == '%' || machines[m].lexema == '=='
					|| machines[m].lexema == '=' || machines[m].lexema == ')' || machines[m].lexema == '(' || machines[m].lexema == 'r'  )){
					word[word_it] = in.text[i];
					i++;
					word_it++;
					while (in.text[i] != '\0' ) {
					if (in.code[in.text[i]] == in.P || in.code[in.text[i]] == in.S  || in.text[i] == ';') {
						word[word_it] = '\0';
						
						
						break;
					}
						word[word_it] = in.text[i];
						i++;
						word_it++;

					
					}
				}
				else if (in.text[i] == '-' &&in.text[i + 1] == '-') {
					word[word_it] = in.text[i];
					i++;
					word_it++;
				}
			else if (in.text[i] == in.text[i+1]) {
				word[word_it] = in.text[i];
				i++;
				word_it++;
				word[word_it] = in.text[i];
				i++;
				word_it++;
			}
			else {
				word[word_it] = in.text[i];
				i++;
				word_it++;
			}

			word[word_it] = '\0';
			flag_in_word = true;
			//sn++;
			pos_LT++;
			//cout << word << "|";
		}
		else
		{
			while (in.code[in.text[i]] != in.S && in.code[in.text[i]] != in.P) {
				word[word_it] = in.text[i];
				i++;
				word_it++;

			}
			word[word_it] = '\0';
			flag_in_word = true;
			//sn++;
			pos_LT++;
			//cout << word <<"|";
		}
		if (flag_in_word) {
			LT::Entry lt;
			flag_error = true;

			for (m = 0; m < N_GRAPHS; m++) {

				if (FST::execute(machines[m].machine, word))
				{					
					if ( strcmp(word, "==") == 0 || strcmp(word, "-") == 0 || strcmp(word, "+") == 0 || strcmp(word, "*") == 0 || strcmp(word, "/") == 0 || strcmp(word, "%") == 0) {
						if (strcmp(word, "==") == 0) {
							lt = { 's' ,indexLT,pos_LT ,indexIT,machines[m].lexema };
						}
						else {


							lt = { 'v' ,indexLT,pos_LT ,indexIT,machines[m].lexema };
						}
					}
					else {
						 lt = { machines[m].lexema ,indexLT,pos_LT,indexIT };
						
					}

					flag_error = true;
					break;
				}
				else {
					flag_error = false;
				}
			}
			if (strcmp(word, "int") == 0)iddatatype = IT::INT;
			else if (strcmp(word, "string") == 0)iddatatype = IT::STR;
			else if (strcmp(word, "bool") == 0)iddatatype = IT::BOOL;
			else if (strcmp(word, "function") == 0)idtype = IT::F;
			else if (strcmp(word, "main") == 0) {
				st.push(word);
				//idtype = IT::F;
				flag_main = true;
			}
			else if (idtype == IT::F && machines[m].lexema == 'i') {

				id = word;
				if (IT::IsId(IdTable, id)== TI_NULLIDX) {
					if (iddatatype != IT::NODEF) {
						st.push(word);
						IT::Entry it = { LexTable.size,id , iddatatype, idtype, 0 };
						IT::Add(IdTable, it);
						indexIT = IdTable.size-1;
						iddatatype = IT::NODEF;
					}
					else {
						cout << word << endl;
						Error::ERROR error = Error::geterrorin(115, indexLT+1, pos_LT);
						throw error;
						break;
					}

				}
				else {
					indexIT = IT::IsId(IdTable, id);
				}
				//доб в табл идентификаторов				
			}
			else if (strcmp(word, "(") == 0 && idtype == IT::F) {
				idtype = IT::P;
			}
			else if (idtype == IT::P && strcmp(word, ")") == 0) {
				idtype = IT::V;
			}
			else if (machines[m].lexema == 'l' || machines[m].lexema == 'T' || machines[m].lexema == 'F') {
				if (!st.empty()) {
					id = word;


					//IT::Entry it;
					if (m == 24) {

						IT::Entry it = { LexTable.size, id , IT::INT, IT::L, 0 };
						it.value.vint = atoi(id);
						IT::Add(IdTable, it);
						indexIT = IdTable.size - 1;
					}
					else if (m == 25) {
						IT::Entry it = { LexTable.size, id , IT::INT, IT::L, 0 };
						it.value.vint = atoi(id);
						IT::Add(IdTable, it);
						indexIT = IdTable.size - 1;
					}

					else if (strcmp(id, "true") == 0) {

						IT::Entry it = { LexTable.size, id , IT::BOOL, IT::L, 1 };
						IT::Add(IdTable, it);
						indexIT = IdTable.size - 1;
						
					}
					else if (strcmp(id, "false") == 0) {

						IT::Entry it = { LexTable.size, id , IT::BOOL, IT::L, 0 };
						IT::Add(IdTable, it);
						indexIT = IdTable.size - 1;
					}
					else if (m == 26) {
						IT::Entry it = { LexTable.size, id , IT::STR,  IT::L, 0 };
						it.value.vstr = { (int)strlen(word) , word };
						IT::Add(IdTable, it);
						indexIT = IdTable.size - 1;
					//IT::Entry it = { LexTable.size, id , IT::STR, IT::L, 0 };
						
						

					}
				}
				else {
					//cout << word << endl;
					Error::ERROR error = Error::geterrorin(115, indexLT+1, pos_LT);
					throw error;
					break;
				}
			}
			else if (machines[m].lexema == 'i') {
				if (!st.empty()) {
					if (strcmp(word, LibFunc[0]) == 0 ) {
						IT::Entry it = { LexTable.size, word , IT::INT, IT::F, 0 };
						IT::Add(IdTable, it);
						indexIT = IdTable.size - 1;
						iddatatype = IT::NODEF;
					}
					else if (strcmp(word, LibFunc[1]) == 0) {
						IT::Entry it = { LexTable.size, word , IT::INT, IT::F, 0 };
						IT::Add(IdTable, it);
						indexIT = IdTable.size - 1;
						iddatatype = IT::NODEF;
					}
					else if (idtype == IT::F || idtype == IT::P) {
						id = word;
						strcat(id, "_");
						strcat(id, st.top());
						if (IT::IsId(IdTable, id) == TI_NULLIDX) {
							if (iddatatype != IT::NODEF) {
								IT::Entry it = { LexTable.size, id , iddatatype, idtype, 0 };
								IT::Add(IdTable, it);
								indexIT = IdTable.size-1;
								iddatatype = IT::NODEF;
							}
							else {
							//	cout << word << endl;
								Error::ERROR error = Error::geterrorin(115, indexLT+1, pos_LT);
								throw error;
								break;
							}
						}
						else {
							indexIT = IT::IsId(IdTable, id);
						}
						
					}
					else if (idtype == IT::V) {
						id = word;
						vs_func = IT::IsId(IdTable,word);
						//cout << vs_func << "   позици€€€€€€€€€€€€     " <<word<< endl;
						if (IdTable.table[vs_func].idtype != IT::F) {
							


							strcat(id, "_");
							strcat(id, st.top());
							if (IT::IsId(IdTable, id) == TI_NULLIDX) {

								if (iddatatype != IT::NODEF) {
									IT::Entry it = { LexTable.size, id , iddatatype, idtype, 0 };

									IT::Add(IdTable, it);
									indexIT = IdTable.size - 1;
									iddatatype = IT::NODEF;
								}
								else {

							
							//	cout << word << endl;
								Error::ERROR error = Error::geterrorin(115, indexLT + 1, pos_LT);
								throw error;
								break;
							

								}
							}
							else {
								indexIT = IT::IsId(IdTable, id);
							}
						}
						else {
							indexIT = IT::IsId(IdTable, word);
		//					cout << indexIT << "   позици€€€€€€€€€€€€    сработал else  " << word << endl;
						}
					}
				}
				else
				{
					Error::ERROR error = Error::geterrorin(114, indexLT+1, pos_LT);
					throw error;
					break;
				}
			}
			lt.idxTI = indexIT;
			LT::Add(LexTable, lt);
			indexIT = -1;
		}









		if (!flag_error) {
			cout << word << endl;
			Error::ERROR error = Error::geterrorin(113, indexLT, pos_LT);
			throw error;
			break;
		}
		
		word = NULL;
		word = new char[256];
		flag_in_word = false;
		flag_error = false;


	}

	

	
		Tables.LexTable = LexTable;
        Tables.idTable = IdTable;
	return Tables;
	
}









































//In::IN Del_probel(In::IN in) {
//	char* word;
//	int word_it = 0;
//	int i = 0;
//	while (in.text[i] != '\0')
//	{
//		if (in.text[i] == '\'') {
//			word[word_it] = in.text[i];
//			word_it++;
//			i++;
//			while (in.text[i] != '\'')
//			{
//				word[word_it] = in.text[i];
//				word_it++;
//				i++;
//			}
//		}//
//
//
////		if(){}
//	}
//}


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
