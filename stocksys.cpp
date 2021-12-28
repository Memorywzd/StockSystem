#include <iostream>
#include "libxl.h"

#include "fileIO.h"
#include "ds.h"

using namespace std;
using namespace libxl;

void initsys(LinkList& data_LinkList, sixtyList& sixtydata_List, AMGraph& graph,
			 fileIO& intro_file, fileIO& mes_file, fileIO& graph_file)
{
	for (int i = 1; i <= 200; i++)
	{
		stock tempStock;

		intro_file.readline(i);
		tempStock.initStock(intro_file.get_cont_str());//初始化简介数据

		string tradeLog_path;
		tradeLog_path += "./data/股票交易日志/" + tempStock.getCode() + ".txt";
		fileIO log_file(tradeLog_path);
		tempStock.initTradeLog();
		log_file.readtxt(tempStock);//初始化交易日志

		data_LinkList.add_data(tempStock);//放入数据链表
	}
	for (int i = 1; i <= 60; i++)
	{
		mes_file.readline(i);
		sixtydata_List.creatESList(data_LinkList, mes_file.get_cont_str());
	}
	graph.creatUDNv(sixtydata_List);
	for (int i = 1; i <= 83; i++)
	{ 
		graph_file.readline(i);
		graph.creatUDNa(graph_file.get_cont_str());
	}
}

int main()
{
	LinkList data_LinkList;
	sixtyList sixtydata_List;
	AMGraph graph;

	fileIO intro_file("./data/A股公司简介.xlsx");
	fileIO mes_file("./data/60支股票信息.xlsx", 1);
	fileIO graph_file("./data/60支股票信息.xlsx", 0);

	initsys(data_LinkList, sixtydata_List, graph, intro_file, mes_file, graph_file);

	hashSearch search_obj(data_LinkList);
	BSTree bsTree(data_LinkList);

	string dest_key;
	/*cout << "哈希查找：输入股票代码，0结束输入" << endl;
	while (cin >> dest_key && dest_key != "0")
	{
		search_obj.hash_search(dest_key);
	}*/
	/*cout << "KMP匹配：输入股票网址，0结束输入" << endl;
	while (cin >> dest_key && dest_key != "0")
	{
		data_LinkList.KMP_search(dest_key);
	}*/
	/*cout << "二叉排序树查找、删除：输入股票代码，0结束输入" << endl;
	while (cin >> dest_key && dest_key != "0")
	{
		bsTree.BSsearch(dest_key);
		bsTree.deleteBST(dest_key);
	}*/
	/*cout << "单链表日期查股价：输入日期，0结束输入" << endl;
	while (cin >> dest_key && dest_key != "0")
	{
		data_LinkList.search_price_by_date(dest_key);
	}*/
	/*cout << "日期直接插排股价：输入日期，0结束输入" << endl;
	while (cin >> dest_key && dest_key != "0")
	{
		data_LinkList.creatPricelist(dest_key);
		data_LinkList.insertSort("rate");
	}*/
	/*cout << "行业快排涨跌幅：输入行业，0结束输入" << endl;
	while (cin >> dest_key && dest_key != "0")
	{
		sixtyList* p = new sixtyList;
		for (int i = 1; i <= 60; i++)
		{
			mes_file.readline(i);
			p->creatQSList(data_LinkList, mes_file.get_cont_str(), dest_key);
		}
		p->quickSort();
		p->showQS();
		delete p;
	}*/
	/*cout << "简单插排评分、收盘价：没有输入" << endl;
	sixtydata_List.easySort("score");
	sixtydata_List.showES();
	cout << endl;
	sixtydata_List.easySort("close");
	sixtydata_List.showES();*/
	/*cout << "求最短路径：输入两个点的序号或名称或代码，0结束输入" << endl;
	while (cin >> dest_key && dest_key != "0")
	{
		string* dest2 = new string;
		cin >> *dest2;
		string* len = new string;
		string* rst = new string;
		graph.getMinLen(dest_key, *dest2, *len, *rst);
		cout << *len << ": " << *rst << endl;
		delete dest2, len, rst;
	}*/
	/*cout << "prim，kruskal基金筛选，输入prim的起始点，0结束输入" << endl;
	int pos;
	while (cin >> pos && pos != 0)
	{
		graph.prime(sixtydata_List, pos);
		cout << endl;
		graph.kruskal(sixtydata_List);
	}*/
	/*cout << "二部图基金筛选，输入10个点，0结束输入" << endl;
	int num[10];
	while (cin >> num[0] && num[0] != 0)
	{
		for (int i = 1; i < 10; i++)
		{
			cin >> num[i];
		}
		graph.bip(sixtydata_List, num);
	}*/
	
	return 0;
}
