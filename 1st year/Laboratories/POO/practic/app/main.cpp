#include <QApplication>
#include "mainwindow.h"
#include "repository.h"
#include "service.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repository;
    Service service(repository);
    MainWindow w(service);
    w.show();
    return a.exec();
}
