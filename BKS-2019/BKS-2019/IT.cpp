#include <iostream>
#include"IT.h"

using namespace IT;

IdTable IT::Create() {

	IdTable IdTable = {};
	IdTable.maxsize = TI_MAXSIZE;
	IdTable.size = 0;
	IdTable.table = new Entry[IdTable.maxsize];

	return IdTable;
}

void IT::Add(IdTable& idtable, Entry entry) {

	idtable.table[idtable.size] = entry;
	idtable.size++;
}

void IT::Delete(IdTable& idtable) {

	IdTable temp = {};
	idtable = temp;

}

Entry IT::GetEntry(IdTable &idtable, int n) {

	return idtable.table[n];
}

bool IT::IsId(IdTable &idtable, char id[ID_MAXSIZE]) {

	for (int i = idtable.size - 1; i >= 0; i--)
	{
		if (!strcmp(id, idtable.table[i].id))
		{
			return 1;
		}
	}
	return 0;
}