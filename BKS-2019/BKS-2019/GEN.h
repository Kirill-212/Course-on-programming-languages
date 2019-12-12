#pragma once
#include"Lex.h"

#include<string>
namespace GEN {
	struct Gen_text
	{
		std::string CONST = "\n.CONST\n\n";
		std::string DATA = ".DATA\n\n";
		std::string CODE = ".CODE\n\n";
		std::string MAIN = "main PROC\n\nSTART:\n\n";

	};
	 void	GetGeN(wchar_t* file, Lex::Tables td);
	 void FixID(Lex::Tables& tables);
}
