#include "ds.h"

LinkList::LinkList()
{
	head = new LNode;
	head->next = NULL;
	length = 0;
}
LinkList::~LinkList()
{
	LNode* p;
	while (head)
	{
		p = head;
		head = head->next;
		delete p;
	}
	head = NULL;
}
void LinkList::add_data(stock& s)
{
	LNode* tail = this->head;
	while (tail->next)
	{
		tail = tail->next;
	}
	LNode* p = new LNode;
	p->key_stock = s;
	p->next = NULL;
	tail->next = p;
	tail = p;
	length++;
}

hashSearch::hashSearch(LinkList& intro)
{
	int hashtemp;
	LNode* introPtr = intro.get_head_ptr()->next;
	for (int i = 0; i < 97; i++)
	{
		hashTable[i] = NULL;
	}
	while (introPtr)
	{
		hashtemp = get_hash(introPtr->key_stock.stockCode);
		hashNode* p = new hashNode;
		p->key_code = introPtr->key_stock.stockCode;
		p->info_stock = introPtr->key_stock;
		p->next = NULL;
		hashNode* t = hashTable[hashtemp];
		if (t == NULL)
			hashTable[hashtemp] = p;
		else
		{
			while (t->next)
			{
				t = t->next;
			}
			t->next = p;
		}
		introPtr = introPtr->next;
	}
}
int hashSearch::get_hash(string key_code)
{
	int hashValue = 0;
	int ascii_sum = 0;
	for (unsigned int i = 0; i < key_code.length(); i++)
	{
		ascii_sum += key_code[i];
	}
	hashValue = ascii_sum % 97;
	return hashValue;//ÅÐ¶ÏÊÇ·ñ0-97
}
bool hashSearch::hash_search(string key)
{
	int hash_cur = get_hash(key);
 	if (hashTable[hash_cur] == NULL)
		return false;
	else if (hashTable[hash_cur]->key_code == key)
	{
		cout << hashTable[hash_cur]->info_stock.stockName << ' ';
		cout << hashTable[hash_cur]->info_stock.stockCode << ' ';
		cout << hashTable[hash_cur]->info_stock.firstCatg << ' ';
		cout << hashTable[hash_cur]->info_stock.secondCatg << ' ';
		cout << hashTable[hash_cur]->info_stock.bussiness << ' ';
		cout << suc_ASL << endl;
		return true;
	}
	else
	{
		hashNode* t = hashTable[hash_cur];
		while (t)
		{
			t = t->next;
			if (t&&t->key_code == key)
			{
				cout << t->info_stock.stockName << ' ';
				cout << t->info_stock.stockCode << ' ';
				cout << t->info_stock.firstCatg << ' ';
				cout << t->info_stock.secondCatg << ' ';
				cout << t->info_stock.bussiness << ' ';
				cout << suc_ASL << endl;
				return true;
			}
		}
		return false;
	}

}

void LinkList::get_next_val(string key)
{
	int i = 0, j = -1;
	kmp_next[0] = -1;
	int keylen = key.length();
	while (i < keylen - 1)
	{
		if (j == -1 || key[i] == key[j])
		{
			i++;
			j++;
			if (key[i] != key[j])
				kmp_next[i] = j;
			else kmp_next[i] = kmp_next[j];
		}
		else j = kmp_next[j];
	}
}
void LinkList::KMP_search(string key)
{
	LNode* p = head->next;
	this->get_next_val(key);
	int ketlen = key.length();
	int websitelen = p->key_stock.website.length();
	while (p)
	{
		int i = 0, j = 0;
		while (i < websitelen && j < ketlen)
		{
			if (j == -1 || p->key_stock.website[i]==key[j])
			{
				i++;
				j++;
			}
			else j = kmp_next[j];
		}
		if (j > ketlen)
		{
			cout << p->key_stock.stockName << ' ' << p->key_stock.stockCode << endl;
			break;
		}
		p = p->next;
	}
}
