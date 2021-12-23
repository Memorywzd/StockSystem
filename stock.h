#pragma once
#include <iostream>
#include <sstream>

using namespace std;

typedef struct priceNode
{
	//开盘价 收盘价 涨跌幅
	string tradeDate;
	double openPrice;
	double closePrice;
	double quotePerChange;

	priceNode* next;
}priceNode, * priceList;

class stock
{
public:
	void initStock(string);
	void initTradeLog();
	void addLogData(string, double, double, double);
	priceList getLog_ptr() { return tradeLog; }
	string getCode() { return stockCode; }
	/*string getName() { return stockname; }*/
private:
	string stockCode;		//股票代码
	string stockName;		//股票简称
	string industryCode;	//行业编码
	string firstCatg;		//一级门类
	string secondCatg;		//二级门类
	string exchange;		//上市交易所
	string compName;		//公司全称
	string listdate;		//上市日期
	string province;		//省份
	string city;			//城市
	string legalp;			//法人
	string address;			//地址
	string website;			//网址
	string email;			//邮箱
	string tel;				//电话
	string bussiness;		//主营业务
	string scope;			//经营范围

	priceList tradeLog;

	friend class fileIO;
	friend class LinkList;
	friend class hashSearch;
};

