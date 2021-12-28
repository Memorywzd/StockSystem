#include "qstocksys.h"

QStocksys::QStocksys(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.pushButton, &QPushButton::clicked, this, &QStocksys::open_query);
	connect(ui.pushButton_2, &QPushButton::clicked, this, &QStocksys::open_analysis);
}

void QStocksys::open_query()
{
	query* w1 = new query(dataset);
	w1->show();
}

void QStocksys::open_analysis()
{
	analysis* w2 = new analysis(dataset);
	w2->show();
}

query::query(ds& dataset, QWidget* parent)
	:QWidget(parent), set(dataset)
{
	qui.setupUi(this);

	connect(qui.pushButton, &QPushButton::clicked, this, &query::hash);
	connect(qui.pushButton_2, &QPushButton::clicked, this, &query::kmp);
	connect(qui.pushButton_3, &QPushButton::clicked, this, &query::bitree_q);
	connect(qui.pushButton_4, &QPushButton::clicked, this, &query::bitree_d);
	connect(qui.pushButton_5, &QPushButton::clicked, this, &query::linklist);
}

void query::hash()
{
	string code_hash = qui.lineEdit->text().toStdString();
	set.search_obj->hash_search(code_hash, qui.textEdit);
}
void query::kmp()
{
	string web_kmp = qui.lineEdit_2->text().toStdString();
	set.data_LinkList->KMP_search(web_kmp, qui.textEdit_2);
}
void query::bitree_q()
{
	string code_bitree = qui.lineEdit_3->text().toStdString();
	set.bsTree->BSsearch(code_bitree, qui.textEdit_3);

}
void query::bitree_d()
{
	string code_bitree = qui.lineEdit_3->text().toStdString();
	set.bsTree->deleteBST(code_bitree, qui.textEdit_3);
}
void query::linklist()
{
	string date_linklist = qui.lineEdit_4->text().toStdString();
	set.data_LinkList->search_price_by_date(date_linklist, qui.textEdit_4);
}

analysis::analysis(ds& dataset, QWidget* parent)
	: QWidget(parent), set(dataset)
{
	aui.setupUi(this);

	connect(aui.pushButton, &QPushButton::clicked, this, &analysis::isort);
	connect(aui.pushButton_2, &QPushButton::clicked, this, &analysis::qsort);
	connect(aui.pushButton_3, &QPushButton::clicked, this, &analysis::esort);
	connect(aui.pushButton_4, &QPushButton::clicked, this, &analysis::min_len);
	connect(aui.pushButton_5, &QPushButton::clicked, this, &analysis::prime_kruskal);
	connect(aui.pushButton_6, &QPushButton::clicked, this, &analysis::bip_graph);

}

void analysis::isort()
{
	string isort_date = aui.lineEdit->text().toStdString();
	set.data_LinkList->creatPricelist(isort_date, aui.textEdit);
	set.data_LinkList->insertSort(aui.dire_mode->currentIndex(), aui.textEdit);
}
void analysis::qsort()
{
	string qsort_catg = aui.lineEdit_2->text().toLocal8Bit();
	sixtyList* p = new sixtyList;
	for (int i = 1; i <= 60; i++)
	{
		set.mes_file->readline(i);
		p->creatQSList(set.data_LinkList, set.mes_file->get_cont_str(), qsort_catg);
	}
	p->quickSort();
	p->showQS(aui.textEdit_2);
	delete p;
}
void analysis::esort()
{
	if (aui.esort_mode->currentIndex() == 0)
		set.sixtydata_List->easySort("score", aui.textEdit_3);
	else if(aui.esort_mode->currentIndex() == 1)
		set.sixtydata_List->easySort("close", aui.textEdit_3);
}
void analysis::min_len()
{
	string ind1, ind2, index1, index2;
	ind1 = aui.lineEdit_3->text().toLocal8Bit();
	ind2 = aui.lineEdit_4->text().toLocal8Bit();
	int in1, in2;
	in1 = aui.floyd_comb_1->currentIndex() + 1;
	in2 = aui.floyd_conb_2->currentIndex() + 1;
	if (ind1 != "" && ind2 != "")
	{
		index1 = ind1;
		index2 = ind2;
	}
	else
	{
		index1 = to_string(in1);
		index2 = to_string(in2);
	}
	set.graph->getMinLen(index1, index2, aui.textEdit_4);
}
void analysis::prime_kruskal()
{
	if (aui.mini_mode->currentIndex() == 0)
		if (aui.prim_comb->currentIndex() != 0)
		{
			set.graph->prime(set.sixtydata_List, aui.textEdit_5, aui.prim_comb->currentIndex());
		}
		else set.graph->prime(set.sixtydata_List, aui.textEdit_5);
	else if (aui.mini_mode->currentIndex() == 1)
		set.graph->kruskal(set.sixtydata_List, aui.textEdit_5);
}
void analysis::bip_graph()
{
	int pos[10] =
	{
		aui.comboBox->currentIndex() + 1,   aui.comboBox_2->currentIndex() + 1,
		aui.comboBox_3->currentIndex() + 1, aui.comboBox_4->currentIndex() + 1,
		aui.comboBox_5->currentIndex() + 1, aui.comboBox_6->currentIndex() + 1,
		aui.comboBox_7->currentIndex() + 1, aui.comboBox_8->currentIndex() + 1,
		aui.comboBox_9->currentIndex() + 1, aui.comboBox_10->currentIndex() + 1,
	};
	set.graph->bip(set.sixtydata_List, pos, aui.textEdit_6);
}
