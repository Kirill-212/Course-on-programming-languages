#include "GEN.h"
#include <fstream>
#include<iostream>
#include<string>
#include"Error.h"
using namespace std;

void GEN::FixID(Lex::Tables& tables)
{
	int nLiteral = 1;
	char* buffer = new char[256];
	char* L = new char[256];
	L[0] = 'L';
	L[1] = '\0';

	for (int i = 0; i < tables.idTable.size; i++)
	{
		if (tables.idTable.table[i].idtype == IT::L)
		{
			itoa(nLiteral, buffer, 10);
			strcat(L, buffer);
			tables.idTable.table[i].id = L;
			L = NULL;
			buffer = NULL;
			L = new char(256);
			L[0] = 'L';
			L[1] = '\0';
			buffer = new char(256);
			nLiteral++;
		}
	}
	L = NULL;
	delete[]L;
	buffer = NULL;
	delete[]buffer;
}

void GEN::GetGeN(wchar_t* file, Lex::Tables td) {
	int i = 0;
	int flag = 0;
	GEN::Gen_text Gen_txt;
	bool par_flag = true;
	bool function_flag = false;
	bool flag_if = false;
	int pos_if = 0;
	int pos_for_function = 0;
	int pos_expression = 0;
	bool flag_main = false;
	int flag_if_one = 1;
	int col_flag_if = 0;
	char* arr = new char[256];
	//bool flag_first_op = true;
	std::cout << "start" << endl;
	ofstream out;
	for (; i < td.LexTable.size; i++) {
		if (td.LexTable.table[i].lexema == 'l' || td.LexTable.table[i].lexema == 'T' || td.LexTable.table[i].lexema == 'F') {//литералы

			if (td.idTable.table[td.LexTable.table[i].idxTI].iddatatype == IT::INT) {
				Gen_txt.CONST += td.idTable.table[td.LexTable.table[i].idxTI].id;
				Gen_txt.CONST += "\t sword  ";
				Gen_txt.CONST += "\t";
				//cout << td.idTable.table[td.LexTable.table[i].idxTI].value.vint;
				Gen_txt.CONST += std::to_string(td.idTable.table[td.LexTable.table[i].idxTI].value.vint);
				Gen_txt.CONST += "\n";
			}
			else if (td.idTable.table[td.LexTable.table[i].idxTI].iddatatype == IT::STR) {

				Gen_txt.CONST += td.idTable.table[td.LexTable.table[i].idxTI].id;
				Gen_txt.CONST += "\t DB  ";
				Gen_txt.CONST += "\t";
				Gen_txt.CONST += td.idTable.table[td.LexTable.table[i].idxTI].value.vstr.str;
				Gen_txt.CONST += " , 0\n";
			}
			else if (td.idTable.table[td.LexTable.table[i].idxTI].iddatatype == IT::BOOL) {
				if (td.idTable.table[td.LexTable.table[i].idxTI].value.T_F == 1) {
					Gen_txt.CONST += td.idTable.table[td.LexTable.table[i].idxTI].id;
					Gen_txt.CONST += "\t word  ";
					Gen_txt.CONST += "\t";
					Gen_txt.CONST += '1';
					Gen_txt.CONST += "\n";
				}
				else if (td.idTable.table[td.LexTable.table[i].idxTI].value.T_F == 0) {
					Gen_txt.CONST += td.idTable.table[td.LexTable.table[i].idxTI].id;
					Gen_txt.CONST += "\t word  ";
					Gen_txt.CONST += "\t";
					Gen_txt.CONST += '0';
					Gen_txt.CONST += "\n";

				}


			}
		}
	}
























	for (i = 0; i < td.LexTable.size; i++) {

		if (!flag_if &&flag_main&& td.LexTable.table[i].lexema == '}') {
			break;
		}
		if (td.LexTable.table[i].lexema == '?') {
			flag++;
			flag_if = true;
			flag_if_one++;
		}
		if (flag_if && td.LexTable.table[i].lexema == '(' && td.LexTable.table[i - 1].lexema == '?') {//флаги asm

			pos_if = i + 1;
			if (flag_main && (td.LexTable.table[i + 1].lexema == 'l' || td.LexTable.table[i + 1].lexema == 'T' || td.LexTable.table[i + 1].lexema == 'F')) {
				if (td.LexTable.table[i + 2].lexema == 's') {
					Gen_txt.MAIN += "MOV BX , ";
					Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i + 3].idxTI].id;
					Gen_txt.MAIN += "\n";
					Gen_txt.MAIN += "MOV AX , ";
					Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i + 1].idxTI].id;
					Gen_txt.MAIN += "\n";
					Gen_txt.MAIN += "cmp AX , BX\n";
					Gen_txt.MAIN += "jz f";
					Gen_txt.MAIN += std::to_string(i + 1);
					Gen_txt.MAIN += "\n";
					Gen_txt.MAIN += " jnz f0";
					Gen_txt.MAIN += std::to_string(i + 1);
					Gen_txt.MAIN += "\n";
					Gen_txt.MAIN += " f";
					Gen_txt.MAIN += std::to_string(i + 1);
					Gen_txt.MAIN += ":";
					Gen_txt.MAIN += "\n";

					i = i + 4;
				}
				else if (td.LexTable.table[i + 2].lexema == ')') {
					Gen_txt.MAIN += "MOV BX , 1\n";
					Gen_txt.MAIN += "MOV AX , ";
					Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i + 1].idxTI].id;
					//Gen_txt.MAIN += "\n";
					Gen_txt.MAIN += "\ncmp AX , BX\n";
					Gen_txt.MAIN += "jz f";
					Gen_txt.MAIN += std::to_string(i + 1);
					Gen_txt.MAIN += "\n";
					Gen_txt.MAIN += " jnz f0";
					Gen_txt.MAIN += std::to_string(i + 1);
					Gen_txt.MAIN += "\n";
					Gen_txt.MAIN += " f";
					Gen_txt.MAIN += std::to_string(i + 1);
					Gen_txt.MAIN += ":";
					Gen_txt.MAIN += "\n";
					i = i + 2;
				}
			}
			else if (!flag_main && (td.LexTable.table[i + 1].lexema == 'l' || td.LexTable.table[i + 1].lexema == 'T' || td.LexTable.table[i + 1].lexema == 'F')) {
				if (td.LexTable.table[i + 2].lexema == 's') {
					Gen_txt.CODE += "MOV BX , ";
					Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 3].idxTI].id;
					Gen_txt.CODE += "\n";
					Gen_txt.CODE += "MOV AX , ";
					Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 1].idxTI].id;
					Gen_txt.CODE += "\n";
					Gen_txt.CODE += "cmp AX , BX\n";
					Gen_txt.CODE += "jz f";
					Gen_txt.CODE += std::to_string(i + 1);
					Gen_txt.CODE += "\n";
					Gen_txt.CODE += "jnz f0";
					Gen_txt.CODE += std::to_string(i + 1);
					Gen_txt.CODE += "\n";
					Gen_txt.CODE += " f";
					Gen_txt.CODE += std::to_string(i + 1);
					Gen_txt.CODE += ":";
					Gen_txt.CODE += "\n";
					i = i + 4;
				}
				else if (td.LexTable.table[i + 2].lexema == ')') {
					Gen_txt.CODE += "MOV BX , 1\n";
					Gen_txt.CODE += "MOV AX , ";
					Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 1].idxTI].id;
					Gen_txt.CODE += "\n";
					Gen_txt.CODE += "cmp AX , BX\n";
					Gen_txt.CODE += "jz f";
					Gen_txt.CODE += std::to_string(i + 1);
					Gen_txt.CODE += "\n";
					Gen_txt.CODE += "jnz f0";
					Gen_txt.CODE += std::to_string(i + 1);
					Gen_txt.CODE += "\n";
					Gen_txt.CODE += " f";
					Gen_txt.CODE += std::to_string(i + 1);
					Gen_txt.CODE += ":";
					Gen_txt.CODE += "\n";
					i = i + 2;

				}
			}
			else if (td.LexTable.table[i + 1].lexema == 'i') {
				if (flag_main) {
					if (td.LexTable.table[i + 2].lexema == ')') {
						Gen_txt.MAIN += "MOV BX , 1\n";
						Gen_txt.MAIN += "MOV AX , ";
						Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i + 1].idxTI].id;
						Gen_txt.MAIN += "\n";
						Gen_txt.MAIN += "cmp AX , BX\n";
						Gen_txt.MAIN += "jz f";
						Gen_txt.MAIN += std::to_string(i + 1);
						Gen_txt.MAIN += "\n";
						Gen_txt.MAIN += "jnz f0";
						Gen_txt.MAIN += std::to_string(i + 1);
						Gen_txt.MAIN += "\n";
						Gen_txt.MAIN += " f";
						Gen_txt.MAIN += std::to_string(i + 1);
						Gen_txt.MAIN += ":";
						Gen_txt.MAIN += "\n";
						i = i + 2;
					}
					else if (td.LexTable.table[i + 2].lexema == 's') {
						Gen_txt.MAIN += "MOV BX , ";
						Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i + 3].idxTI].id;
						Gen_txt.MAIN += "\n";
						Gen_txt.MAIN += "MOV AX , ";
						Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i + 1].idxTI].id;
						Gen_txt.MAIN += "\n";
						Gen_txt.MAIN += "cmp AX , BX\n";
						Gen_txt.MAIN += "jz f";
						Gen_txt.MAIN += std::to_string(i + 1);
						Gen_txt.MAIN += "\n";
						Gen_txt.MAIN += "jnz f0";
						Gen_txt.MAIN += std::to_string(i + 1);
						Gen_txt.MAIN += "\n";
						Gen_txt.MAIN += " f";
						Gen_txt.MAIN += std::to_string(i + 1);
						Gen_txt.MAIN += ":";
						Gen_txt.MAIN += "\n";
						i = i + 4;
					}
				}
				else {
					if (td.LexTable.table[i + 2].lexema == ')') {
						Gen_txt.CODE += "MOV BX , 1\n";
						Gen_txt.CODE += "MOV AX , ";
						Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 1].idxTI].id;
						Gen_txt.CODE += "\n";
						Gen_txt.CODE += "cmp AX , BX\n";
						Gen_txt.CODE += "jz f";
						Gen_txt.CODE += std::to_string(i + 1);
						Gen_txt.CODE += "\n";
						Gen_txt.CODE += "jnz f0";
						Gen_txt.CODE += std::to_string(i + 1);
						Gen_txt.CODE += "\n";
						Gen_txt.CODE += " f";
						Gen_txt.CODE += std::to_string(i + 1);
						Gen_txt.CODE += ":";
						Gen_txt.CODE += "\n";
						i = i + 2;
					}
					else if (td.LexTable.table[i + 2].lexema == 's') {
						Gen_txt.CODE += "MOV BX , ";
						Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 4].idxTI].id;
						Gen_txt.CODE += "\n";
						Gen_txt.CODE += "MOV AX , ";
						Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 1].idxTI].id;
						Gen_txt.CODE += "\n";
						Gen_txt.CODE += "cmp AX , BX\n";
						Gen_txt.CODE += "jz f";
						Gen_txt.CODE += std::to_string(i + 1);
						Gen_txt.CODE += "\n";
						Gen_txt.CODE += "jnz f0";
						Gen_txt.CODE += std::to_string(i + 1);
						Gen_txt.CODE += "\n";
						Gen_txt.CODE += " f";
						Gen_txt.CODE += std::to_string(i + 1);
						Gen_txt.CODE += ":";
						Gen_txt.CODE += "\n";
						i = i + 4;
					}
				}
			}

		}
		else if (td.LexTable.table[i].lexema == 'm') {
			flag_main = true;
		}
		else if (td.LexTable.table[i].lexema == 'r') {//return
			if (td.idTable.table[td.LexTable.table[i + 1].idxTI].iddatatype == IT::STR) {
				if (td.idTable.table[td.LexTable.table[i + 1].idxTI].idtype == IT::L) {
					Gen_txt.CODE += ";-\n";
					Gen_txt.CODE += "MOV AX , ";
					Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 1].idxTI].id;
					Gen_txt.CODE += "\n";
					Gen_txt.CODE += "ret";
					Gen_txt.CODE += "\n";
					Gen_txt.CODE += "\n;-\n";
					i = i + 2;
				}
				else {

					Gen_txt.CODE += ";-\n";
					Gen_txt.CODE += "MOV EX , ";
					Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 1].idxTI].id;
					Gen_txt.CODE += "\n";
					Gen_txt.CODE += "ret";
					Gen_txt.CODE += "\n;-\n";
					i = i + 2;
				}
			}
			else {
				if (td.idTable.table[td.LexTable.table[i + 1].idxTI].idtype == IT::L) {
					Gen_txt.CODE += ";-\n";
					Gen_txt.CODE += "MOV AX , ";
					Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 1].idxTI].id;
					Gen_txt.CODE += "\n";
					Gen_txt.CODE += "ret";
					Gen_txt.CODE += "\n";
					Gen_txt.CODE += "\n;-\n";
					i = i + 2;
				}
				else {

					Gen_txt.CODE += ";-\n";
					Gen_txt.CODE += "MOV AX , ";
					Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 1].idxTI].id;
					Gen_txt.CODE += "\n";
					Gen_txt.CODE += "ret";
					Gen_txt.CODE += "\n;-\n";
					i = i + 2;
				}
			}
		}
		else if (td.LexTable.table[i].lexema == 'd') {//переменные
			if (td.idTable.table[td.LexTable.table[i + 2].idxTI].iddatatype == IT::INT) {
				Gen_txt.DATA += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
				Gen_txt.DATA += "\t sword  \t?\n";
				i = i + 3;
			}
			else if (td.idTable.table[td.LexTable.table[i + 2].idxTI].iddatatype == IT::STR) {
				Gen_txt.DATA += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
				Gen_txt.DATA += "\t DD  \t?\n";
				i = i + 3;
			}
			else if (td.idTable.table[td.LexTable.table[i + 2].idxTI].iddatatype == IT::BOOL) {
				Gen_txt.DATA += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
				Gen_txt.DATA += "\t word  \t?\n";
				i = i + 3;
			}
		}







		else if (flag_if  && td.LexTable.table[i].lexema == '}') {

		col_flag_if++;
		flag_if = false;
		if (flag_if_one == col_flag_if) {
			col_flag_if = 1;
			flag_if_one = 1;
			if (flag_main) {

				Gen_txt.MAIN += "f0";
				Gen_txt.MAIN += std::to_string(pos_if);
				Gen_txt.MAIN += ':';
				Gen_txt.MAIN += "\nfin:\n";
			}
			else {
				Gen_txt.CODE += "f0";
				Gen_txt.CODE += std::to_string(pos_if);
				Gen_txt.CODE += ':';
				Gen_txt.CODE += "\nfin:\n";
			}
			}
		else {
			if (flag_main) {

				Gen_txt.MAIN += "f0";
				Gen_txt.MAIN += std::to_string(pos_if);
				Gen_txt.MAIN += ':';

			}
			else {
				Gen_txt.CODE += "f0";
				Gen_txt.CODE += std::to_string(pos_if);
				Gen_txt.CODE += ':';

			}
		}
		
		}
		else if (!flag_if &&function_flag && td.LexTable.table[i].lexema == '}') {

			if (td.LexTable.table[i - 3].lexema == 'r') {
				Gen_txt.CODE += td.idTable.table[td.LexTable.table[pos_for_function].idxTI].id;
				Gen_txt.CODE += " ENDP\n\n";
				function_flag = false;
			}

		}




		else if (td.LexTable.table[i].lexema == 'i'&&td.LexTable.table[i + 1].lexema == '=') {//выражения 




			pos_expression = i;
			if (function_flag && !flag_main) {//выражения в функции
				if (td.idTable.table[td.LexTable.table[i].idxTI].iddatatype == IT::BOOL) {//i=l;
					Gen_txt.CODE += "mov AX , ";
					Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
					Gen_txt.CODE += " \n mov ";
					Gen_txt.CODE += td.idTable.table[td.LexTable.table[i].idxTI].id;
					Gen_txt.CODE += " , AX ";
					Gen_txt.CODE += "\n";
					i = i + 3;

				}
				else if (td.idTable.table[td.LexTable.table[i].idxTI].iddatatype == IT::STR) {//i=l;
					Gen_txt.CODE += "mov ";
					Gen_txt.CODE += td.idTable.table[td.LexTable.table[i].idxTI].id;
					Gen_txt.CODE += " , offset ";
					Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
					Gen_txt.CODE += "\n";
					i = i + 3;
				}
				else if (td.idTable.table[td.LexTable.table[i].idxTI].iddatatype == IT::INT) {//i=l;


					Gen_txt.CODE += "MOV BX , 0 \n";
					Gen_txt.CODE += "MOV AX , 0 \n";
					i = i + 2;
					for (; i < td.LexTable.size; i++) {
						if (td.LexTable.table[i].lexema == '~' || td.LexTable.table[i].lexema == ';') {
							Gen_txt.CODE += "MOV AX , 0\nPOP AX\n";
							Gen_txt.CODE += "MOV ";
							Gen_txt.CODE += td.idTable.table[td.LexTable.table[pos_expression].idxTI].id;
							Gen_txt.CODE += " , AX\n";
							Gen_txt.CODE += "\n";
							break;
						}
						else if (td.LexTable.table[i].lexema == 'l' || td.LexTable.table[i].lexema == 'i') {//i=l+...;						
							if (td.idTable.table[td.LexTable.table[i].idxTI].iddatatype == IT::STR) {
								//Gen_txt.CODE += " push bks \n";
								Gen_txt.CODE += "PUSH offset ";
								Gen_txt.CODE += td.idTable.table[td.LexTable.table[i].idxTI].id;
								Gen_txt.CODE += " \n";

							}
							else {
							Gen_txt.CODE += " push bks \n";
							Gen_txt.CODE += "PUSH ";
							Gen_txt.CODE += td.idTable.table[td.LexTable.table[i].idxTI].id;
							Gen_txt.CODE += " \n";
							}
							

						}
						else if (td.LexTable.table[i].lexema == 'v' || td.LexTable.table[i].lexema == '@') {
							if (td.LexTable.table[i].value == '+') {
								Gen_txt.CODE += "POP BX\n";
								Gen_txt.CODE += "POP AX\n";
								Gen_txt.CODE += "POP AX\n";
								Gen_txt.CODE += "ADD AX , BX \n";
							//	Gen_txt.CODE += " push bks \n";
								Gen_txt.CODE += "PUSH AX \n ";

							}
							else if (td.LexTable.table[i].value == '-') {
								Gen_txt.CODE += "POP BX\n";
								Gen_txt.CODE += "POP AX\n";
								Gen_txt.CODE += "POP AX\n";
								Gen_txt.CODE += "SUB AX , BX \n";
							//	Gen_txt.CODE += " push bks \n";
								Gen_txt.CODE += "PUSH AX \n";

							}
							else if (td.LexTable.table[i].value == '*') {
								Gen_txt.CODE += "POP BX\n";
								Gen_txt.CODE += "POP AX\n";
								Gen_txt.CODE += "POP AX\n";
								Gen_txt.CODE += "MUL BX \n";
								//Gen_txt.CODE += " push bks \n";
								Gen_txt.CODE += "PUSH AX \n";

							}
							else if (td.LexTable.table[i].value == '/') {

								Gen_txt.CODE += "POP BX\n";
								Gen_txt.CODE += "POP AX\n";
								Gen_txt.CODE += "POP AX\n";
								Gen_txt.CODE += "CDQ \n";
								Gen_txt.CODE += "DIV BX \n";
								//Gen_txt.MAIN += " push bks \n";
								Gen_txt.CODE += "PUSH AX \n";

							}
							else if (td.LexTable.table[i].value == '%') {
								Gen_txt.CODE += "POP BX\n";
								Gen_txt.CODE += "POP AX\n";
								Gen_txt.CODE += "POP AX\n";
								Gen_txt.CODE += "CDQ \n";
								Gen_txt.CODE += "IDIV BX \n";
								Gen_txt.CODE += "MOV AX,DX \n";
								//Gen_txt.CODE += " push bks \n";
								Gen_txt.CODE += "PUSH AX  \n";

							}
							else if (td.LexTable.table[i].lexema == '@') {
								Gen_txt.CODE += "call ";
								Gen_txt.CODE += td.idTable.table[td.LexTable.table[i].idxTI].id;//Gen_txt.MAIN += " push bks \n";
								Gen_txt.CODE += "\n push AX \n ";




							}

						}
					}
				}
			}
			else if (flag_main) {
				if (td.idTable.table[td.LexTable.table[i].idxTI].iddatatype == IT::BOOL) {//i=l;
					Gen_txt.MAIN += "mov AX , ";
					Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
					Gen_txt.MAIN += " \n mov ";
					Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i].idxTI].id;
					Gen_txt.MAIN += " , AX ";
					Gen_txt.MAIN += "\n";
					i = i + 3;

				}
				else if (td.idTable.table[td.LexTable.table[i].idxTI].iddatatype == IT::STR) {//i=l;
					Gen_txt.MAIN += "mov ";
					Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i].idxTI].id;
					Gen_txt.MAIN += " , offset ";
					Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
					Gen_txt.MAIN += "\n";
					i = i + 3;
				}
				else if (td.idTable.table[td.LexTable.table[i].idxTI].iddatatype == IT::INT) {//i=l;


					Gen_txt.MAIN += "MOV BX , 0 \n";
					Gen_txt.MAIN += "MOV AX , 0 \n";
					i = i + 2;
					for (; i < td.LexTable.size; i++) {
						if (td.LexTable.table[i].lexema == '~' || td.LexTable.table[i].lexema == ';') {
							Gen_txt.MAIN += "MOV AX , 0\nPOP AX\n";
							Gen_txt.MAIN += "MOV ";
							Gen_txt.MAIN += td.idTable.table[td.LexTable.table[pos_expression].idxTI].id;
							Gen_txt.MAIN += " , AX\n";
							Gen_txt.MAIN += "\n";
							break;
						}
						if (td.LexTable.table[i].lexema == '~' || td.LexTable.table[i].lexema == ';') {
							Gen_txt.MAIN += "MOV AX , 0\nPOP AX\n";
							Gen_txt.MAIN += "MOV ";
							Gen_txt.MAIN += td.idTable.table[td.LexTable.table[pos_expression].idxTI].id;
							Gen_txt.MAIN += " , AX\n";
							Gen_txt.MAIN += "\n";
							break;
						}
						else if (td.LexTable.table[i].lexema == 'l' || td.LexTable.table[i].lexema == 'i') {//i=l+...;						
							if (td.idTable.table[td.LexTable.table[i].idxTI].iddatatype == IT::STR) {
							//	Gen_txt.MAIN += " push bks \n";	
								Gen_txt.MAIN += "PUSH offset ";
								Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i].idxTI].id;
								Gen_txt.MAIN += " \n";
								
							}
							else {
							Gen_txt.MAIN += " push bks \n";
							Gen_txt.MAIN += "PUSH ";
							Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i].idxTI].id;
							Gen_txt.MAIN += " \n";
							}
							
							
						}
						else if (td.LexTable.table[i].lexema == 'v' || td.LexTable.table[i].lexema == '@') {
							if (td.LexTable.table[i].value == '+') {
								Gen_txt.MAIN += "POP BX\n";
								Gen_txt.MAIN += "POP AX\n";
								Gen_txt.MAIN += "POP AX\n";
								Gen_txt.MAIN += "ADD AX , BX \n";
							//	Gen_txt.MAIN += " push bks \n";
								Gen_txt.MAIN += "PUSH AX \n ";
								
							}
							else if (td.LexTable.table[i].value == '-') {
								Gen_txt.MAIN += "POP BX\n";
								Gen_txt.MAIN += "POP AX\n";
								Gen_txt.MAIN += "POP AX\n";
								Gen_txt.MAIN += "SUB AX , BX \n";
							//	Gen_txt.MAIN += " push bks \n";
								Gen_txt.MAIN += "PUSH AX \n";
								
							}
							else if (td.LexTable.table[i].value == '*') {
								Gen_txt.MAIN += "POP BX\n";
								Gen_txt.MAIN += "POP AX\n";
								Gen_txt.MAIN += "POP AX\n";
								Gen_txt.MAIN += "MUL BX \n";
							//	Gen_txt.MAIN += " push bks \n";
								Gen_txt.MAIN += "PUSH AX \n";
								
							}
							else if (td.LexTable.table[i].value == '/') {
								
								Gen_txt.MAIN += "POP BX\n";
								Gen_txt.MAIN += "POP AX\n";
								Gen_txt.MAIN += "POP AX\n";
								Gen_txt.MAIN += "CDQ \n";
								Gen_txt.MAIN += "DIV BX \n";
								//Gen_txt.MAIN += " push bks \n";
								Gen_txt.MAIN += "PUSH AX \n";
								
							}
							else if (td.LexTable.table[i].value == '%') {
								Gen_txt.MAIN += "POP BX\n";
								Gen_txt.MAIN += "POP AX\n";
								Gen_txt.MAIN += "POP AX\n";
								Gen_txt.MAIN += "CDQ \n";
								Gen_txt.MAIN += "IDIV BX \n";
								Gen_txt.MAIN += "MOV AX,DX \n";
							//	Gen_txt.MAIN += " push bks \n";
								Gen_txt.MAIN += "PUSH AX  \n";
								
							}
							else if (td.LexTable.table[i].lexema == '@') {
								Gen_txt.MAIN += "call ";
								Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i].idxTI].id;//Gen_txt.MAIN += " push bks \n";
								Gen_txt.MAIN += "\n push AX \n ";
								



							}

						}
					}
				}
			}
		}



		else if (td.LexTable.table[i].lexema == 'p') {//++
			if (!flag_main) {
				if (td.idTable.table[td.LexTable.table[i + 2].idxTI].iddatatype == IT::BOOL) {
					Gen_txt.CODE += "\n;print \n";
					Gen_txt.CODE += "push ";
					Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
					Gen_txt.CODE += "\n  ";
					Gen_txt.CODE += " call ";
					Gen_txt.CODE += "call ConsoleBool \n";
					i = i + 3;
				}
				else if (td.idTable.table[td.LexTable.table[i + 2].idxTI].iddatatype == IT::INT) {
					Gen_txt.CODE += "\n;print \n";
					Gen_txt.CODE += "push ";
					Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
					Gen_txt.CODE += "\n ";
					Gen_txt.CODE += " call ";
					Gen_txt.CODE += " ConsoleInt \n";
					i = i + 3;
				}
				else if (td.idTable.table[td.LexTable.table[i + 2].idxTI].iddatatype == IT::STR) {

					if (td.LexTable.table[i + 2].lexema == 'l') {
						Gen_txt.CODE += "\n;print \n";
						Gen_txt.CODE += "push offset ";
						Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
						Gen_txt.CODE += "\n  ";
						Gen_txt.CODE += " call ";
						Gen_txt.CODE+= " ConsoleStr \n";
						i = i + 3;
					}
					else if (td.LexTable.table[i + 2].lexema == 'i') {
						Gen_txt.CODE += "\n;print \n";
						Gen_txt.CODE += "push  ";
						Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
						Gen_txt.CODE += "\n  ";
						Gen_txt.CODE += "call ";
						Gen_txt.CODE += " ConsoleStr \n";
						i = i + 3;
					}
				}

			}
			else {
				if (td.idTable.table[td.LexTable.table[i + 2].idxTI].iddatatype == IT::BOOL) {
					Gen_txt.MAIN += "\n;print \n";
					Gen_txt.MAIN += "push ";
					Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
					Gen_txt.MAIN += "\n ";
					Gen_txt.MAIN += " call ";
					Gen_txt.MAIN += " ConsoleBool \n";
					i = i + 3;
				}
				else if (td.idTable.table[td.LexTable.table[i + 2].idxTI].iddatatype == IT::INT) {
					Gen_txt.MAIN += "\n;print \n";
					Gen_txt.MAIN += "push ";
					Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
					Gen_txt.MAIN += "\n ";
					Gen_txt.MAIN += " call ";
					Gen_txt.MAIN += " ConsoleInt \n";
					i = i + 3;
				}
				else if (td.idTable.table[td.LexTable.table[i + 2].idxTI].iddatatype == IT::STR) {
					if (td.LexTable.table[i + 2].lexema == 'l') {
						Gen_txt.MAIN += "\n;print \n";
						Gen_txt.MAIN += "push offset ";
						Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
						Gen_txt.MAIN += "\n  ";
						Gen_txt.MAIN += " call ";
						Gen_txt.MAIN += " ConsoleStr \n";
						i = i + 3;
					}
					else if (td.LexTable.table[i + 2].lexema == 'i') {
						Gen_txt.MAIN += "\n;print \n";
						Gen_txt.MAIN += "push  ";
						Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
						Gen_txt.MAIN += "\n  ";
						Gen_txt.MAIN += " call ";
						Gen_txt.MAIN += " ConsoleStr \n";
						i = i + 3;
					}
				}
			}

		}





		else if (td.LexTable.table[i].lexema == 'f') {//функции
			pos_for_function = i + 1;
			function_flag = true;
			Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 1].idxTI].id;
			Gen_txt.CODE += " PROC ";
			par_flag = false;
			for (; i < td.LexTable.size; i++) {
				if (td.LexTable.table[i].lexema == '(') {
					par_flag = true;
				}
				else if (td.LexTable.table[i].lexema == ')') {
					par_flag = false;
				}
				else if (td.LexTable.table[i].lexema == 'i'&& par_flag) {
					Gen_txt.CODE += td.idTable.table[td.LexTable.table[i].idxTI].id;
					if (td.idTable.table[td.LexTable.table[i].idxTI].iddatatype == IT::INT) {

						Gen_txt.CODE += ": sword";
						if (td.LexTable.table[i + 1].lexema == ')') {
							par_flag = false;
							break;
						}
						else {
							Gen_txt.CODE += " , ";
						}
					}
					else if (td.idTable.table[td.LexTable.table[i].idxTI].iddatatype == IT::STR) {
						//Gen_txt.CODE += td.idTable.table[td.LexTable.table[i ].idxTI].id;
						Gen_txt.CODE += ": dword";
						if (td.LexTable.table[i + 1].lexema == ')') {
							par_flag = false;
							break;
						}
						else {
							Gen_txt.CODE += " , ";
						}
					}
					else if (td.idTable.table[td.LexTable.table[i].idxTI].iddatatype == IT::BOOL) {
						//Gen_txt.CODE += td.idTable.table[td.LexTable.table[i].idxTI].id;
						Gen_txt.CODE += ": word";
						if (td.LexTable.table[i + 1].lexema == ')') {
							par_flag = false;
							break;
						}
						else {
							Gen_txt.CODE += " , ";
						}
					}
				}
			}
			Gen_txt.CODE += "\n\n";

		}
	}




	out.open(file);
	out << ".586P\n\n\n";
	out << ".MODEL FLAT,STDCALL\n\n";
	out << "includelib kernel32.lib\n";
	out << "includelib libucrt.lib\n\n";
	out << "EXTERN strlen1 :proc\n";
	out << "EXTERN ConsoleInt :proc\n";
	out << "EXTERN ConsoleStr :proc\n";
	out << "EXTERN ConsoleBool :proc\n";
	out << "EXTERN stringtoint :proc\n\n";
	out << "ExitProcess PROTO : DWORD\n";
	out << "MessageBoxA PROTO : DWORD, : DWORD, : DWORD, : DWORD\n\n";
	out << ".STACK 4096\n\n";
	out << Gen_txt.CONST;
	out << "\n";
	out << Gen_txt.DATA;
	out << "\n bks word 0\n";
	out << "\n consolehandle dd 0h \n";
	out << "\n";
	out << Gen_txt.CODE;
	out << Gen_txt.MAIN;
	out << "\npush 0\ncall ExitProcess\nmain ENDP\nend main\n";
	out.close();
	std::cout << "end" << endl;

}
