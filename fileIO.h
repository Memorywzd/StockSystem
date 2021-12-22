#pragma once

#include <iostream>
#include <fstream>
#include <Windows.h>

#include "libxl.h"

using namespace std;
using namespace libxl;

class fileIO
{
public:
	fileIO(const wchar_t*, bool, int, const wchar_t*);
	~fileIO();
	char* w2c(char*, const wchar_t*, size_t);//�˺���֧�����Ķ�ȡ����ʾ���������������������� 

private:
	const wchar_t* path_to_save;
	bool isTxt = false;

	ifstream txtfile;
	Book* book;
	Sheet* sheetread;
	CellType celltype;
	Format* format;
	string strcont;
	double numcont;
};

