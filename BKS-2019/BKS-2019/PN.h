#pragma once
 
namespace PN {
	bool PolishNotation(int n, LT::LexTable & lextable, IT::IdTable & idtable);
	int getP(LT::Entry table);
	void polish_notation(Lex::Tables td);
	bool PolishNotation1(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable);

}