#include "fileIO.h"

fileIO::fileIO(const wchar_t* path, bool writeflag = false,int sheetnum = 0,const wchar_t* savepath=L"0")
{
	wstring paths(path);
	const wchar_t* txtpath = L"./data/��Ʊ������־";
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

//�˺���֧�����Ķ�ȡ����ʾ����������������������
char* fileIO::w2c(char* pcstr, const wchar_t* pwstr, size_t len)
{
	//��ȡת����ĳ���
	int nlength = wcslen(pwstr);
	//ӳ��һ��unicode�ַ�����һ�����ֽ��ַ���
	int nbytes = WideCharToMultiByte(0, 0, pwstr, nlength, NULL, 0, NULL, NULL); 
	if (nbytes > len)nbytes = len;
	// ͨ�����ϵõ��Ľ����ת��unicode �ַ�Ϊascii �ַ�
	WideCharToMultiByte(0, 0, pwstr, nlength, pcstr, nbytes, NULL, NULL);

	return pcstr;
}