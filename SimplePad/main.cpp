#include "SimplePad.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimplePad w;
    w.show();
    return a.exec();
}
