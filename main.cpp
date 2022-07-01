#include "miner.h"

#include <QApplication>
#include <QtWidgets>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Miner* miner = new Miner();
    miner->show();

    return app.exec();

}
