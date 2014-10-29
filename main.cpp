
#include "boidscene.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BoidScene b;
    b.show();

    return a.exec();
}
