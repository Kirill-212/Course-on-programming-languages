#include "Lex.h"
#include "PN.h"
#include <queue>
#include<stack>
using namespace std;
bool PN::PolishNotation(int n, LT::LexTable & lextable, IT::IdTable & idtable)
{

	std::queue<LT::Entry> current;
	std::stack<LT::Entry> stack;

	int i = n;
	int priority;
	int parCount = 0;

	while (lextable.table[i].lexema != ';')
	{
		priority = getP(lextable.table[i]);

		if (lextable.table[i].lexema == 'i' && lextable.table[i + 1].lexema == '(') // попали на вызов функции.
		{
			i++;
			priority = getP(lextable.table[i]);
			while (priority < 2)
			{
				if (priority == 0)
				{
					current.push(lextable.table[i]);
					parCount++;
				}
				else if (priority == 1)stack.push(lextable.table[i]);
				else if (priority == -2);
				else if (priority == -1)
				{
					while (getP(stack.top()) != 1) // выталкиваем стек пока не встретим открывашку.
					{
						current.push(stack.top());
						stack.pop();
					}
					stack.pop();
					current.push({ '@', lextable.table[i].sn, lextable.table[i].indexLT, parCount });
					i++;
					priority = getP(lextable.table[i]);
					break;
				}

				i++;
				priority = getP(lextable.table[i]);
			}
		}

		if (priority == 0) current.push(lextable.table[i]);
		else if (priority == 1) stack.push(lextable.table[i]);
		else if (priority == 2 || priority == 3)
		{
			while (!stack.empty())
			{
				if (getP(stack.top()) >= priority)
				{
					current.push(stack.top());
					stack.pop();
				}
				else break;
			}
			stack.push(lextable.table[i]);
		}
		else if (priority == -1)
		{
			while (getP(stack.top()) != 1) // выталкиваем стек пока не встретим открывашку.
			{
				current.push(stack.top());
				stack.pop();
			}
			stack.pop();
		}
		else if (priority == -3) break;
		i++;
	}
	while (!stack.empty())
	{
		current.push(stack.top());
		stack.pop();
	}
	current.push(lextable.table[i]);
	//обратная польская запись построена.


	int posLast = i; // позиция последнего символа выражения до польской записи
	i = n;

	for (i; i <= posLast; i++) {
		lextable.table[i] = { '#' , -1 , i , -1 };
		while (!current.empty())
		{
			lextable.table[i] = current.front();
			lextable.table[i].indexLT = i;
			current.pop();
			i++;
		}

	}
	return true;
}

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