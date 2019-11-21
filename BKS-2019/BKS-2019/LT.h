#pragma once
#define LEXEMA_FIXSIZE	1
#define LT_MAXSIZE		4096
#define LT_TI_NULLIDX	0xffffffff
#define LEX_INT  		't'//correct 1 25
#define LEX_STRING		't'//+ 2
#define LEX_BOOL		't'//new 3
#define LEX_ID			'i'//+ 4
#define LEX_LITERAL		'l'//+ 5
#define LEX_FUNCTION	'f'//+ 6 
#define LEX_DEC 		'd'// ????????? 7
#define LEX_RETURN      'r'//+ 8
#define LEX_PRINT		'p'//+ p 9
#define LEX_SEMICOLON	';'//+ ; 10
#define LEX_COMMA		','//+ , 11
#define LEX_LEFTBRACE	'{'//+ { 12
#define LEX_BRACELET	'}'//+ } 13
#define LEX_LEFTHESIS	'('//+ ( 14
#define LEX_RIGHTHESIS	')'//+ ) 15
#define LEX_PLUS		'+'//+ + 16
#define LEX_MINUS		'-'//+ - 17
#define LEX_STAR		'*'//+ * 18
#define LEX_DIRSLASH	'/'//+ 19
#define LEX_EQUAL       '='//+ 20
#define LEX_MAIN		'm'//+ 21
#define LEX_IF  		'?'//if 22
#define LEX_EQUAL_IF	'=='//== 23
#define LEX_PERSENT     '%'//% 24
#define LEX_TRUE 'T'//25
#define LEX_FALSE 'F'//26


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
