#pragma once
#include <iostream>

using namespace std;

class stock
{
public:

private:
	string stockCode;		//��Ʊ����
	string shortname;		//��Ʊ���
	string industryCode;	//��ҵ����
	string firstCatg;		//һ������
	string secondCatg;		//��������
	string exchange;		//���н�����
	string fullname;		//��˾ȫ��
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

	//���̼� ���̼� �ǵ���
	double openPrice = -1;
	double closePrice = -1;
	double quoteChange = 0;
};

