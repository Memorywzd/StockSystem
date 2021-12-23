#include <iostream>
#include "libxl.h"

#include "fileIO.h"
#include "stock.h"
#include "ds.h"

using namespace std;
using namespace libxl;

void initsys(LinkList& intro_LinkList, fileIO& intro_file)
{
	for (int i = 1; i <= 200; i++)
	{
		stock tempStock;
		intro_file.readline(i);
		//cout << intro_file.get_cont_str() << endl;
		tempStock.initStock(intro_file.get_cont_str());
		intro_LinkList.add_data(tempStock);
	}
	/*LNode* temp = intro_LinkList.get_head_ptr()->next;
	int maxlen = 0;
	while (temp)
	{
		if(temp->key_stock.getweb().length()>maxlen)
			maxlen= temp->key_stock.getweb().length();
		temp = temp->next;
	}
	cout << maxlen << endl;*/
}

int main()
{
	
	LinkList intro_LinkList;
	fileIO intro_file("./data/A股公司简介.xlsx");
	initsys(intro_LinkList, intro_file);
	hashSearch search_obj(intro_LinkList);
	string dest_key;
	/*cout << "输入股票代码，0结束输入" << endl;
	while (cin >> dest_key && dest_key != "0")
	{
		if (!search_obj.hash_search(dest_key))cout << "fail!" << endl;
	}*/
	cout << "输入股票网址，0结束输入" << endl;
	while (cin >> dest_key && dest_key != "0")
	{
		intro_LinkList.KMP_search(dest_key);
	}
	
	return 0;
}