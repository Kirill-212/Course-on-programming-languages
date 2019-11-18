#pragma once
#define LEXEMA_FIXSIZE	1
#define LT_MAXSIZE		4096
#define LT_TI_NULLIDX	0xffffffff
#define LEX_INTEGER		't'
#define LEX_STRING		't'
#define LEX_ID			'i'
#define LEX_LITERAL		'l'
#define LEX_FUNCTION	'f'
#define LEX_DECLARE		'd'
#define LEX_RETURN      'r'
#define LEX_PRINT		'p'
#define LEX_SEMICOLON	';'
#define LEX_COMMA		','
#define LEX_LEFTBRACE	'{'
#define LEX_BRACELET	'}'
#define LEX_LEFTHESIS	'('
#define LEX_RIGHTHESIS	')'
#define LEX_PLUS		'+'
#define LEX_MINUS		'-'
#define LEX_STAR		'*'
#define LEX_DIRSLASH	'/'
#define LEX_EQUAL       '='
#define LEX_MAIN		'm'

namespace LT {

	struct Entry {
		char lexema; // лексема
		int sn;						 // номер строки
		int idxTI;					 // индекс в таблице индентификаторов
		char value;
	};

	struct LexTable {
		int maxsize;				 // макс размер таблицы лексем
		int size;					 // текущий размер
		Entry* table; 				 // массив строк таблицы лексем
	};


	LexTable Create();

	void Add(
		LexTable& lextable,			 // экземпл€р табл лексем
		Entry entry					 // строка таблицы лексем
	);

	Entry GetEntry(					 // получить строку в таблицу лексем
		LexTable& lextable,			 // экземпл€р табл лексем
		int n						 // номер получаемой строки			
	);

	void Delete(LexTable& lextable); // удалить таблицу лексем


};
