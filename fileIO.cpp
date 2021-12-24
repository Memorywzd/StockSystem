#include "fileIO.h"

fileIO::fileIO(string path, int sheetnum)
{
	const char* pathc = path.data();
	string dest = "./data/股票交易日志";
	string sour = path.substr(0, 19);
	if (sour == dest)
	{
		isTxt = true;
		txtfile.open(path);
	}
	else
	{
		book = xlCreateXMLBook();
		book->setKey("TommoT", "windows-2421220b07c2e10a6eb96768a2p7r6gc");
		if (book->load(pathc))
		{
			sheetread = book->getSheet(sheetnum);
			path_to_save = path;
		}
	}
}

fileIO::fileIO(string path, string writeflag, string savepath)
{
	const char* pathc = path.data();
	const char* txtpath = "./data/股票交易日志";
	if(path[13] == *txtpath)
	{
		isTxt = true;
		txtfile.open(path);
	}
	else
	{
		book = xlCreateXMLBook();
		book->setKey("TommoT", "windows-2421220b07c2e10a6eb96768a2p7r6gc");
		if (book->load(pathc))
		{
			sheetread = book->getSheet(0);
			//if (savepath == "0")*path_to_save = *pathc;
			//else *path_to_save = *savepath;
		}
	}
}

fileIO::~fileIO()
{
	const char* pathc = path_to_save.data();
	if (isTxt)
		txtfile.close();
	else
	{
		book->save(pathc);
		book->release();
	}
}

void fileIO::readline(int row)
{
	//列遍历
	strcont = "";
	for (int col = sheetread->firstCol(); col < sheetread->lastCol(); col++)
	{
		//读取某行某列的单元格的类型。有字符串型，数值型，空值。
		CellType celltype = sheetread->cellType(row, col);
		//从单元格中读取字符串及其格式
		if (celltype == CELLTYPE_STRING)
		{
			const char* pcstr = sheetread->readStr(row, col);
			string temp = pcstr;
			strcont += temp + " ";
		}
		else if (celltype == CELLTYPE_NUMBER)
		{
			const char* pcstr = sheetread->readStr(row, col);
			string temp = pcstr;
			strcont += temp + " ";
		}
		else if (celltype == CELLTYPE_BLANK)
		{
			strcont += "BLANK ";
		}
		else if (celltype == CELLTYPE_EMPTY)
		{
			strcont += "EMPTY ";
		}
		else strcont += "UNHANDLED ";
	}
}

void fileIO::readtxt(stock& tempStock)
{
	char buffer[100];
	bool firstline = true;
	string temp, trash;
	string tradeDate;
	double openPrice, closePrice;
	string qpc;
	double quotePerChange;
	while (txtfile)
	{
		txtfile.getline(buffer, 100);
		if (firstline)
		{
			firstline = false;
			continue;
		}
		temp = buffer;
		if (temp == "")continue;
		istringstream ss(temp);
		ss >> tradeDate >> openPrice >> closePrice;
		ss >> trash >> trash >> trash;
		ss >> trash >> trash >> trash;
		ss >> qpc;
		qpc.pop_back();
		quotePerChange = atof(qpc.c_str());
		tempStock.addLogData(tradeDate, openPrice, closePrice, quotePerChange);
	}
}
