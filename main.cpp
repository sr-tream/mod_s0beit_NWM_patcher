#include "nwm.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NWM w;
    w.show();

    return a.exec();
}
