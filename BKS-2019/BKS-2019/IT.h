#pragma once
#define ID_MAXSIZE 5//максимальное кол-во символов в идентификаторе
#define TI_MAXSIZE 4096//максимальное кол-во строк в таблице идентификаторов
#define  TI_INT_DEFAULT 0x00000000//значание по умолчанию для типа integer
#define TI_STR_DEFAULT 0x00// значение типа по умолчанию для типа string
#define  TI_NULLIDX 0xffffffff//нет элемента таблицы идентификаторов
#define  TI_STR_MAXSIZE 255

namespace IT {

	enum IDDATATYPE { INT = 1, STR = 2 };		// типы данных индентификаторов: integer , string
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4 };    // типы идентификаторов: переменная, функция, параметр, литерал


	struct Entry {
		int idxfirstLE;							// индекс первой строки в таблице лексем
		char* id;								// идентификатор
		IDDATATYPE iddatatype;					// тип данных
		IDTYPE idtype;							// тип идентификатора
		union {
			int vint;							// значение integer
			struct {
				int len;						// количество символов в string
				char* str;	                    // cимволы string
			}vstr;								// значение string
		}value;									 // значение идентификатора

	};

	struct IdTable {
		int maxsize;
		int size;
		Entry* table;
	};

	IdTable Create();

	void Add(IdTable& idtable, Entry entry);

	Entry GetEntry(IdTable& idtable, int n);

	bool IsId(IdTable& idtable, char id[ID_MAXSIZE]); // есть ли индентификатор в таблице

	void Delete(IdTable& idtable);
}