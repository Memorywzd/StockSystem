#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "libxl.h"
#include "stock.h"

using namespace std;
using namespace libxl;

class fileIO
{
public:
	fileIO(string, int sheetnum = 0);	// read only
	fileIO(string, string, int);		// r/w
	~fileIO();
	void readline(int);
	void readtxt(stock&);
	void write(string, int col, int row = -1);
	string get_cont_str() { return strcont; }

private:
	string path_to_save;
	bool isTxt = false;

	ifstream txtfile;
	Book* book;
	Sheet* sheetread;
	Sheet* sheetwrite;

	string strcont;
};
