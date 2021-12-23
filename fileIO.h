#pragma once

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <sstream>

#include "libxl.h"
#include "stock.h"

using namespace std;
using namespace libxl;

class fileIO
{
public:
	fileIO(string);							// read only
	fileIO(string, bool, int, const char*);	// r/w
	~fileIO();
	void readline(int);
	void readtxt(stock&);
	string get_cont_str() { return strcont; }

private:
	string path_to_save;
	bool isTxt = false;

	ifstream txtfile;
	Book* book;
	Sheet* sheetread;

	string strcont;
	//double numcont;
};

