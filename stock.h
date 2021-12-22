#pragma once
#include <iostream>

using namespace std;

class stock
{
public:

private:
	string stockCode;		//股票代码
	string shortname;		//股票简称
	string industryCode;	//行业编码
	string firstCatg;		//一级门类
	string secondCatg;		//二级门类
	string exchange;		//上市交易所
	string fullname;		//公司全称
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

	//开盘价 收盘价 涨跌幅
	double openPrice = -1;
	double closePrice = -1;
	double quoteChange = 0;
};

