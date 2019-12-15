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
			if (strcmp(table.idTable.table[table.LexTable.table[i].idxTI].id , "stringtoint")==0 || strcmp(table.idTable.table[table.LexTable.table[i].idxTI].id, "strlen1")==0 ) {

				
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

int conv(char* s)
{
	int q = 1;
	int res = 0;
	if (s[0] == '-')q = -1;
	for (int i = 2; i < strlen(s); ++i)
	{
		res *= 8;
		res += (s[i] - '0');
	}
	res = res * q;
	return res;
}
int conv1(char* arr) {
	int N = strlen(arr);
	int res = 0;
	int i = 0;
	int col = 1;
	int f = 1;
	if (arr[0] == '-') {
		f = -1; 
		i = 1;
	}

	for (; i < N; i++) {
		col = col * 10;
	}
	col = col / 10;
	if (f == -1) {
		i = 1;
	}
	else {
		i = 0;
	}
	for (; i < N; i++) {
		res += ((int)arr[i] - (int)'0')*col;
		col = col / 10;
	}
	res = res * f;
	return res;
}
Lex::Tables Lex::Lex_analyz_new(In::IN in) {
	char LibFunc[2][225] = { "stringtoint", "strlen1" };
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
		{LEX_LITERAL         , FST::FST GRAPH_integer_literal8           },//14		
		{LEX_LITERAL            , FST::FST GRAPH_integer_literal10       },//13		
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
	bool flag_mines = false;
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

			if (in.text[i] == '-' &&in.text[i + 1] == '-') {
				flag_mines = true;
				word[word_it] = in.text[i];
				i++;
				word_it++;
			}
			else if (in.text[i] == '-' && (machines[m].lexema == '=' || machines[m].lexema == '-' || machines[m].lexema == '+' || machines[m].lexema == '*' || machines[m].lexema == '=' || machines[m].lexema == '/' || machines[m].lexema == '%' || machines[m].lexema == '=='
				    || machines[m].lexema == '=' || machines[m].lexema == ')' || machines[m].lexema == '(' || machines[m].lexema == 'r')) {
					word[word_it] = in.text[i];
					i++;
					word_it++;
					while (in.text[i] != '\0') {
					if (!flag_mines&&(in.code[in.text[i]] == in.P || in.code[in.text[i]] == in.S || in.text[i] == ';'||in.text[i]=='%'|| in.text[i] == '1'|| in.text[i] == '2'|| in.text[i] == '3'
						||in.text[i] == '4'||in.text[i] == '5'|| in.text[i] == '6'|| in.text[i] == '7'|| in.text[i] == '8'|| in.text[i] == '9'|| in.text[i] == '9'|| in.text[i] == '0')) {
						word[word_it] = '\0';


						break;
					}
					else if (flag_mines && (in.code[in.text[i]] == in.P || in.code[in.text[i]] == in.S || in.text[i] == ';')) {
						flag_mines = false;
						word[word_it] = '\0';


						break;
					}
					word[word_it] = in.text[i];
					i++;
					word_it++;


					}
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
			while (in.code[in.text[i]] != in.S && in.code[in.text[i]] != in.P) {//выдел€ем слова
				if (in.text[i] == '%' || in.text[i] == '*' || in.text[i] == '-' || in.text[i] == '+' || in.text[i] == '/') {
					break;
				}
				word[word_it] = in.text[i];
				i++;
				word_it++;

			}
			word[word_it] = '\0';
			flag_in_word = true;
			//sn++;
			pos_LT++;
			cout << word <<"|";
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
					if (m + 1 == N_GRAPHS) {
						if (std::strlen(word) < 3) {
							Error::ERROR error = Error::geterrorin(130, indexLT + 1, pos_LT);
							throw error;
							break;
						}
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
					//	cout << word << endl;
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

						//cout << word;
						IT::Entry it = { LexTable.size, id , IT::INT, IT::L, 0 };
						it.value.vint = conv(id);
					//	it.value.vint = atoi(id);
						IT::Add(IdTable, it);
						indexIT = IdTable.size - 1;
					}
					else if (m == 25) {
						IT::Entry it = { LexTable.size, id , IT::INT, IT::L, 0 };
						it.value.vint = conv1(id);
						//it.value.vint = conv(id);
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
			cout<<endl << word << endl;
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





