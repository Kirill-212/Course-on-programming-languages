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
	GEN::Gen_text Gen_txt;
	bool par_flag = true;
	bool function_flag = false;
	bool flag_if = false;
	int pos_if=0;
	int pos_for_function = 0;
	int pos_expression = 0;
	bool flag_main = false;
	char* arr = new char[256];
	//bool flag_first_op = true;
	std::cout << "start" << endl;
	ofstream out;
	for ( ; i < td.LexTable.size; i++) {
		if (td.LexTable.table[i].lexema == 'l' || td.LexTable.table[i].lexema == 'T' || td.LexTable.table[i].lexema == 'F') {//литералы

			if (td.idTable.table[td.LexTable.table[i].idxTI].iddatatype == IT::INT) {
				Gen_txt.CONST += td.idTable.table[td.LexTable.table[i].idxTI].id;
				Gen_txt.CONST += "\t sdword  ";
				Gen_txt.CONST += "\t";
				Gen_txt.CONST += std::to_string(td.idTable.table[td.LexTable.table[i].idxTI].value.vint);
				Gen_txt.CONST += "\n";
			}
			else if (td.idTable.table[td.LexTable.table[i].idxTI].iddatatype == IT::STR) {
				
				Gen_txt.CONST += td.idTable.table[td.LexTable.table[i].idxTI].id;
				Gen_txt.CONST += "\t DQ  ";
				Gen_txt.CONST += "\t";
				Gen_txt.CONST += td.idTable.table[td.LexTable.table[i].idxTI].value.vstr.str;
				Gen_txt.CONST += "\n";
			}
			else if (td.idTable.table[td.LexTable.table[i].idxTI].iddatatype == IT::BOOL) {
				if (td.idTable.table[td.LexTable.table[i].idxTI].value.T_F==1) {
					Gen_txt.CONST += td.idTable.table[td.LexTable.table[i].idxTI].id;
					Gen_txt.CONST += "\t dword  ";
					Gen_txt.CONST += "\t";
					Gen_txt.CONST += '1';
					Gen_txt.CONST += "\n";
				}
				else if (td.idTable.table[td.LexTable.table[i].idxTI].value.T_F == 0) {
					Gen_txt.CONST += td.idTable.table[td.LexTable.table[i].idxTI].id;
					Gen_txt.CONST += "\t dword  ";
					Gen_txt.CONST += "\t";
					Gen_txt.CONST += '0';
					Gen_txt.CONST += "\n";

				}


			}
		}
	}
		for (i=0; i < td.LexTable.size; i++) {
				if (!flag_if &&flag_main&& td.LexTable.table[i].lexema == '}') {
					break;
				}
				if (td.LexTable.table[i].lexema == '?') {
				flag_if = true;
				}
				
			 if (flag_if && td.LexTable.table[i].lexema == '(' && td.LexTable.table[i - 1].lexema == '?') {//флаги asm
				
				pos_if = i + 1;
				if (flag_main && (td.LexTable.table[i + 1].lexema == 'l' || td.LexTable.table[i + 1].lexema == 'T' || td.LexTable.table[i + 1].lexema == 'F')) {
					if (td.LexTable.table[i + 2].lexema == 's') {
						Gen_txt.MAIN += "MOV EBX , ";
						Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i + 3].idxTI].id;
						Gen_txt.MAIN += "\n";
						Gen_txt.MAIN += "MOV EAX , ";
						Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i + 1].idxTI].id;
						Gen_txt.MAIN += "\n";
						Gen_txt.MAIN += "cmp EAX , EBX\n";
						Gen_txt.MAIN += "jz f";
						Gen_txt.MAIN += std::to_string(i+1);
						//Gen_txt.MAIN += "\n";
						Gen_txt.MAIN += "\njnz f0";
						Gen_txt.MAIN += std::to_string(i + 1);
						//Gen_txt.MAIN += "\n";
						Gen_txt.MAIN += "\nf";
						Gen_txt.MAIN += std::to_string(i + 1);
						Gen_txt.MAIN += ":\n";

						i = i + 4;
					}
					else if (td.LexTable.table[i + 2].lexema == ')') {
						Gen_txt.MAIN += "MOV EBX , 1\n";
						Gen_txt.MAIN += "MOV EAX , ";
						Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i + 1].idxTI].id;
						//Gen_txt.MAIN += "\n";
						Gen_txt.MAIN += "\ncmp EAX , EBX\n";
						Gen_txt.MAIN += "jz f";
						Gen_txt.MAIN += std::to_string(i + 1);
						Gen_txt.MAIN += "\njnz f0";
						Gen_txt.MAIN += std::to_string(i + 1);
						Gen_txt.MAIN += "\nf";
						Gen_txt.MAIN += std::to_string(i + 1);
						Gen_txt.MAIN += ":\n";
						i = i + 2;
					}
				}
				else if (!flag_main && (td.LexTable.table[i + 1].lexema == 'l' || td.LexTable.table[i + 1].lexema == 'T' || td.LexTable.table[i + 1].lexema == 'F')) {
					if (td.LexTable.table[i + 2].lexema == 's') {
						Gen_txt.CODE += "MOV EBX , ";
						Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 3].idxTI].id;
						Gen_txt.CODE += "\n";
						Gen_txt.CODE += "MOV EAX , ";
						Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 1].idxTI].id;
						Gen_txt.CODE += "\n";
						Gen_txt.CODE += "cmp EAX , EBX\n";
						Gen_txt.CODE += "jz f";
						Gen_txt.CODE += std::to_string(i + 1);
						//Gen_txt.CODE += "\n";
						Gen_txt.CODE += "\njnz f0";
						Gen_txt.CODE += std::to_string(i + 1);
						//Gen_txt.CODE += "\n";
						Gen_txt.CODE += "\nf";
						Gen_txt.CODE += std::to_string(i + 1);
						Gen_txt.CODE += ":\n";
						i = i + 4;
					}
					else if (td.LexTable.table[i + 2].lexema == ')') {
						Gen_txt.CODE += "MOV EBX , 1\n";
						Gen_txt.CODE += "MOV EAX , ";
						Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 1].idxTI].id;
						Gen_txt.CODE += "\n";
						Gen_txt.CODE += "cmp EAX , EBX\n";
						Gen_txt.CODE += "jz f";
						Gen_txt.CODE += std::to_string(i + 1);
						//Gen_txt.CODE += "\n";
						Gen_txt.CODE += "\njnz f0";
						Gen_txt.CODE += std::to_string(i + 1);
						//Gen_txt.CODE += "\n";
						Gen_txt.CODE += "\nf";
						Gen_txt.CODE += std::to_string(i + 1);
						Gen_txt.CODE += ":\n";
						i = i + 2;

					}
				}
				else if (td.LexTable.table[i + 1].lexema == 'i') {
					if (flag_main) {
						if (td.LexTable.table[i + 2].lexema == ')') {
							Gen_txt.MAIN += "MOV EBX , 1\n";
							Gen_txt.MAIN += "MOV EAX , ";
							Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i + 1].idxTI].id;
							Gen_txt.MAIN += "\n";
							Gen_txt.MAIN += "cmp EAX , EBX\n";
							Gen_txt.MAIN += "jz f";
							Gen_txt.MAIN += std::to_string(i + 1);
							//.MAIN += "\n";
							Gen_txt.MAIN += "\njnz f0";
							Gen_txt.MAIN += std::to_string(i + 1);
							Gen_txt.MAIN += "\n";
							i = i + 2;
						}
						else if (td.LexTable.table[i + 2].lexema == 's') {
							Gen_txt.MAIN += "MOV EBX , ";
							Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i + 3].idxTI].id;
							Gen_txt.MAIN += "\n";
							Gen_txt.MAIN += "MOV EAX , ";
							Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i + 1].idxTI].id;
							Gen_txt.MAIN += "\n";
							Gen_txt.MAIN += "cmp EAX , EBX\n";
							Gen_txt.MAIN += "jz f";
							Gen_txt.MAIN += std::to_string(i + 1);
							//Gen_txt.MAIN += "\n";
							Gen_txt.MAIN += "/njnz f0";
							Gen_txt.MAIN += std::to_string(i + 1);
							Gen_txt.MAIN += "\n";
							i = i + 4;
						}
					}
					else {
						if (td.LexTable.table[i + 2].lexema == ')') {
							Gen_txt.CODE += "MOV EBX , 1\n";
							Gen_txt.CODE += "MOV EAX , ";
							Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 1].idxTI].id;
							Gen_txt.CODE += "\n";
							Gen_txt.CODE += "cmp EAX , EBX\n";
							Gen_txt.CODE += "jz f";
							Gen_txt.CODE += std::to_string(i + 1);
							//Gen_txt.CODE += "\n";
							Gen_txt.CODE += "\njnz f0";
							Gen_txt.CODE += std::to_string(i + 1);
							Gen_txt.CODE += "\n";
							i = i + 2;
						}
						else if (td.LexTable.table[i + 2].lexema == 's') {
							Gen_txt.CODE += "MOV EBX , ";
							Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 4].idxTI].id;
							Gen_txt.CODE += "\n";
							Gen_txt.CODE += "MOV EAX , ";
							Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 1].idxTI].id;
							Gen_txt.CODE += "\n";
							Gen_txt.CODE += "cmp EAX , EBX\n";
							Gen_txt.CODE += "jz f";
							Gen_txt.CODE += std::to_string(i + 1);
							//Gen_txt.CODE += "\n";
							Gen_txt.CODE += "\njnz f0";
							Gen_txt.CODE += std::to_string(i + 1);
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
				if (td.idTable.table[td.LexTable.table[i + 1].idxTI].idtype == IT::L) {
					Gen_txt.CODE += ";-\n";
					Gen_txt.CODE += "MOV EAX , ";
					Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 1].idxTI].id;
					Gen_txt.CODE += "\nret";
					Gen_txt.CODE += "\n;-\n";
					i = i + 2;
				}
				else {

					Gen_txt.CODE += ";-\n";
					Gen_txt.CODE += "MOV EAX , ";
					Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 1].idxTI].id;
					Gen_txt.CODE += "ret";
					Gen_txt.CODE += "\n;-\n";
					i = i + 2;
				}

			}
			else if (td.LexTable.table[i].lexema == 'd') {//переменные
				if (td.idTable.table[td.LexTable.table[i + 2].idxTI].iddatatype == IT::INT) {
					Gen_txt.DATA += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
					Gen_txt.DATA += "\t sdword  \t?\n";
					i = i + 3;
				}
				else if (td.idTable.table[td.LexTable.table[i + 2].idxTI].iddatatype == IT::STR) {
					Gen_txt.DATA += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
					Gen_txt.DATA += "\t DQ  \t?\n";
					i = i + 3;
				}
				else if (td.idTable.table[td.LexTable.table[i + 2].idxTI].iddatatype == IT::BOOL) {
					Gen_txt.DATA += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
					Gen_txt.DATA += "\t dword  \t?\n";
					i = i + 3;
				}
			}
			 


			else if (flag_if &&function_flag && td.LexTable.table[i].lexema == '}') {
				flag_if = false;
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
						Gen_txt.CODE += "mov ";
						Gen_txt.CODE += td.idTable.table[td.LexTable.table[i].idxTI].id;
						Gen_txt.CODE += " , ";
						Gen_txt.CODE += td.idTable.table[td.LexTable.table[i+2].idxTI].id;
						Gen_txt.CODE += "\n";
						i = i + 3;

					}
					else if (td.idTable.table[td.LexTable.table[i].idxTI].iddatatype == IT::STR) {//i=l;
						Gen_txt.CODE += "mov ";
						Gen_txt.CODE += td.idTable.table[td.LexTable.table[i].idxTI].id;
						Gen_txt.CODE += " , ";
						Gen_txt.CODE += td.idTable.table[td.LexTable.table[i+2].idxTI].id;
						Gen_txt.CODE += "\n";
						i = i + 3;
					}
					else if (td.idTable.table[td.LexTable.table[i].idxTI].iddatatype == IT::INT) {//i=l;


						Gen_txt.CODE += "MOV EBX , 0 \n";
						Gen_txt.CODE += "MOV EAX , 0 \n";
						i = i + 2;
						for (; i < td.LexTable.size; i++) {

							if (td.LexTable.table[i].lexema == '~' || td.LexTable.table[i].lexema == ';') {
								Gen_txt.CODE += "MOV EAX , 0\nPOP EAX\n";
								Gen_txt.CODE += "MOV ";
								Gen_txt.CODE += td.idTable.table[td.LexTable.table[pos_expression].idxTI].id;
								Gen_txt.CODE += " , EAX\n";
								Gen_txt.CODE += "\n";
								break;
							}
							else if (td.LexTable.table[i].lexema == 'l' || td.LexTable.table[i].lexema == 'i') {//i=l+...;							
								Gen_txt.CODE += "PUSH ";
								Gen_txt.CODE += td.idTable.table[td.LexTable.table[i].idxTI].id;
								Gen_txt.CODE += "\n";
							}
							else if (td.LexTable.table[i].lexema == 'v'|| td.LexTable.table[i].lexema == '@') {
								if (td.LexTable.table[i].value == '+') {
									Gen_txt.CODE += "POP EBX\n";
									Gen_txt.CODE += "POP EAX\n";
									Gen_txt.CODE += "ADD EAX , EBX \n";
									Gen_txt.CODE += "PUSH EAX \n";
								}
								else if (td.LexTable.table[i].value == '-') {
									Gen_txt.CODE += "POP EBX\n";
									Gen_txt.CODE += "POP EAX\n";
									Gen_txt.CODE += "SUB EAX , EBX \n";
									Gen_txt.CODE += "PUSH EAX \n";
								}
								else if (td.LexTable.table[i].value == '*') {
									Gen_txt.CODE += "POP EBX\n";
									Gen_txt.CODE += "POP EAX\n";
									Gen_txt.CODE += "MUL EBX \n";
									Gen_txt.CODE += "PUSH EAX \n";
								}
								else if (td.LexTable.table[i].value == '/') {
									Gen_txt.CODE += "POP EBX\n";
									Gen_txt.CODE += "POP EAX\n";
									Gen_txt.CODE += "CDQ \n";
									Gen_txt.CODE += "IDIV EBX \n";
									Gen_txt.CODE += "PUSH EAX \n";
								}
								else if (td.LexTable.table[i].value == '%') {
									Gen_txt.CODE += "POP EBX\n";
									Gen_txt.CODE += "POP EAX\n";
									Gen_txt.CODE += "CDQ \n";
									Gen_txt.CODE += "IDIV EBX \n";
									Gen_txt.CODE += "MOV EAX,DX \n";
									Gen_txt.CODE += "PUSH EAX \n";
								}
								else if (td.LexTable.table[i].lexema == '@') {
									Gen_txt.CODE += "call ";
									Gen_txt.CODE += td.idTable.table[td.LexTable.table[i].idxTI].id;
									Gen_txt.CODE += "\n push EAX\n";



								}

							}
						}
					}
				}
				else if (flag_main) {
					if (td.idTable.table[td.LexTable.table[i].idxTI].iddatatype == IT::BOOL) {//i=l;
						Gen_txt.MAIN += "mov ";
						Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i].idxTI].id;
						Gen_txt.MAIN += " , ";
						Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
						Gen_txt.MAIN += "\n";
						i = i + 3;

					}
					else if (td.idTable.table[td.LexTable.table[i].idxTI].iddatatype == IT::STR) {//i=l;
						Gen_txt.MAIN += "mov ";
						Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i].idxTI].id;
						Gen_txt.MAIN += " , ";
						Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
						Gen_txt.MAIN += "\n";
						i = i + 3;
					}
					else if (td.idTable.table[td.LexTable.table[i].idxTI].iddatatype == IT::INT) {//i=l;


						Gen_txt.MAIN += "MOV EBX , 0 \n";
						Gen_txt.MAIN += "MOV EAX , 0 \n";
						i = i + 2;
						for (; i < td.LexTable.size; i++) {
							if (td.LexTable.table[i].lexema == '~' || td.LexTable.table[i].lexema == ';') {
								Gen_txt.MAIN += "MOV EAX , 0\nPOP EAX\n";
								Gen_txt.MAIN += "MOV ";
								Gen_txt.MAIN += td.idTable.table[td.LexTable.table[pos_expression].idxTI].id;
								Gen_txt.MAIN += " , EAX\n";
								Gen_txt.MAIN += "\n";
								break;
							}
							if (td.LexTable.table[i].lexema == '~' || td.LexTable.table[i].lexema == ';') {
								Gen_txt.MAIN += "MOV EAX , 0\nPOP EAX\n";
								Gen_txt.MAIN += "MOV ";
								Gen_txt.MAIN += td.idTable.table[td.LexTable.table[pos_expression].idxTI].id;
								Gen_txt.MAIN += " , EAX\n";
								Gen_txt.MAIN += "\n";
								break;
							}
							else if (td.LexTable.table[i].lexema == 'l' || td.LexTable.table[i].lexema == 'i') {//i=l+...;							
								Gen_txt.MAIN += "PUSH ";
								Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i].idxTI].id;
								Gen_txt.MAIN += "\n";
							}
							else if (td.LexTable.table[i].lexema == 'v' || td.LexTable.table[i].lexema == '@') {
								if (td.LexTable.table[i].value == '+') {
									Gen_txt.MAIN += "POP EBX\n";
									Gen_txt.MAIN += "POP EAX\n";
									Gen_txt.MAIN += "ADD EAX , EBX \n";
									Gen_txt.MAIN += "PUSH EAX \n";
								}
								else if (td.LexTable.table[i].value == '-') {
									Gen_txt.MAIN += "POP EBX\n";
									Gen_txt.MAIN += "POP EAX\n";
									Gen_txt.MAIN += "SUB EAX , EBX \n";
									Gen_txt.MAIN += "PUSH EAX \n";
								}
								else if (td.LexTable.table[i].value == '*') {
									Gen_txt.MAIN += "POP EBX\n";
									Gen_txt.MAIN += "POP EAX\n";
									Gen_txt.MAIN += "MUL EBX \n";
									Gen_txt.MAIN += "PUSH EAX \n";
								}
								else if (td.LexTable.table[i].value == '/') {
									Gen_txt.MAIN += "POP EBX\n";
									Gen_txt.MAIN += "POP EAX\n";
									Gen_txt.MAIN += "CDQ \n";
									Gen_txt.MAIN += "IDIV EBX \n";
									Gen_txt.MAIN += "PUSH EAX \n";
								}
								else if (td.LexTable.table[i].value == '%') {
									Gen_txt.MAIN += "POP EBX\n";
									Gen_txt.MAIN += "POP EAX\n";
									Gen_txt.MAIN += "CDQ \n";
									Gen_txt.MAIN += "IDIV EBX \n";
									Gen_txt.MAIN += "MOV EAX,DX \n";
									Gen_txt.MAIN += "PUSH EAX \n";
								}
								else if (td.LexTable.table[i].lexema == '@') {
									Gen_txt.MAIN += "call ";
									Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i].idxTI].id;
									Gen_txt.MAIN += "\n push EAX\n";



								}

							}
						}
					}
				}
			}
			else if (td.LexTable.table[i].lexema == 'p') {//++
				if (!flag_main) {
					if (td.LexTable.table[i + 2].lexema == 'l' || td.LexTable.table[i + 2].lexema == 'T' || td.LexTable.table[i + 2].lexema == 'F') {
						Gen_txt.CODE += "\n;print";
						Gen_txt.CODE += "push 0\npush 0\n push sizeof ";
						Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
						Gen_txt.CODE += "\npush sizeof ";
						Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
						Gen_txt.CODE += "\npush consolehandle\ncall WriteConsoleA\npush -11\ncall GetStdHandle\nmov consolehandle,eax\n";
						i = i + 3;
					}
					else if (td.LexTable.table[i + 2].lexema == 'i') {
						Gen_txt.CODE += "\n;print";
						Gen_txt.CODE += "push 0\npush 0\n push sizeof ";
						Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
						Gen_txt.CODE += "\npush sizeof ";
						Gen_txt.CODE += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
						Gen_txt.CODE += "\npush consolehandle\ncall WriteConsoleA\npush -11\ncall GetStdHandle\nmov consolehandle,eax\n";
						i = i + 3;
					}
				}
				else {
					if (td.LexTable.table[i + 2].lexema == 'l' || td.LexTable.table[i + 2].lexema == 'T' || td.LexTable.table[i + 2].lexema == 'F') {
						Gen_txt.MAIN += "\n;print";
						Gen_txt.MAIN += "push 0\npush 0\n push sizeof ";
						Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
						Gen_txt.MAIN += "\npush sizeof ";
						Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
						Gen_txt.MAIN += "\npush consolehandle\ncall WriteConsoleA\npush -11\ncall GetStdHandle\nmov consolehandle,eax\n";
						i = i + 3;
					}
					else if (td.LexTable.table[i + 2].lexema == 'i') {
						Gen_txt.MAIN += "\n;print";
						Gen_txt.MAIN += "push 0\npush 0\n push sizeof ";
						Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
						Gen_txt.MAIN += "\npush sizeof ";
						Gen_txt.MAIN += td.idTable.table[td.LexTable.table[i + 2].idxTI].id;
						Gen_txt.MAIN += "\npush consolehandle\ncall WriteConsoleA\npush -11\ncall GetStdHandle\nmov consolehandle,eax\n";
						i = i + 3;
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

							Gen_txt.CODE += ": sdword";
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
							Gen_txt.CODE += ": DQ";
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
							Gen_txt.CODE += ": dword";
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
	out << "EXTERN strlen :proc\n";
	out << "EXTERN stringtoint :proc\n\n";
	out << "ExitProcess PROTO : DWORD\n";
	out << "MessageBoxA PROTO : DWORD, : DWORD, : DWORD, : DWORD\n\n";
	out << "SetConsoleTitleA PROTO :DWORD\n";
	out << "GetStdHandle     PROTO :DWORD\n";
	out << "WriteConsoleA    PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD\n\n";
	out << ".STACK 4096\n\n";	
	out << Gen_txt.CONST;
	out << "consoletitle db 'console title', 0";	
	out << "\n";
	out << Gen_txt.DATA;
	out << "\n";
	out << Gen_txt.CODE;
	out << Gen_txt.MAIN;
	out << "\npush 0\ncall ExitProcess\nmain ENDP\nend main\n";
	out.close();
	std::cout << "end" << endl;

}
