#pragma once

#include <iostream>

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
	void add_data(stock&);
	LNode* get_head_ptr() { return head; }
private:
	LNode* head;
	int length;
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
	bool hash_search(string);
private:
	hashNode* hashTable[97];
	double factor = 200.0 / 97;
	double suc_ASL = 1 + factor / 2;
	double fail_ASL = factor + exp(0 - factor);
};