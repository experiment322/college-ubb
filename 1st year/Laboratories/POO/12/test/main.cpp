#include <qapplication.h>
#include "ui.h"
#include "repository.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    FlightRepository repository;
    FlightController controller(repository);
    QApplication a(argc, argv);
    MainWindow w(controller);
    w.show();

    return a.exec();
}
