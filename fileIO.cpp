#include "fileIO.h"

fileIO::fileIO(string path)
{
	const char* pathc = path.data();
	const char* txtpath = "./data/股票交易日志";
	if (path[13] == *txtpath)
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
			path_to_save = path;
		}
	}
}

fileIO::fileIO(string path, bool writeflag, int sheetnum = 0, const char* savepath = "0")
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
			sheetread = book->getSheet(sheetnum);
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
	for (int col = sheetread->firstCol(); col < sheetread->lastCol(); col++)
	{
		//从单元格中读取字符串及其格式
		const char* pcstr = sheetread->readStr(row, col);
		string temp = pcstr;
		strcont += temp + " ";
	}
}