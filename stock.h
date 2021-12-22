#pragma once
#include <iostream>
#include <sstream>

using namespace std;

typedef struct priceNode
{
	//���̼� ���̼� �ǵ���
	string tradeDate = "0";
	double openPrice = -1;
	double closePrice = -1;
	double quotePerChange = 0;
}priceNode, * priceList;

class stock
{
public:
	void initStock(string);
	void initTradeLog(string);
	/*string getCode() { return stockCode; }
	string getName() { return stockname; }*/
private:
	string stockCode;		//��Ʊ����
	string stockName;		//��Ʊ���
	string industryCode;	//��ҵ����
	string firstCatg;		//һ������
	string secondCatg;		//��������
	string exchange;		//���н�����
	string compName;		//��˾ȫ��
	string listdate;		//��������
	string province;		//ʡ��
	string city;			//����
	string legalp;			//����
	string address;			//��ַ
	string website;			//��ַ
	string email;			//����
	string tel;				//�绰
	string bussiness;		//��Ӫҵ��
	string scope;			//��Ӫ��Χ

	priceList tradeLog;

	friend class LNode;
	friend class hashSearch;
};

