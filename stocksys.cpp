#include <iostream>
#include "libxl.h"

#include "fileIO.h"
#include "stock.h"
#include "ds.h"

using namespace std;
using namespace libxl;

void initsys(LinkList& data_LinkList, sixtyList& sixtydata_List, fileIO& intro_file, fileIO& mes_file)
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
	/*LNode* temp = data_LinkList.get_head_ptr()->next;
	while (temp)
	{
		cout << temp->key_stock.getCode() << endl << "���׼�¼��" << endl;
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
	sixtyList sixtydata_List;

	fileIO intro_file("./data/A�ɹ�˾���.xlsx");
	fileIO mes_file("./data/60֧��Ʊ��Ϣ.xlsx", 1);

	initsys(data_LinkList, sixtydata_List, intro_file, mes_file);

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
	/*cout << "�������������ң������Ʊ���룬0��������" << endl;
	while (cin >> dest_key && dest_key != "0")
	{
		bsTree.BSsearch(dest_key);
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

	return 0;
}
