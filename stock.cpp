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

void stock::initTradeLog(string inputs)
{
	istringstream isstream(inputs);
}