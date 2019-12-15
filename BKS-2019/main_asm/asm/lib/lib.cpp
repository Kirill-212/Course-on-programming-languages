#include<iostream>
#include <cstdlib>
#include<string>
extern "C" {
	void ConsoleInt(short value)
	{
		std::cout << value << std::endl;
	}

	void ConsoleStr(char* value)
	{
		std::cout << value << std::endl;
	}

	void ConsoleBool(int value)
	{
		if (value) std::cout << "true" << std::endl;
		else std::cout << "false" << std::endl;
	}


	int stringtoint(char* arr) {
		int N = std::strlen(arr);
		int res = 0;
		int i = 0;
		int col = 1;
		for (; i < N; i++) {
			col = col * 10;
		}
		col = col / 10;
		for (i = 0; i < N; i++) {
			res += ((int)arr[i] - (int)'0')*col;
			col = col / 10;
		}
		return res;
	}


	
	int strlen1(char* arr) {
		
		int res = std::strlen(arr);
		return res;
	}


}
