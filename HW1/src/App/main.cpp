#include "minidraw.h"
#include <QtWidgets/QApplication>


int main(int argc, char* argv[])
{
    //检查内存泄露
    _CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
    QApplication a(argc, argv);
    MiniDraw w;
    w.resize(1024,768);
    w.setWindowTitle("画板");
    w.setWindowIcon(QIcon("../resources/77.jpg"));
    w.show();
    return a.exec();
}
