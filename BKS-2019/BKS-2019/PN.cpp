#include "Lex.h"
#include "PN.h"
#include <queue>
#include<stack>
using namespace std;


int PN::getP(LT::Entry table)
{

	char token = table.lexema;

	if (token == 'v') token = table.value;

	if (token == '*' || token == '/') return 3;
	else if (token == '+' || token == '-'||token=='%') return 2;
	else if (token == '(') return 1;
	else if (token == ')') return -1;
	else if (token == ',') return -2;
	else if (token == ';') return -3;
	else return 0;
}



bool PN::PolishNotation1(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable) {
	stack<LT::Entry> st;
	int getprior;
	int in_id=-1;
	bool flag = false;
	int cobaka = 0;
	queue<LT::Entry> myQueue;
	int end;
	for (int i = lextable_pos; i < lextable.size; i++) {
		if (lextable.table[i].lexema == 'i'&&lextable.table[i + 1].lexema == '(') {
			in_id = lextable.table[i].idxTI;
			i++;
			flag = true;
		}
		if (lextable.table[i].lexema == ';') {
			end = i;
			break;
		}
		if (lextable.table[i].lexema != ',') {

			getprior = PN::getP(lextable.table[i]);
			if (getprior == 0) {
				myQueue.push(lextable.table[i]);
			}
			if (getprior == 1) {
				st.push(lextable.table[i]);
			}

			if (getprior > 1) {

				while (!st.empty()) {
					if (PN::getP(st.top()) >= getprior) {
						myQueue.push(st.top());
						st.pop();
					}
					else { break; }

				}
				st.push(lextable.table[i]);
			}

			if (getprior == -1) {

				while (PN::getP(st.top()) != 1) {
					myQueue.push(st.top());
					st.pop();
				}
				st.pop();
				if (flag) {
					cout << cobaka + 1 << endl;
					myQueue.push({ '@',myQueue.front().sn,cobaka + 1,in_id });
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
		if (lextable.table[end].lexema == ';') {
			lextable.table[end].lexema = '~';
		}
	}
	return 1;
}










void PN::polish_notation(Lex::Tables td)
{
	bool flag = false;
	int i = 0;
	for (i; i < td.LexTable.size; i++) {
		if (td.LexTable.table[i].lexema == '=') {
			
			if (td.LexTable.table[i+1].lexema != 'T') {
				if ( td.LexTable.table[i + 2].lexema != ';') {
					
								flag=PN::PolishNotation1(i, td.LexTable, td.idTable);
								
								i = i + 1;
					
				}

				
			}

			


		}
	}
}