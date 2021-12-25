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
void BSTree::deleteBST(string key_code)
{
	BSNode* p = bsTree, * f = NULL;
	while (p)
	{
		if (p->key_code == key_code)
			break;
		f = p;
		if (p->key_code > key_code)
			p = p->lchild;
		else p = p->rchild;
	}
	if (!p)
	{
		cout << "没有该股票信息！" << endl;
		return;
	}
	BSNode* q = p;
	BSNode* s;
	if (p->lchild && p->rchild)
	{
		s = p->lchild;
		while (s->rchild)
		{
			q = s;
			s = s->rchild;
		}
		p->key_code = s->key_code;
		if (q != p)
			q->rchild = s->lchild;
		else q->lchild = s->lchild;
		delete s;
		cout << p->key_code << ' ';
		cout << p->lchild->key_code << ' ' << p->rchild->key_code << endl;
		return;
	}
	else if (!p->rchild)
		p = p->lchild;
	else if (!p->lchild)
		p = p->rchild;
	if (!f)
		bsTree = p;
	else if (q == f->lchild)
		f->lchild = p;
	else f->rchild = p;
	delete q;
	if (p)
	{
		cout << p->key_code << ' ';
		if (p->lchild)
			cout << p->lchild->key_code << ' ';
		else cout << "新节点左子树为空！" << ' ';
		if (p->rchild) 
			cout << p->rchild->key_code << endl;
		else cout << "新节点右子树为空！" << endl;
	}
	else cout << "该节点为叶子节点" << endl;
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

sixtyList::sixtyList()
{
	QStable = new sixtyNode[60];
	length = 0;
	EShead = new sixtyNode;
	EShead->next = NULL;
}
sixtyList::~sixtyList()
{
	delete[]QStable;
	length = 0;
	sixtyNode* p = EShead;
	while (p)
	{
		sixtyNode* t;
		t = p;
		p = p->next;
		delete t;
	}
}
void sixtyList::creatQSList(LinkList& data, string inputs, string catg)
{
	LNode* p = data.get_head_ptr()->next;
	istringstream ss(inputs);
	string temp, code;
	int score;
	ss >> temp >> temp >> code >> score;
	while (p)
	{
		if (p->key_stock.getCode() == code && p->key_stock.getCatg() == catg)
		{
			priceList pt = p->key_stock.getLog_ptr()->next;
			double max_rate = -10000.0;
			string max_date;
			while (pt)
			{
				if (pt->quotePerChange > max_rate)
				{
					max_rate = pt->quotePerChange;
					max_date = pt->tradeDate;
				}
				pt = pt->next;
			}
			QStable[length].name = p->key_stock.getName();
			QStable[length].code = code;
			QStable[length].score = score;
			QStable[length].date = max_date;
			QStable[length].rate = max_rate;
			QStable[length].next = NULL;
			length++;
			break;
		}
		p = p->next;
	}
}
void sixtyList::quickSort()
{
	QSort(0, length - 1);
}
void sixtyList::QSort(int low, int high)
{
	if (low < high)
	{
		int pivotloc = partition(low, high);
		QSort(low, pivotloc - 1);
		QSort(pivotloc + 1, high);
	}
}
int sixtyList::partition(int low, int high)
{
	sixtyNode t = QStable[low];
	double pivotkey = QStable[low].rate;
	while (low < high)
	{
		while (low < high && QStable[high].rate <= pivotkey)
			high--;
		QStable[low] = QStable[high];
		while (low < high && QStable[low].rate >= pivotkey)
			low++;
		QStable[high] = QStable[low];
	}
	QStable[low] = t;
	return low;
}
void sixtyList::showQS()
{
	if (length == 0)
		cout << "无该行业数据！" << endl;
	for (int i = 0; i < length; i++)
	{
		cout << i << ' ' << QStable[i].code << ' ' << QStable[i].name << ' ';
		cout << QStable[i].rate << ' ' << QStable[i].date << endl;
	}
}

void sixtyList::creatESList(LinkList& data, string inputs)
{
	sixtyNode* work_ptr = EShead;
	while (work_ptr->next)
	{
		work_ptr = work_ptr->next;
	}
	LNode* p = data.get_head_ptr()->next;
	istringstream ss(inputs);
	string temp, code;
	int index,score;
	ss >> index >> temp >> code >> score;
	while (p)
	{
		if (p->key_stock.getCode() == code)
		{
			priceList pt = p->key_stock.getLog_ptr()->next;
			sixtyNode* t = new sixtyNode;
			t->index = index;
			t->name = p->key_stock.getName();
			t->code = p->key_stock.getCode();
			t->score = score;
			t->close = pt->closePrice;
			t->next = NULL;
			work_ptr->next = t;
			break;
		}
		p = p->next;
	}
}
void sixtyList::easySort(string sortmode)
{
	sixtyNode* unsorted = EShead;
	sixtyNode* sorted = new sixtyNode;
	while (unsorted->next)
	{
		sixtyNode* tempun = unsorted->next;
		int max_score = -1;
		double max_close = -1;
		while (tempun)
		{
			if (sortmode == "score" && tempun->score > max_score)
				max_score = tempun->score;
			else if (sortmode == "close" && tempun->close > max_close)
				max_close = tempun->close;
			tempun = tempun->next;
		}
		tempun = unsorted;
		//cout << max_score << endl;
		while (tempun->next)
		{
			if (tempun->next->score == max_score || tempun->next->close == max_close)
				break;
			else tempun = tempun->next;
		}
		sixtyNode* found = tempun->next;
		tempun->next = found->next;
		found->next = NULL;
		sixtyNode* temps = sorted;
		while (temps->next)
		{
			temps = temps->next;
		}
		temps->next = found;
	}
	EShead = sorted;
}
void sixtyList::showES()
{
	sixtyNode* p = EShead->next;
	int pos = 1;
	while (p)
	{
		cout << p->index << ' ' << p->code << ' ' << p->name << ' ' << p->score << ' ' << p->close << endl;
		pos++;
		p = p->next;
	}
}
string sixtyList::getNameByIndex(int index)
{
	sixtyNode* p = EShead->next;
	while (p)
	{
		if (p->index == index)
			return p->name;
		p = p->next;
	}
}

AMGraph::AMGraph()
{
	vexnum = 0;
	arcnum = 0;
	for (int i = 0; i < 60; i++)
	{
		for (int j = 0; j < 60; j++)
		{
			arcs[i][j] = 32767;
		}
	}
}
void AMGraph::creatUDNv(sixtyList &lst)
{
	sixtyNode* p = lst.EShead->next;
	while (p)
	{
		vexs[vexnum].index = p->index;
		vexs[vexnum].name = p->name;
		vexnum++;
		p = p->next;
	}
}
void AMGraph::creatUDNa(string inputs)
{
	istringstream ss(inputs);
	int index1, index2, weight;
	ss >> index1 >> index2 >> weight;
	index1--;
	index2--;
	arcs[index1][index2] = weight;
	arcs[index2][index1] = weight;
	arcnum++;
}
void AMGraph::floyd()
{
	for (int i = 0; i < vexnum; i++)
	{
		for (int j = 0; j < vexnum; j++)
		{
			d[i][j] = arcs[i][j];
			if (d[i][j] < 32767 && i != j)
				path[i][j] = i;
			else path[i][j] = -1;
		}
	}
	for (int k = 0; k < vexnum; k++)
	{
		for (int i = 0; i < vexnum; i++)
		{
			for (int j = 0; j < vexnum; j++)
			{
				if (d[i][k] + d[k][j] < d[i][j])
				{
					d[i][j] = d[i][k] + d[k][j];
					path[i][j] = path[k][j];
				}
			}
		}
	}
}
void AMGraph::getMinLen(string index1, string index2, string& min_len, string& rst)
{
	floyd();
	int pos1 = 61, pos2 = 61;
	istringstream ss1(index1), ss2(index2);
	if (!(ss1 >> pos1 && ss2 >> pos2))
	{
		for (int i = 0; i < 60; i++)
		{
			if (vexs[i].name == index1 || vexs[i].code == index1)
				pos1 = i;
			else if (vexs[i].name == index2 || vexs[i].code == index2)
				pos2 = i;
		}
	}
	pos1--;
	pos2--;
	bool legpos = true;
	if (pos1 >= 0 && pos1 < 60)legpos = false;
	else if (pos2 >= 0 && pos2 < 60)legpos = false;
	if (legpos)
	{
		min_len += "输入的点不存在";
		rst += "无路径";
	}
	else if (pos1 == pos2)
	{
		min_len += "0";
		rst += to_string(pos1 + 1) + ' ' + to_string(pos1 + 1);
	}
	else if (d[pos1][pos2] == 32767)
	{
		min_len += "两点不连通";
		rst += "无路径";
	}
	else
	{
		min_len = to_string(d[pos1][pos2]);
		while (path[pos1][pos2] != pos1)
		{
			rst += to_string(pos2 + 1) + ' ';
			pos2 = path[pos1][pos2];
		}
		rst += to_string(pos2 + 1) + ' ';
		rst += to_string(pos1 + 1) + ' ';
	}
}

void AMGraph::prime(sixtyList& lst,int pos)
{
	lst.easySort("score");
	floyd();
	int initw = 32767, posnow;
	for (int i = 0; i < 60; i++)
	{
		for (int j = 0; j < 60; j++)
		{
			if (d[i][j] < initw)
			{
				initw = d[i][j];
				posnow = i;
			}
		}
	}
	if (pos != -1)posnow = --pos;
	for (int i = 0; i < vexnum; i++)
	{
		if (i != posnow)
		{
			closedge[i].adjvex = posnow;
			closedge[i].lowcost = d[posnow][i];
		}
	}
	closedge[posnow].lowcost = 0;
	int count = 0;
	int posnext;
	for (int i = 1; i < vexnum; i++)
	{
		int minw = 32767;
		int temp;
		for (int j = 0; j < vexnum; j++)
			if (j != posnow && closedge[j].lowcost != 0 && closedge[j].lowcost < minw)
			{
				minw = closedge[j].lowcost;
				temp = j;
			}
		for (int j = 0; j < vexnum; j++)
		{
			if (minw != d[posnow][temp])
			{
				posnext = temp;
				break;
			}
			sixtyNode* p = lst.EShead->next;
			bool find = false;
			while (p)
			{
				if (closedge[j].lowcost == minw && p->index == j)
				{
					posnext = j;
					find = true;
					break;
				}
				p = p->next;
			}
			if (find)break;
		}
		count++;
		if (count < 6)
		{
			cout << minw << ' ' << closedge[posnext].adjvex + 1 << ": " << lst.getNameByIndex(closedge[posnext].adjvex + 1) << ' ';
			cout << posnext + 1 << ": " << lst.getNameByIndex(posnext + 1) << endl;
		}
		closedge[posnext].lowcost = 0;
		for (int j = 0; j < vexnum; j++)
		{
			if (closedge[j].lowcost != 0 && d[posnext][j] < closedge[j].lowcost)
			{
				closedge[j].adjvex = posnext;
				closedge[j].lowcost = d[posnext][j];
			}
		}
		posnow = posnext;
	}
}
