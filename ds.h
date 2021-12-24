#pragma once

#include <iostream>
#include <sstream>

#include "stock.h"

using namespace std;

class LNode
{
public:
	stock key_stock;
	LNode* next;
};
class LinkList
{
public:
	LinkList();
	~LinkList();
	void add_data(stock);

	void KMP_search(string);
	void get_next_val(string);

	void search_price_by_date(string);

	void creatPricelist(string);
	void insertSort(string);

	LNode* get_head_ptr() { return head; }
private:
	LNode* head;
	priceNode* price_sort;
	int length;
	int kmp_next[40];
};

class hashNode
{
public:
	string key_code;
	stock info_stock;
	hashNode* next;
};
class hashSearch
{
public:
	hashSearch(LinkList&);
	int get_hash(string);
	void hash_search(string);
private:
	hashNode* hashTable[97];
	double factor = 200.0 / 97;//wrong
	double suc_ASL = 1 + factor / 2;
	double fail_ASL = factor + exp(-factor);
};

class BSNode
{
public:
	string key_code;
	stock info_stock;
	BSNode* lchild, * rchild;
};
class BSTree
{
public:
	BSTree(LinkList&);
	void BSsearch(string);
private:
	BSNode* bsTree;
	//ASL
};

class sixtyNode
{
public:
	string name;
	string code;
	int score;
	string date;
	double rate;
	double close;
	sixtyNode* next;
};
class sixtyList
{
public:
	sixtyList();
	~sixtyList();
	void creatQSList(LinkList&, string, string);
	void creatESList(LinkList&, string);

	void quickSort();
	void QSort(int, int);
	int partition(int, int);
	void showQS();

	void easySort(string);
	void showES();
private:
	sixtyNode* QStable;
	int length;
	sixtyNode* EShead;
};
