#include "qstocksys.h"
#include <qtextcodec.h>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec* gbk = QTextCodec::codecForName("gb18030");
    QTextCodec::setCodecForLocale(gbk);
    QStocksys w;
    w.show();
    return a.exec();
}
