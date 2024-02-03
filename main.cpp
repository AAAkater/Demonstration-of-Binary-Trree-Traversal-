#include "tree.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    tree w;
    w.show();
    return app.exec();
}
