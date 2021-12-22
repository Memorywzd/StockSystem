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
	//LNode* temp = intro_LinkList.get_head_ptr()->next;
	/*while (temp)
	{
		cout << temp->key_stock.getCode()<<' ' << temp->key_stock.getName() << endl;
		temp = temp->next;
	}*/
}

int main()
{
	
	LinkList intro_LinkList;
	fileIO intro_file("./data/A¹É¹«Ë¾¼ò½é.xlsx");
	initsys(intro_LinkList, intro_file);
	hashSearch search_obj(intro_LinkList);
	string dest_key;
	while (cin >> dest_key && dest_key != "0")
	{
		if (!search_obj.hash_search(dest_key))cout << "fail!" << endl;
	}
	return 0;
}