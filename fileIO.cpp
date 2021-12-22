#include "fileIO.h"

fileIO::fileIO(const wchar_t* path, bool writeflag = false,int sheetnum = 0,const wchar_t* savepath=L"0")
{
	wstring paths(path);
	const wchar_t* txtpath = L"./data/股票交易日志";
	if(paths[13] == *txtpath)
	{
		isTxt = true;
		txtfile.open(path);
	}
	else
	{
		book = xlCreateXMLBook();
		book->setKey(L"TommoT", L"windows-2421220b07c2e10a6eb96768a2p7r6gc");
		if (book->load(path))
		{
			sheetread = book->getSheet(sheetnum);
			if (savepath == L"0")path_to_save = path;
			else path_to_save = savepath;
		}
	}
}

fileIO::~fileIO()
{
	if (isTxt)
	{
		txtfile.close();
	}
	else
	{
		book->save(path_to_save);
		book->release();
	}
}

//此函数支持中文读取和显示，需加入否则中文内容乱码
char* fileIO::w2c(char* pcstr, const wchar_t* pwstr, size_t len)
{
	//获取转换后的长度
	int nlength = wcslen(pwstr);
	//映射一个unicode字符串到一个多字节字符串
	int nbytes = WideCharToMultiByte(0, 0, pwstr, nlength, NULL, 0, NULL, NULL); 
	if (nbytes > len)nbytes = len;
	// 通过以上得到的结果，转换unicode 字符为ascii 字符
	WideCharToMultiByte(0, 0, pwstr, nlength, pcstr, nbytes, NULL, NULL);

	return pcstr;
}