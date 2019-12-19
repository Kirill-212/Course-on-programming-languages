#pragma once
#include "FST.h"
#include "Log.h"
#include "IT.h"
#include"LT.h"
#include"In.h"
#include<vector>
#define N_GRAPHS 28
#define LIBFUNCTIONS 2

#define GRAPH_string  (7,   \
FST::NODE(1, FST::RELATION('s', 1)), \
FST::NODE(1, FST::RELATION('t', 2)), \
FST::NODE(1, FST::RELATION('r', 3)), \
FST::NODE(1, FST::RELATION('i', 4)), \
FST::NODE(1, FST::RELATION('n', 5)), \
FST::NODE(1, FST::RELATION('g', 6)), \
FST::NODE())

#define GRAPH_int (4,	\
FST::NODE(1, FST::RELATION('i', 1)),\
FST::NODE(1, FST::RELATION('n', 2)),\
FST::NODE(1, FST::RELATION('t', 3)),\
FST::NODE())

#define GRAPH_bool  (5,   \
FST::NODE(1, FST::RELATION('b', 1)), \
FST::NODE(1, FST::RELATION('o', 2)), \
FST::NODE(1, FST::RELATION('o', 3)), \
FST::NODE(1, FST::RELATION('l', 4)), \
FST::NODE())

#define GRAPH_function (9,\
FST::NODE(1, FST::RELATION('f', 1)),\
FST::NODE(1, FST::RELATION('u', 2)),\
FST::NODE(1, FST::RELATION('n', 3)),\
FST::NODE(1, FST::RELATION('c', 4)),\
FST::NODE(1, FST::RELATION('t', 5)),\
FST::NODE(1, FST::RELATION('i', 6)),\
FST::NODE(1, FST::RELATION('o', 7)),\
FST::NODE(1, FST::RELATION('n', 8)),\
FST::NODE())

#define GRAPH_print (6,\
FST::NODE(1, FST::RELATION('p', 1)),\
FST::NODE(1, FST::RELATION('r', 2)),\
FST::NODE(1, FST::RELATION('i', 3)),\
FST::NODE(1, FST::RELATION('n', 4)),\
FST::NODE(1, FST::RELATION('t', 5)),\
FST::NODE())
#define GRAPH_if (3,\
FST::NODE(1, FST::RELATION('i', 1)),\
FST::NODE(1, FST::RELATION('f', 2)),\
FST::NODE())
#define GRAPH_EQUAL_IF (3,\
FST::NODE(1, FST::RELATION('=', 1)),\
FST::NODE(1, FST::RELATION('=', 2)),\
	FST::NODE())


#define GRAPH_main ( 5,\
FST::NODE(1, FST::RELATION('m', 1)),\
FST::NODE(1, FST::RELATION('a', 2)),\
FST::NODE(1, FST::RELATION('i', 3)),\
FST::NODE(1, FST::RELATION('n', 4)),\
FST::NODE())

#define GRAPH_dec (4,\
FST::NODE(1, FST::RELATION('d', 1)),\
FST::NODE(1, FST::RELATION('e', 2)),\
FST::NODE(1, FST::RELATION('c', 3)),\
FST::NODE()) 


#define GRAPH_return (7,\
FST::NODE(1, FST::RELATION('r', 1)),\
FST::NODE(1, FST::RELATION('e', 2)),\
FST::NODE(1, FST::RELATION('t', 3)),\
FST::NODE(1, FST::RELATION('u', 4)),\
FST::NODE(1, FST::RELATION('r', 5)),\
FST::NODE(1, FST::RELATION('n', 6)),\
FST::NODE())
#define GRAPH_true (5,\
FST::NODE(1, FST::RELATION('t', 1)),\
FST::NODE(1, FST::RELATION('r', 2)),\
FST::NODE(1, FST::RELATION('u', 3)),\
FST::NODE(1, FST::RELATION('e', 4)),\
FST::NODE())
#define GRAPH_false (6,\
FST::NODE(1, FST::RELATION('f', 1)),\
FST::NODE(1, FST::RELATION('a', 2)),\
FST::NODE(1, FST::RELATION('l', 3)),\
FST::NODE(1, FST::RELATION('s', 4)),\
FST::NODE(1, FST::RELATION('e', 5)),\
FST::NODE())

#define GRAPH_stringtoint (12,\
FST::NODE(1, FST::RELATION('s', 1)),\
FST::NODE(1, FST::RELATION('t', 2)),\
FST::NODE(1, FST::RELATION('r', 3)),\
FST::NODE(1, FST::RELATION('i', 4)),\
FST::NODE(1, FST::RELATION('n', 5)),\
FST::NODE(1, FST::RELATION('g', 6)),\
FST::NODE(1, FST::RELATION('t', 7)),\
FST::NODE(1, FST::RELATION('o', 8)),\
FST::NODE(1, FST::RELATION('i', 9)),\
FST::NODE(1, FST::RELATION('n', 10)),\
FST::NODE(1, FST::RELATION('t', 11)),\
FST::NODE())

#define GRAPH_stringtoint (7,\
FST::NODE(1, FST::RELATION('s', 1)),\
FST::NODE(1, FST::RELATION('t', 2)),\
FST::NODE(1, FST::RELATION('r', 3)),\
FST::NODE(1, FST::RELATION('l', 4)),\
FST::NODE(1, FST::RELATION('e', 5)),\
FST::NODE(1, FST::RELATION('n', 6)),\
FST::NODE())


#define GRAPH_integer_literal10 (3,\
FST::NODE(21, FST::RELATION('1', 1), FST::RELATION('-', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), \
	FST::RELATION('4', 1), FST::RELATION('5', 1), FST::RELATION('6', 1), \
	FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1), FST::RELATION('0', 1), \
	FST::RELATION('1', 2), FST::RELATION('2', 2), FST::RELATION('3', 2), \
	FST::RELATION('4', 2), FST::RELATION('5', 2), FST::RELATION('6', 2), \
	FST::RELATION('7', 2), FST::RELATION('8', 2), FST::RELATION('9', 2), FST::RELATION('0', 2)), \
	\
	FST::NODE(20, FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), \
		FST::RELATION('4', 1), FST::RELATION('5', 1), FST::RELATION('6', 1), \
		FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1), FST::RELATION('0', 1), \
		FST::RELATION('1', 2), FST::RELATION('2', 2), FST::RELATION('3', 2), \
		FST::RELATION('4', 2), FST::RELATION('5', 2), FST::RELATION('6', 2), \
		FST::RELATION('7', 2), FST::RELATION('8', 2), FST::RELATION('9', 2), FST::RELATION('0', 2)), \
	FST::NODE())
#define GRAPH_integer_literal8 (5, \
FST::NODE(2, FST::RELATION('0', 1), FST::RELATION('-', 1)),\
FST::NODE(1, FST::RELATION('0', 2)), \
FST::NODE(16, FST::RELATION('1', 3), FST::RELATION('2', 3), FST::RELATION('3', 3), \
	FST::RELATION('4', 3), FST::RELATION('5', 3), FST::RELATION('6', 3), \
	FST::RELATION('7', 3), FST::RELATION('0', 3), \
	FST::RELATION('1', 4), FST::RELATION('2', 4), FST::RELATION('3', 4), \
	FST::RELATION('4', 4), FST::RELATION('5', 4), FST::RELATION('6', 4), \
	FST::RELATION('7', 4), FST::RELATION('0', 4)), \
	\
	FST::NODE(16, FST::RELATION('1', 3), FST::RELATION('2', 3), FST::RELATION('3', 3), \
		FST::RELATION('4', 3), FST::RELATION('5', 3), FST::RELATION('6', 3), \
		FST::RELATION('7', 3), FST::RELATION('0', 3), \
		FST::RELATION('1', 4), FST::RELATION('2', 4), FST::RELATION('3', 4), \
		FST::RELATION('4', 4), FST::RELATION('5', 4), FST::RELATION('6', 4), \
		FST::RELATION('7', 4), FST::RELATION('0', 4)), \
	FST::NODE())

#define GRAPH_id (3, FST::NODE(52, FST::RELATION('a', 1), FST::RELATION('b', 1), FST::RELATION('c', 1), FST::RELATION('d', 1), \
	FST::RELATION('e', 1), FST::RELATION('f', 1), FST::RELATION('g', 1), FST::RELATION('h', 1), \
	FST::RELATION('i', 1), FST::RELATION('j', 1), FST::RELATION('k', 1), FST::RELATION('l', 1), \
	FST::RELATION('m', 1), FST::RELATION('n', 1), FST::RELATION('o', 1), FST::RELATION('p', 1), \
	FST::RELATION('q', 1), FST::RELATION('r', 1), FST::RELATION('s', 1), FST::RELATION('t', 1), \
	FST::RELATION('u', 1), FST::RELATION('v', 1), FST::RELATION('w', 1), FST::RELATION('x', 1), \
	FST::RELATION('y', 1), FST::RELATION('z', 1), \
	FST::RELATION('a', 2), FST::RELATION('b', 2), FST::RELATION('c', 2), FST::RELATION('d', 2), \
	FST::RELATION('e', 2), FST::RELATION('f', 2), FST::RELATION('g', 2), FST::RELATION('h', 2), \
	FST::RELATION('i', 2), FST::RELATION('j', 2), FST::RELATION('k', 2), FST::RELATION('l', 2), \
	FST::RELATION('m', 2), FST::RELATION('n', 2), FST::RELATION('o', 2), FST::RELATION('p', 2), \
	FST::RELATION('q', 2), FST::RELATION('r', 2), FST::RELATION('s', 2), FST::RELATION('t', 2), \
	FST::RELATION('u', 2), FST::RELATION('v', 2), FST::RELATION('w', 2), FST::RELATION('x', 2), \
	FST::RELATION('y', 2), FST::RELATION('z', 2)), \
	FST::NODE(62, FST::RELATION('a', 1), FST::RELATION('b', 1), FST::RELATION('c', 1), FST::RELATION('d', 1), \
		FST::RELATION('e', 1), FST::RELATION('f', 1), FST::RELATION('g', 1), FST::RELATION('h', 1), \
		FST::RELATION('i', 1), FST::RELATION('j', 1), FST::RELATION('k', 1), FST::RELATION('l', 1), \
		FST::RELATION('m', 1), FST::RELATION('n', 1), FST::RELATION('o', 1), FST::RELATION('p', 1), \
		FST::RELATION('q', 1), FST::RELATION('r', 1), FST::RELATION('s', 1), FST::RELATION('t', 1), \
		FST::RELATION('u', 1), FST::RELATION('v', 1), FST::RELATION('w', 1), FST::RELATION('x', 1), \
		FST::RELATION('y', 1), FST::RELATION('z', 1), \
		FST::RELATION('a', 2), FST::RELATION('b', 2), FST::RELATION('c', 2), FST::RELATION('d', 2), \
		FST::RELATION('e', 2), FST::RELATION('f', 2), FST::RELATION('g', 2), FST::RELATION('h', 2), \
		FST::RELATION('i', 2), FST::RELATION('j', 2), FST::RELATION('k', 2), FST::RELATION('l', 2), \
		FST::RELATION('m', 2), FST::RELATION('n', 2), FST::RELATION('o', 2), FST::RELATION('p', 2), \
		FST::RELATION('q', 2), FST::RELATION('r', 2), FST::RELATION('s', 2), FST::RELATION('t', 2), \
		FST::RELATION('u', 2), FST::RELATION('v', 2), FST::RELATION('w', 2), FST::RELATION('x', 2), \
		FST::RELATION('y', 2), FST::RELATION('z', 2), \
		FST::RELATION('1', 2), FST::RELATION('2', 2), FST::RELATION('3', 2), FST::RELATION('4', 2), \
		FST::RELATION('5', 2), FST::RELATION('6', 2), FST::RELATION('7', 2), FST::RELATION('8', 2), \
		FST::RELATION('9', 2), FST::RELATION('0', 2)), \
	FST::NODE())

#define GRAPH_string_literal (3, FST::NODE(1, FST::RELATION('\'', 1)), \
FST::NODE(89, \
	FST::RELATION('a', 1), FST::RELATION('b', 1), FST::RELATION('c', 1), FST::RELATION('d', 1), \
	FST::RELATION('e', 1), FST::RELATION('f', 1), FST::RELATION('g', 1), FST::RELATION('h', 1), \
	FST::RELATION('i', 1), FST::RELATION('j', 1), FST::RELATION('k', 1), FST::RELATION('l', 1), \
	FST::RELATION('m', 1), FST::RELATION('n', 1), FST::RELATION('o', 1), FST::RELATION('p', 1), \
	FST::RELATION('q', 1), FST::RELATION('r', 1), FST::RELATION('s', 1), FST::RELATION('t', 1), \
	FST::RELATION('u', 1), FST::RELATION('v', 1), FST::RELATION('w', 1), FST::RELATION('x', 1), \
	FST::RELATION('y', 1), FST::RELATION('z', 1), \
	FST::RELATION('A', 1), FST::RELATION('B', 1), FST::RELATION('C', 1), FST::RELATION('D', 1), \
	FST::RELATION('E', 1), FST::RELATION('F', 1), FST::RELATION('G', 1), FST::RELATION('H', 1), \
	FST::RELATION('I', 1), FST::RELATION('J', 1), FST::RELATION('K', 1), FST::RELATION('L', 1), \
	FST::RELATION('M', 1), FST::RELATION('N', 1), FST::RELATION('O', 1), FST::RELATION('P', 1), \
	FST::RELATION('Q', 1), FST::RELATION('R', 1), FST::RELATION('S', 1), FST::RELATION('T', 1), \
	FST::RELATION('U', 1), FST::RELATION('V', 1), FST::RELATION('W', 1), FST::RELATION('X', 1), \
	FST::RELATION('Y', 1), FST::RELATION('Z', 1), \
	FST::RELATION('0', 1), FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), \
	FST::RELATION('4', 1), FST::RELATION('5', 1), FST::RELATION('6', 1), FST::RELATION('7', 1), \
	FST::RELATION('8', 1), FST::RELATION('9', 1), \
	FST::RELATION(' ', 1), FST::RELATION(',', 1), FST::RELATION('.', 1), FST::RELATION(';', 1), \
	FST::RELATION('-', 1), FST::RELATION('+', 1), FST::RELATION('*', 1), FST::RELATION('/', 1), \
	FST::RELATION('=', 1), FST::RELATION(':', 1), FST::RELATION(')', 1), FST::RELATION('(', 1), \
	FST::RELATION('}', 1), FST::RELATION('{', 1), FST::RELATION(']', 1), FST::RELATION('[', 1), \
	FST::RELATION('!', 1), FST::RELATION('?', 1), FST::RELATION('#', 1), FST::RELATION('&', 1), \
	FST::RELATION('>', 1), FST::RELATION('<', 1), FST::RELATION('[', 1), FST::RELATION(']', 1), \
	FST::RELATION('\'', 2)), \
	FST::NODE())

#define GRAPH_SEMICOLON (2,FST::NODE(1, FST::RELATION(';', 1)),\
	FST::NODE())

#define GRAPH_COMMA (2,FST::NODE(1, FST::RELATION(',', 1)),\
	FST::NODE())

#define GRAPH_LEFTBRCE (2,FST::NODE(1, FST::RELATION('{', 1)),\
	FST::NODE())

#define GRAPH_BRACELET (2,FST::NODE(1, FST::RELATION(' }', 1)),\
	FST::NODE())

#define GRAPH_LEFTHESIS (2,FST::NODE(1, FST::RELATION('(', 1)),\
	FST::NODE())

#define GRAPH_RIGHTHESIS (2,FST::NODE(1, FST::RELATION(')', 1)),\
	FST::NODE())

#define GRAPH_PLUS (2,FST::NODE(1, FST::RELATION('+', 1)),\
	FST::NODE())

#define GRAPH_MINUS (2,FST::NODE(1, FST::RELATION('-', 1)),\
	FST::NODE())

#define GRAPH_START (2,FST::NODE(1, FST::RELATION('*', 1)),\
	FST::NODE())

#define GRAPH_DIRSLASH (2,FST::NODE(1, FST::RELATION('/', 1)),\
	FST::NODE())

#define GRAPH_EQUAL (2,FST::NODE(1, FST::RELATION('=', 1)),\
	FST::NODE())
#define GRAPH_PERSENT (2,FST::NODE(1, FST::RELATION('%', 1)),\
	FST::NODE())


namespace Lex {




	

	struct Machines
	{
		char lexema;
		FST::FST machine;
	};
	struct Par_function {
		int indxLT;
		std::vector<IT::IDDATATYPE> type;
	};
	struct Word_array
	{
		char ** array;		// массив слов
		int n;				// количество слов
		int *sn;			// номера строки

	};

	struct Tables {
		LT::LexTable LexTable;
		IT::IdTable  idTable;
	};
	void chekDelaring(Tables td);
	void Sem_analiz(Tables table);
	Tables Lex_analyz_new(In::IN g);
	int ret_index_for_expression(int pos, std::vector<Lex::Par_function> par_func);
}