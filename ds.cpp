#include "ds.h"

ds::ds()
{
	data_LinkList = new LinkList;
	sixtydata_List = new sixtyList;
	graph = new AMGraph;
	intro_file = new fileIO("./data/A股公司简介.xlsx");
	mes_file = new fileIO("./data/60支股票信息.xlsx", 1);
	graph_file = new fileIO("./data/60支股票信息.xlsx", 0);

	initds(data_LinkList, sixtydata_List, graph, intro_file, mes_file, graph_file);

	search_obj = new hashSearch(data_LinkList);
	bsTree = new BSTree(data_LinkList);
}

void ds::initds(LinkList*& data_LinkList, sixtyList*& sixtydata_List, AMGraph*& graph,
	fileIO*& intro_file, fileIO*& mes_file, fileIO*& graph_file)
{
	for (int i = 1; i <= 200; i++)
	{
		stock tempStock;

		intro_file->readline(i);
		tempStock.initStock(intro_file->get_cont_str());//初始化简介数据

		string tradeLog_path;
		tradeLog_path += "./data/股票交易日志/" + tempStock.getCode() + ".txt";
		fileIO* log_file;
		log_file = new fileIO(tradeLog_path);
		tempStock.initTradeLog();
		log_file->readtxt(tempStock);//初始化交易日志
		delete log_file;

		data_LinkList->add_data(tempStock);//放入数据链表
	}
	for (int i = 1; i <= 60; i++)
	{
		mes_file->readline(i);
		sixtydata_List->creatESList(data_LinkList, mes_file->get_cont_str());
	}
	graph->creatUDNv(sixtydata_List);
	for (int i = 1; i <= 83; i++)
	{
		graph_file->readline(i);
		graph->creatUDNa(graph_file->get_cont_str());
	}
}


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

hashSearch::hashSearch(LinkList*& intro)
{
	int hashtemp;
	LNode* introPtr = intro->get_head_ptr()->next;
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
void hashSearch::hash_search(string key, QTextEdit*& show)
{
	ostringstream oss;
	oss << "输入的股票代码是：" << key << endl;
	bool find = false;
	int hash_cur = get_hash(key);
	if (hashTable[hash_cur] == NULL)
		find = false;
	else if (hashTable[hash_cur]->key_code == key)
	{
		find = true;
		oss << hashTable[hash_cur]->info_stock.stockName << ' ';
		oss << hashTable[hash_cur]->info_stock.stockCode << ' ';
		oss << hashTable[hash_cur]->info_stock.firstCatg << ' ';
		oss << hashTable[hash_cur]->info_stock.secondCatg << ' ';
		oss << hashTable[hash_cur]->info_stock.bussiness << ' ';
		oss << suc_ASL << endl;
	}
	else
	{
		hashNode* t = hashTable[hash_cur];
		while (t)
		{
			t = t->next;
			if (t && t->key_code == key)
			{
				find = true;
				oss << t->info_stock.stockName << ' ';
				oss << t->info_stock.stockCode << ' ';
				oss << t->info_stock.firstCatg << ' ';
				oss << t->info_stock.secondCatg << ' ';
				oss << t->info_stock.bussiness << ' ';
				oss << suc_ASL << endl;
			}
		}
	}
	if (!find)
		oss << "fail!" << endl;
	show->append(QString::fromLocal8Bit(oss.str().c_str()));
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
void LinkList::KMP_search(string key, QTextEdit*& show)
{
	ostringstream oss;
	oss << "输入的网址字符串的子串是：" << key << endl;
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
			oss << p->key_stock.stockName << ' ' << p->key_stock.stockCode << endl;
			find = true;
		}
		p = p->next;
	}
	if (!find)
		oss << "fail!" << endl;
	show->append(QString::fromLocal8Bit(oss.str().c_str()));
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
BSTree::BSTree(LinkList*& data)
{
	bsTree = NULL;
	LNode* p = data->get_head_ptr()->next;
	while (p)
	{
		insertBST(bsTree, p->key_stock);
		p = p->next;
	}
}
void BSTree::BSsearch(string key,QTextEdit*& show)
{
	ostringstream oss;
	oss << "输入的股票代码是：" << key << endl;
	BSNode* result = searchBST(bsTree, key);
	if (result == NULL)
		oss << "fail!" << endl;
	else
	{
		oss << setw(20) << setiosflags(ios::right) << result->info_stock.getLog_ptr()->next->openPrice << ' ';
		oss << setw(20) << setiosflags(ios::right) << result->info_stock.getLog_ptr()->next->closePrice << ' ';
		oss << setw(20) << setiosflags(ios::right) << result->info_stock.getLog_ptr()->next->quotePerChange << '%';
		oss << endl;
	}
	show->append(QString::fromLocal8Bit(oss.str().c_str()));
}
void BSTree::deleteBST(string key_code,QTextEdit*& show)
{
	ostringstream oss;
	oss << "输入的股票代码是：" << key_code << endl;
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
		oss << "没有该股票信息！" << endl;
		show->append(QString::fromLocal8Bit(oss.str().c_str()));
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
		oss << p->key_code << ' ';
		oss << p->lchild->key_code << ' ' << p->rchild->key_code << endl;
		show->append(QString::fromLocal8Bit(oss.str().c_str()));
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
		oss << p->key_code << ' ';
		if (p->lchild)
			oss << p->lchild->key_code << ' ';
		else oss << "新节点左子树为空！" << ' ';
		if (p->rchild)
			oss << p->rchild->key_code << endl;
		else oss << "新节点右子树为空！" << endl;
	}
	else
		oss << "该节点为叶子节点" << endl;
	show->append(QString::fromLocal8Bit(oss.str().c_str()));
}

void LinkList::search_price_by_date(string date,QTextEdit*& show)
{
	ostringstream oss;
	oss << "输入的日期是：" << date << endl;
	LNode* p = head->next;
	while (p)
	{
		bool find = false;
		priceList t = p->key_stock.getLog_ptr()->next;
		oss << p->key_stock.stockCode << ' ' << p->key_stock.stockName << ' ';
		while (t)
		{
			if (t->tradeDate == date)
			{
				find = true;
				oss << setw(20) << setiosflags(ios::right) << t->openPrice << ' ';
				oss << setw(20) << setiosflags(ios::right) << t->closePrice << ' ';
				oss << setw(20) << setiosflags(ios::right) << t->quotePerChange << '%';
				oss << endl;
			}
			t = t->next;
		}
		if (!find)
			oss << "没有当日信息!" << endl;
		p = p->next;
	}
	show->append(QString::fromLocal8Bit(oss.str().c_str()));
}

void LinkList::creatPricelist(string date, QTextEdit*& show)
{
	ostringstream oss;
	oss << "输入的日期是：" << date << endl;
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
		else
			oss << p->key_stock.getCode() << ' ' << p->key_stock.getName() << ' ' << "无当日数据！" << endl;
		p = p->next;
	}
	show->append(QString::fromLocal8Bit(oss.str().c_str()));
}
void LinkList::insertSort(int sortmode, QTextEdit*& show)
{
	ostringstream oss;
	oss << "当前排序模式为：" << sortmode << endl;
	if (price_sort->next == NULL)return;
	priceList unnext;
	priceList unsorted = price_sort->next->next;
	price_sort->next->next = NULL;
	while (unsorted)
	{
		unnext = unsorted->next;
		priceList sorted = price_sort;
		if (sortmode == 0)
		{
			while (sorted->next && sorted->next->openPrice > unsorted->openPrice)
				sorted = sorted->next;
		}
		else if (sortmode == 1)
		{
			while (sorted->next && sorted->next->closePrice > unsorted->closePrice)
				sorted = sorted->next;
		}
		else if (sortmode == 2)
		{
			while (sorted->next && sorted->next->quotePerChange > unsorted->quotePerChange)
				sorted = sorted->next;
		}
		unsorted->next = sorted->next;
		sorted->next = unsorted;
		unsorted = unnext;
	}
	priceList p = price_sort->next;
	fileIO* writef = new fileIO("./data/价格和涨跌幅排序结果.xlsx", "write", sortmode);
	string title("股票代码 股票名称 开盘价 收盘价 涨跌幅 " + p->tradeDate);
	writef->write(title, 6, 0);
	while (p)
	{
		oss << p->code << ' ' << p->name << ' ';
		oss << setw(20) << setiosflags(ios::right) << p->openPrice << ' ';
		oss << setw(20) << setiosflags(ios::right) << p->closePrice << ' ';
		oss << setw(20) << setiosflags(ios::right) << p->quotePerChange << '%' << endl;
		p = p->next; 
	}
	writef->write(oss.str(), 5);
	delete writef;
	show->append(QString::fromLocal8Bit(oss.str().c_str()));
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
void sixtyList::creatQSList(LinkList*& data, string inputs, string catg)
{
	LNode* p = data->get_head_ptr()->next;
	istringstream ss(inputs);
	string temp, code;
	double score;
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
void sixtyList::showQS(QTextEdit*& show)
{
	ostringstream oss;
	if (length == 0)
		oss << "无该行业数据！" << endl;
	for (int i = 0; i < length; i++)
	{
		oss << setw(4) << i + 1 << ' ' << QStable[i].code << ' ' << QStable[i].name << ' ';
		oss << setw(8) << QStable[i].rate << "% " << QStable[i].date << endl;
	}
	show->append(QString::fromLocal8Bit(oss.str().c_str()));
}

void sixtyList::creatESList(LinkList*& data, string inputs)
{
	sixtyNode* work_ptr = EShead;
	while (work_ptr->next)
	{
		work_ptr = work_ptr->next;
	}
	LNode* p = data->get_head_ptr()->next;
	istringstream ss(inputs);
	string temp, code;
	int index;
	double score;
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
void sixtyList::easySort(string sortmode, QTextEdit*& show)
{
	sixtyNode* unsorted = EShead;
	sixtyNode* sorted = new sixtyNode;
	sorted->next = NULL;
	while (unsorted->next)
	{
		sixtyNode* tempun = unsorted->next;
		double max_score = -1;
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
	showES(sortmode, show);
}
void sixtyList::showES(string sortmod, QTextEdit*& show)
{
	ostringstream oss;
	sixtyNode* p = EShead->next;
	int pos = 1;
	fileIO* writef;
	if (sortmod == "score")
		writef = new fileIO("./data/评分排序.xlsx", "write", 0);
	else if(sortmod == "close")
		writef = new fileIO("./data/收盘价排序.xlsx", "write", 0);
	string title("序号 股票名称 股票代码 评分 收盘价");
	writef->write(title, 5, 0);
	while (p)
	{
		oss << pos << ' ' << p->code << ' ' << p->name << ' ' << setw(15) << p->score << ' ';
		oss << setw(15) << p->close << endl;
		pos++;
		p = p->next;
	}
	writef->write(oss.str(), 5, 1);
	delete writef;
	show->append(QString::fromLocal8Bit(oss.str().c_str()));
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
void AMGraph::creatUDNv(sixtyList*& lst)
{
	sixtyNode* p = lst->EShead->next;
	while (p)
	{
		vexs[vexnum].index = p->index;
		vexs[vexnum].name = p->name;
		vexs[vexnum].code = p->code;
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
void AMGraph::getMinLen(string index1, string index2, QTextEdit*& show)
{
	ostringstream oss;
	oss << "输入的节点为：" << index1 << ' ' << index2 << endl;
	string min_len, rst;
	floyd();
	int pos1 = 61, pos2 = 61;
	istringstream ss1(index1), ss2(index2);
	if (!(ss1 >> pos1 && ss2 >> pos2))
	{
		for (int i = 0; i < 60; i++)
		{
			if (vexs[i].name == index1 || vexs[i].code == index1)
				pos1 = i + 1;
			else if (vexs[i].name == index2 || vexs[i].code == index2)
				pos2 = i + 1;
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
	//if (rst != "无路径")
	//	reverse(rst.begin(), rst.end());
	oss << min_len << ": " << rst << endl;
	show->append(QString::fromLocal8Bit(oss.str().c_str()));
}

void AMGraph::prime(sixtyList*& lst,QTextEdit*& show, int pos)
{
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
	if (pos != -1 && pos > 0 && pos < 61)posnow = --pos;
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
		posnext = temp;
		tedges[i - 1].w = minw;
		tedges[i - 1].pos1 = closedge[posnext].adjvex + 1;
		tedges[i - 1].pos2 = posnext + 1;
		tedges[i - 1].name1 = lst->getNameByIndex(tedges[i - 1].pos1);
		tedges[i - 1].name2 = lst->getNameByIndex(tedges[i - 1].pos2);
		tedges[i - 1].totalscore = 0;
		bool find1 = false, find2 = false;
		sixtyNode* p = lst->EShead->next;
		while (p)
		{
			if (p->index == (tedges[i - 1].pos1))
			{
				tedges[i - 1].totalscore += p->score;
				find1 = true;
			}
			if (p->index == (tedges[i - 1].pos2))
			{
				tedges[i - 1].totalscore += p->score;
				find1 = true;
			}
			if (find1 && find2)break;
			p = p->next;
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
	for (int i = 0; i < 58; i++)
	{
		int t = i;
		int temp1, temp2, temp3;
		string temp4, temp5;
		int temp6;
		for (int j = i + 1; j < 59; j++)
		{
			if (tedges[j].w < tedges[t].w)
				t = j;
		}
		if (t != i)
		{
			temp1 = tedges[i].w;
			temp2 = tedges[i].pos1;
			temp3 = tedges[i].pos2;
			temp4 = tedges[i].name1;
			temp5 = tedges[i].name2;
			temp6 = tedges[i].totalscore;
			tedges[i].w = tedges[t].w;
			tedges[i].pos1 = tedges[t].pos1;
			tedges[i].pos2 = tedges[t].pos2;
			tedges[i].name1 = tedges[t].name1;
			tedges[i].name2 = tedges[t].name2;
			tedges[i].totalscore = tedges[t].totalscore;
			tedges[t].w = temp1;
			tedges[t].pos1 = temp2;
			tedges[t].pos2 = temp3;
			tedges[t].name1 = temp4;
			tedges[t].name2 = temp5;
			tedges[t].totalscore = temp6;
		}
	}
	for (int i = 0; i < 59; i++)
	{
		int t = i;
		int temp1, temp2, temp3;
		string temp4, temp5;
		int temp6;
		for (int j = i + 1; j < 60; j++)
		{
			if (tedges[j].w == tedges[t].w &&
				tedges[j].totalscore > tedges[t].totalscore)
				t = j;
		}
		if (t != i)
		{
			temp1 = tedges[i].w;
			temp2 = tedges[i].pos1;
			temp3 = tedges[i].pos2;
			temp4 = tedges[i].name1;
			temp5 = tedges[i].name2;
			temp6 = tedges[i].totalscore;
			tedges[i].w = tedges[t].w;
			tedges[i].pos1 = tedges[t].pos1;
			tedges[i].pos2 = tedges[t].pos2;
			tedges[i].name1 = tedges[t].name1;
			tedges[i].name2 = tedges[t].name2;
			tedges[i].totalscore = tedges[t].totalscore;
			tedges[t].w = temp1;
			tedges[t].pos1 = temp2;
			tedges[t].pos2 = temp3;
			tedges[t].name1 = temp4;
			tedges[t].name2 = temp5;
			tedges[t].totalscore = temp6;
		}
	}
	ostringstream oss;
	for (int i = 0; i < 6; i++)
	{
		oss << setw(8) << tedges[i].w << ' ' << tedges[i].pos1 << ": " << tedges[i].name1 << ' ';
		oss << setw(8) << tedges[i].pos2 << ": " << tedges[i].name2 << ' ' << tedges[i].totalscore << endl;
	}
	show->append(QString::fromLocal8Bit(oss.str().c_str()));
}

void AMGraph::kruskal(sixtyList*& lst,QTextEdit*& show)
{
	floyd();
	for (int i = 0; i < vexnum; i++)
	{
		for (int j = 0; j < vexnum; j++)
		{
			bool find1 = false, find2 = false;
			int pos = 60 * i + j;
			edge[pos].head = i;
			edge[pos].tail = j;
			edge[pos].lowcost = d[i][j];
			edge[pos].totalscore = 0;
			sixtyNode* p = lst->EShead->next;
			while (p)
			{
				if (p->index == (j + 1))
				{
					edge[pos].totalscore += p->score;
					find1 = true;
				}
				if (p->index == (i + 1))
				{
					edge[pos].totalscore += p->score;
					find1 = true;
				}
				if (find1 && find2)break;
				p = p->next;
			}
		}
		vexset[i] = i;
	}
	for (int i = 0; i < 3599; i++)
	{
		int t = i;
		int temp1, temp2, temp3, temp4;
		for (int j = i + 1; j < 3600; j++)
		{
			if (edge[j].lowcost < edge[t].lowcost)
				t = j;
		}
		if (t != i)
		{
			temp1 = edge[i].head;
			temp2 = edge[i].tail;
			temp3 = edge[i].lowcost;
			temp4 = edge[i].totalscore;
			edge[i].head = edge[t].head;
			edge[i].tail = edge[t].tail;
			edge[i].lowcost = edge[t].lowcost;
			edge[i].totalscore = edge[t].totalscore;
			edge[t].head = temp1;
			edge[t].tail = temp2;
			edge[t].lowcost = temp3;
			edge[t].totalscore = temp4;
		}
	}
	for (int i = 0; i < 3599; i++)
	{
		int t = i;
		int temp1, temp2, temp3, temp4;
		for (int j = i + 1; j < 3600; j++)
		{
			if (edge[j].lowcost == edge[t].lowcost &&
				edge[j].totalscore > edge[t].totalscore)
				t = j;
		}
		if (t != i)
		{
			temp1 = edge[i].head;
			temp2 = edge[i].tail;
			temp3 = edge[i].lowcost;
			temp4 = edge[i].totalscore;
			edge[i].head = edge[t].head;
			edge[i].tail = edge[t].tail;
			edge[i].lowcost = edge[t].lowcost;
			edge[i].totalscore = edge[t].totalscore;
			edge[t].head = temp1;
			edge[t].tail = temp2;
			edge[t].lowcost = temp3;
			edge[t].totalscore = temp4;
		}
	}
	int count = 0;
	ostringstream oss;
	for (int i = 0; i < 3600; i++)
	{
		if (vexset[edge[i].head] != vexset[edge[i].tail])
		{
			if (count++ < 6)
			{
				oss << setw(8) << edge[i].lowcost << ' ';
				oss << setw(8) << edge[i].head + 1 << ": " << lst->getNameByIndex(edge[i].head + 1) << ' ';
				oss << setw(8) << edge[i].tail + 1 << ": " << lst->getNameByIndex(edge[i].tail + 1) << ' ';
				oss << setw(8) << edge[i].totalscore << endl;
			}
			for (int j = 0; j < 60; j++)
			{
				if (vexset[j] == vexset[edge[i].tail])
					vexset[j] = vexset[edge[i].head];
			}
		}
	}
	show->append(QString::fromLocal8Bit(oss.str().c_str()));
}

void AMGraph::bip(sixtyList*& lst, int* inputs,QTextEdit*& show)
{
	ostringstream oss;
	int points_ind[10];
	int sides[10][10];
	int color[10];
	int stack[10], top = 0;
	bool isBip = true;
	for (int i = 0; i < 10; i++)
	{
		points_ind[i] = inputs[i];
		points_ind[i]--;
		color[i] = -1;
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			sides[i][j] = arcs[points_ind[i]][points_ind[j]];
		}
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			oss << setw(8) << sides[i][j];
		oss << endl;
	}
	color[0] = 1;
	stack[top++] = points_ind[0];
	while (top > 0)
	{
		int top_p = stack[--top];
		for (int i = 0; i < 10; i++)
		{
			if (sides[top_p][i] < 32767 && color[i] == -1)
			{
				color[i] = ~color[top_p];
				stack[top++] = i;
			}
			else if (sides[top_p][i] < 32767 && color[top_p] == color[i])
				isBip = false;
		}
	}
	if (isBip)
	{
		for (int i = 0; i < 10; i++)
		{
			oss << setw(4) << points_ind[i] + 1 << ' ';
			oss << lst->getNameByIndex(points_ind[i] + 1) << endl;
		}
	}
	else
		oss << "不能构成二部图！" << endl;
	show->append(QString::fromLocal8Bit(oss.str().c_str()));
}
