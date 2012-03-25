#include <QtGui/QApplication>
#include "dbcviewer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DBCViewer w;
    w.show();

    return a.exec();
}
