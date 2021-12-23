#include <iostream>
#include "libxl.h"

#include "fileIO.h"
#include "stock.h"
#include "ds.h"

using namespace std;
using namespace libxl;

void initsys(LinkList& data_LinkList, fileIO& intro_file)
{
	for (int i = 1; i <= 200; i++)
	{
		stock tempStock;

		intro_file.readline(i);
		tempStock.initStock(intro_file.get_cont_str());//初始化基本数据

		string tradeLog_path;
		tradeLog_path += "./data/股票交易日志/" + tempStock.getCode() + ".txt";
		fileIO log_file(tradeLog_path);
		tempStock.initTradeLog();
		log_file.readtxt(tempStock);//初始化交易日志

		data_LinkList.add_data(tempStock);//放入数据链表
	}
	/*LNode* temp = data_LinkList.get_head_ptr()->next;
	while (temp)
	{
		cout << temp->key_stock.getCode() << endl << "交易记录：" << endl;
		priceList temp1 = temp->key_stock.getLog_ptr()->next;
		while (temp1)
		{
			cout << temp1->tradeDate << ' ' << temp1->openPrice << ' ';
			cout << temp1->closePrice << ' ' << temp1->quotePerChange << endl;
			temp1 = temp1->next;
		}
		temp = temp->next;
	}*/
}

int main()
{
	
	LinkList data_LinkList;
	fileIO intro_file("./data/A股公司简介.xlsx");
	initsys(data_LinkList, intro_file);
	hashSearch search_obj(data_LinkList);
	BSTree bsTree();
	string dest_key;
	/*cout << "哈希查找：输入股票代码，0结束输入" << endl;
	while (cin >> dest_key && dest_key != "0")
	{
		if (!search_obj.hash_search(dest_key))cout << "fail!" << endl;
	}*/
	/*cout << "KMP匹配：输入股票网址，0结束输入" << endl;
	while (cin >> dest_key && dest_key != "0")
	{
		data_LinkList.KMP_search(dest_key);
	}*/
	cout << "二叉排序树查找：输入股票代码，0结束输入" << endl;
	while (cin >> dest_key && dest_key != "0")
	{

	}
	
	return 0;
}