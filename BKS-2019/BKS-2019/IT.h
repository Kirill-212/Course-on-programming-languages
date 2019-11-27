#pragma once
#define ID_MAXSIZE 5//������������ ���-�� �������� � ��������������
#define TI_MAXSIZE 4096//������������ ���-�� ����� � ������� ���������������
#define  TI_INT_DEFAULT 0x00000000//�������� �� ��������� ��� ���� intege
#define TI_BOOL_DEFAULT true //�� �� ��������� ��� bool 
#define TI_STR_DEFAULT 0x00// �������� ���� �� ��������� ��� ���� string
#define  TI_NULLIDX 0xffffffff//��� �������� ������� ���������������
#define  TI_STR_MAXSIZE 255

namespace IT {

	enum IDDATATYPE { INT = 1, STR = 2 ,BOOL=3,NODEF=0};		// ���� ������ ����������������: integer , string
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4 };    // ���� ���������������: ����������, �������, ��������, �������


	struct Entry {
		int idxfirstLE;							// ������ ������ ������ � ������� ������
		char* id;								// �������������
		IDDATATYPE iddatatype;					// ��� ������
		IDTYPE idtype;							// ��� ��������������
		union {
			int vint;							// �������� integer
			struct {
				int len;						// ���������� �������� � string
				char* str;	                    // c������ string
			}vstr;								// �������� string
			bool T_F;                           //�������� bool
		}value;									 // �������� ��������������

	};

	struct IdTable {
		int maxsize;
		int size;
		Entry* table;
	};

	IdTable Create();

	void Add(IdTable& idtable, Entry entry);

	Entry GetEntry(IdTable& idtable, int n);

	bool IsId(IdTable& idtable, char id[ID_MAXSIZE]); // ���� �� �������������� � �������

	void Delete(IdTable& idtable);
}