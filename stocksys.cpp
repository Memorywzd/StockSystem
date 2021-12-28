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
		tempStock.initStock(intro_file.get_cont_str());//��ʼ���������

		string tradeLog_path;
		tradeLog_path += "./data/��Ʊ������־/" + tempStock.getCode() + ".txt";
		fileIO log_file(tradeLog_path);
		tempStock.initTradeLog();
		log_file.readtxt(tempStock);//��ʼ��������־

		data_LinkList.add_data(tempStock);//������������
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

	fileIO intro_file("./data/A�ɹ�˾���.xlsx");
	fileIO mes_file("./data/60֧��Ʊ��Ϣ.xlsx", 1);
	fileIO graph_file("./data/60֧��Ʊ��Ϣ.xlsx", 0);

	initsys(data_LinkList, sixtydata_List, graph, intro_file, mes_file, graph_file);

	hashSearch search_obj(data_LinkList);
	BSTree bsTree(data_LinkList);

	string dest_key;
	/*cout << "��ϣ���ң������Ʊ���룬0��������" << endl;
	while (cin >> dest_key && dest_key != "0")
	{
		search_obj.hash_search(dest_key);
	}*/
	/*cout << "KMPƥ�䣺�����Ʊ��ַ��0��������" << endl;
	while (cin >> dest_key && dest_key != "0")
	{
		data_LinkList.KMP_search(dest_key);
	}*/
	/*cout << "�������������ҡ�ɾ���������Ʊ���룬0��������" << endl;
	while (cin >> dest_key && dest_key != "0")
	{
		bsTree.BSsearch(dest_key);
		bsTree.deleteBST(dest_key);
	}*/
	/*cout << "���������ڲ�ɼۣ��������ڣ�0��������" << endl;
	while (cin >> dest_key && dest_key != "0")
	{
		data_LinkList.search_price_by_date(dest_key);
	}*/
	/*cout << "����ֱ�Ӳ��Źɼۣ��������ڣ�0��������" << endl;
	while (cin >> dest_key && dest_key != "0")
	{
		data_LinkList.creatPricelist(dest_key);
		data_LinkList.insertSort("rate");
	}*/
	/*cout << "��ҵ�����ǵ�����������ҵ��0��������" << endl;
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
	/*cout << "�򵥲������֡����̼ۣ�û������" << endl;
	sixtydata_List.easySort("score");
	sixtydata_List.showES();
	cout << endl;
	sixtydata_List.easySort("close");
	sixtydata_List.showES();*/
	/*cout << "�����·�����������������Ż����ƻ���룬0��������" << endl;
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
	/*cout << "prim��kruskal����ɸѡ������prim����ʼ�㣬0��������" << endl;
	int pos;
	while (cin >> pos && pos != 0)
	{
		graph.prime(sixtydata_List, pos);
		cout << endl;
		graph.kruskal(sixtydata_List);
	}*/
	/*cout << "����ͼ����ɸѡ������10���㣬0��������" << endl;
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
