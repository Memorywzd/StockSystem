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
void LinkList::add_data(stock s)
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
	return hashValue;//判断是否0-97
}
void hashSearch::hash_search(string key)
{
	bool find = false;
	int hash_cur = get_hash(key);
	if (hashTable[hash_cur] == NULL)
		find = false;
	else if (hashTable[hash_cur]->key_code == key)
	{
		find = true;
		cout << hashTable[hash_cur]->info_stock.stockName << ' ';
		cout << hashTable[hash_cur]->info_stock.stockCode << ' ';
		cout << hashTable[hash_cur]->info_stock.firstCatg << ' ';
		cout << hashTable[hash_cur]->info_stock.secondCatg << ' ';
		cout << hashTable[hash_cur]->info_stock.bussiness << ' ';
		cout << suc_ASL << endl;
	}
	else
	{
		hashNode* t = hashTable[hash_cur];
		while (t)
		{
			t = t->next;
			if (t&&t->key_code == key)
			{
				find = true;
				cout << t->info_stock.stockName << ' ';
				cout << t->info_stock.stockCode << ' ';
				cout << t->info_stock.firstCatg << ' ';
				cout << t->info_stock.secondCatg << ' ';
				cout << t->info_stock.bussiness << ' ';
				cout << suc_ASL << endl;
			}
		}
	}
	if (!find)
		cout << "fail!" << endl;
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
	int keylen = key.length();
	bool find = false;
	while (p)
	{
		int i = 0, j = 0;
		int websitelen = p->key_stock.website.length();
		while (i < websitelen && j < keylen)
		{
			if (j == -1 || p->key_stock.website[i] == key[j])
			{
				i++;
				j++;
			}
			else j = kmp_next[j];
		}
		if (j >= keylen)
		{
			cout << p->key_stock.stockName << ' ' << p->key_stock.stockCode << endl;
			find = true;
			//break;
		}
		p = p->next;
	}
	if (!find)cout << "fail!" << endl;
}

void insertBST(BSNode*& bst, stock s)
{
	if (!bst)
	{
		BSNode* t = new BSNode;
		t->key_code = s.getCode();
		t->info_stock = s;
		t->lchild = t->rchild = NULL;
		bst = t;
	}
	else if (s.getCode() < bst->key_code)
		insertBST(bst->lchild, s);
	else if (s.getCode() > bst->key_code)
		insertBST(bst->rchild, s);
	else cout << "insertBST: erro!" << endl;
}
BSNode* searchBST(BSNode* bst, string key)
{
	if ((!bst) || key == bst->key_code)
		return bst;
	else if (key < bst->key_code)
		return searchBST(bst->lchild, key);
	else return searchBST(bst->rchild, key);
}
BSTree::BSTree(LinkList& data)
{
	bsTree = NULL;
	LNode* p = data.get_head_ptr()->next;
	while (p)
	{
		insertBST(bsTree, p->key_stock);
		p = p->next;
	}
}
void BSTree::BSsearch(string key)
{
	BSNode* result = searchBST(bsTree, key);
	if (result == NULL)
		cout << "fail!" << endl;
	else
	{
		cout << result->info_stock.getLog_ptr()->next->openPrice << ' ';
		cout << result->info_stock.getLog_ptr()->next->closePrice << ' ';
		cout << result->info_stock.getLog_ptr()->next->quotePerChange << '%';
		cout << endl;
	}
}

void LinkList::search_price_by_date(string date)
{
	LNode* p = head->next;
	while (p)
	{
		bool find = false;
		priceList t = p->key_stock.getLog_ptr()->next;
		cout << p->key_stock.stockCode << ' ' << p->key_stock.stockName << ' ';
		while (t)
		{
			if (t->tradeDate == date)
			{
				find = true;
				cout << t->openPrice << ' ' << t->closePrice << ' ' << t->quotePerChange;
				cout << endl;
			}
			t = t->next;
		}
		if (!find)
			cout << "没有当日信息!" << endl;
		p = p->next;
	}
}

void LinkList::creatPricelist(string date)
{
	LNode* p = head->next;
	price_sort = new priceNode;
	price_sort->next = NULL;
	priceList t = price_sort;
	while (p)
	{
		priceNode* work_ptr = p->key_stock.tradeLog->next;
		while (work_ptr)
		{
			if (work_ptr->tradeDate == date)break;
			work_ptr = work_ptr->next;
		}
		if (work_ptr)
		{
			priceNode* temp = new priceNode;
			temp->code = p->key_stock.getCode();
			temp->name = p->key_stock.getName();
			temp->tradeDate = work_ptr->tradeDate;
			temp->openPrice = work_ptr->openPrice;
			temp->closePrice = work_ptr->closePrice;
			temp->quotePerChange = work_ptr->quotePerChange;
			temp->next = NULL;
			t->next = temp;
			t = t->next;
		}
		else cout << p->key_stock.getCode() << ' ' << p->key_stock.getName() << ' ' << "无当日数据！" << endl;
		p = p->next;
	}
}
void LinkList::insertSort(string sortmode)
{
	if (price_sort->next == NULL)return;
	priceList unnext;
	priceList unsorted = price_sort->next->next;
	price_sort->next->next = NULL;
	while (unsorted)
	{
		unnext = unsorted->next;
		priceList sorted = price_sort;
		if (sortmode == "open")
		{
			while (sorted->next && sorted->next->openPrice > unsorted->openPrice)
				sorted = sorted->next;
		}
		else if (sortmode == "close")
		{
			while (sorted->next && sorted->next->closePrice > unsorted->closePrice)
				sorted = sorted->next;
		}	
		else if (sortmode == "rate")
		{
			while (sorted->next && sorted->next->quotePerChange > unsorted->quotePerChange)
				sorted = sorted->next;
		}
		unsorted->next = sorted->next;
		sorted->next = unsorted;
		unsorted = unnext;
	}
	priceList p = price_sort->next;
	while (p)
	{
		cout << p->code << ' ' << p->name << ' ' << p->openPrice << ' ' << p->closePrice << ' ' << p->quotePerChange << endl;
		p = p->next;
	}
}
