#include<iostream>
#include <cstdlib>
#include<string>
extern "C" {

	int getmin(int* f, int col) {
		int s = f[0];
		for (int i = 0; i < col; i++) {
			if (s > f[i]) {
				s = f[i];
			}
		}
		return s;
	}
	int getmax(int* f, int col) {
		int s = f[0];
		for (int i = 0; i < col; i++) {
			if (s < f[i]) {
				s = f[i];
			}
		}
		return s;
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
