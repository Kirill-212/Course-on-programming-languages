#include <iostream>
#include "LT.h"
using namespace LT;


LexTable LT::Create() {

	LexTable LexTable = {};
	LexTable.size = 0;
	LexTable.maxsize = LT_MAXSIZE;
	LexTable.table = new Entry[LexTable.maxsize];

	return LexTable;
}

void LT::Add(LexTable& lextable, Entry entry) {

	lextable.table[lextable.size] = entry;
	lextable.size++;

}

void LT::Delete(LexTable& lextable) {

	LexTable temp = {};
	lextable = temp;
}

Entry LT::GetEntry(LexTable &lextable, int n) {

	return lextable.table[n];
}