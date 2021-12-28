#pragma once

#include <iostream>
#include "libxl.h"

#include <QtWidgets/QWidget>
#include "ui_qstocksys.h"
#include "ui_query.h"
#include "ui_analysis.h"

#include "ds.h"

using namespace std;
using namespace libxl;

class QStocksys : public QWidget
{
    Q_OBJECT

public:
    QStocksys(QWidget* parent = Q_NULLPTR);

private:
    Ui::QStocksysClass ui;

    ds dataset;
    void open_query();
    void open_analysis();
};

class query :public QWidget
{
    Q_OBJECT

public:
    query(ds&, QWidget* parent = Q_NULLPTR);
   
private:
    Ui::queryClass qui;

    void hash();
    void kmp();
    void bitree_q();
    void bitree_d();
    void linklist();

    ds& set;
};

class analysis :public QWidget
{
public:
    analysis(ds&, QWidget* parent = Q_NULLPTR);

private:
    Ui::analysisClass aui;

    void isort();
    void qsort();
    void esort();
    void min_len();
    void prime_kruskal();
    void bip_graph();

    ds& set;
};
