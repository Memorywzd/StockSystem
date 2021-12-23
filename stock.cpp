#include "stock.h"

void stock::initStock(string inputs)
{
	istringstream isstream(inputs);
	isstream >> stockCode >> stockName >> industryCode >> firstCatg;
	isstream >> secondCatg >> exchange >> compName >> listdate;
	isstream >> province >> city >> legalp >> address;
	isstream >> website >> email >> tel >> bussiness;
	isstream >> scope;
}

void stock::initTradeLog()
{
	tradeLog = new priceNode;
	tradeLog->next = NULL;
}

void stock::addLogData(string date, double op, double cp, double qpc)
{
	priceNode* tail = tradeLog;
	while (tail->next)
	{
		tail = tail->next;
	}
	priceNode* p = new priceNode;
	p->tradeDate = date;
	p->openPrice = op;
	p->closePrice = cp;
	p->quotePerChange = qpc;
	p->next = NULL;
	tail->next = p;
	tail = p;
}