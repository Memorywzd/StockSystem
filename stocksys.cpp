#include <iostream>
#include "libxl.h"

#include "fileIO.h"
#include "stock.h"
#include "ds.h"

using namespace std;
using namespace libxl;

int main()
{
	stock tempStock;
	fileIO intro_file("./data/A�ɹ�˾���.xlsx");
	intro_file.readline(1);
	cout << intro_file.get_cont_str();
	return 0;
}