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
		tempStock.initStock(intro_file.get_cont_str());//��ʼ����������

		string tradeLog_path;
		tradeLog_path += "./data/��Ʊ������־/" + tempStock.getCode() + ".txt";
		fileIO log_file(tradeLog_path);
		tempStock.initTradeLog();
		log_file.readtxt(tempStock);//��ʼ��������־

		data_LinkList.add_data(tempStock);//������������
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
	fileIO intro_file("./data/A�ɹ�˾���.xlsx");
	initsys(data_LinkList, intro_file);
	hashSearch search_obj(data_LinkList);
	BSTree bsTree();
	string dest_key;
	/*cout << "��ϣ���ң������Ʊ���룬0��������" << endl;
	while (cin >> dest_key && dest_key != "0")
	{
		if (!search_obj.hash_search(dest_key))cout << "fail!" << endl;
	}*/
	/*cout << "KMPƥ�䣺�����Ʊ��ַ��0��������" << endl;
	while (cin >> dest_key && dest_key != "0")
	{
		data_LinkList.KMP_search(dest_key);
	}*/
	cout << "�������������ң������Ʊ���룬0��������" << endl;
	while (cin >> dest_key && dest_key != "0")
	{

	}
	
	return 0;
}