#include "accountmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    AccountManager manager;
    manager.startLogin();

    return app.exec();
}
