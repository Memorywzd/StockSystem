#pragma once

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>

#include "libxl.h"
#include "stock.h"

using namespace std;
using namespace libxl;

class fileIO
{
public:
	fileIO(string);
	fileIO(string, bool, int, const char*);
	~fileIO();
	void readline(int);
	string get_cont_str() { return strcont; }
	double get_cont_num() { return numcont; }

private:
	string path_to_save;
	bool isTxt = false;

	ifstream txtfile;
	Book* book;
	Sheet* sheetread;

	string strcont;
	double numcont;
};

