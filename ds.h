#pragma once

#include <iostream>
#include <sstream>
#include <QTextEdit>


#include <iomanip>

#include "stock.h"
#include "fileIO.h"

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

	void KMP_search(string, QTextEdit*&);
	void get_next_val(string);

	void search_price_by_date(string, QTextEdit*&);

	void creatPricelist(string, QTextEdit*&);
	void insertSort(int, QTextEdit*&);

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
	hashSearch(LinkList*&);
	int get_hash(string);
	void hash_search(string, QTextEdit*&);
	void getASL();
private:
	hashNode* hashTable[97];
	double suc_ASL;
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
	BSTree(LinkList*&);
	void BSsearch(string, QTextEdit*&);
	void deleteBST(string, QTextEdit*&);
	void insertBST(BSNode*&, stock);
private:
	BSNode* bsTree;
	int snum;
	double suc_ASL;
};

class sixtyNode
{
public:
	int index;
	string name;
	string code;
	double score;
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
	void creatQSList(LinkList*&, string, string);
	void creatESList(LinkList*&, string);

	void quickSort();
	void QSort(int, int);
	int partition(int, int);
	void showQS(QTextEdit*&);

	void easySort(string, QTextEdit*&);
	void showES(string, QTextEdit*&);

	string getNameByIndex(int);
private:
	sixtyNode* QStable;
	int length;
	sixtyNode* EShead;
	friend class AMGraph;
};

class AMGraph
{
public:
	AMGraph();
	void creatUDNv(sixtyList*&);
	void creatUDNa(string);

	void floyd();
	void getMinLen(string, string, QTextEdit*&);
	void prime(sixtyList*&, QTextEdit*&, int pos = -1);
	void kruskal(sixtyList*&, QTextEdit*&);
	void bip(sixtyList*&, int*, QTextEdit*&);
private:
	sixtyNode vexs[60];
	int arcs[60][60];
	int vexnum, arcnum;
	int d[60][60];
	int path[60][60];
	struct closedge
	{
		int adjvex;
		int lowcost;
	}closedge[60];
	struct tedge
	{
		int w;
		int pos1;
		int pos2;
		string name1;
		string name2;
		double totalscore;
	}tedges[59];
	struct kedge
	{
		int head;
		int tail;
		int lowcost;
		double totalscore;
	}edge[3600];
	int vexset[60];
};

class ds
{
public:
	ds();
	LinkList* data_LinkList;
	sixtyList* sixtydata_List;
	AMGraph* graph;

	fileIO* intro_file;
	fileIO* mes_file;
	fileIO* graph_file;

	hashSearch* search_obj;
	BSTree* bsTree;

private:
	void initds(LinkList*&, sixtyList*&, AMGraph*&,
				fileIO*&, fileIO*&, fileIO*&);
};
