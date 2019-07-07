#include "ui.h"

#include <qwidget.h>
#include <qlineedit.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include "controller.h"

using namespace std;

MainWindow::MainWindow(FlightController& Controller, QWidget* Parent) : QMainWindow(Parent), controller{ Controller }
{
    this->setGeometry(0, 0, 400, 600);
    mainWidget = new QWidget(this);
    mainWidget->setGeometry(0, 0, 400, 600);
    idLineEdit = new QLineEdit(mainWidget);
    idLineEdit->setGeometry(0, 0, 400, 30);
    durationLineEdit = new QLineEdit(mainWidget);
    durationLineEdit->setGeometry(0, 30, 400, 30);
    freeSeatsLineEdit = new QLineEdit(mainWidget);
    freeSeatsLineEdit->setGeometry(0, 60, 400, 30);
    departureCityLineEdit = new QLineEdit(mainWidget);
    departureCityLineEdit->setGeometry(0, 90, 400, 30);
    arrivalCityLineEdit = new QLineEdit(mainWidget);
    arrivalCityLineEdit->setGeometry(0, 120, 400, 30);
    addPushButton = new QPushButton(mainWidget);
    addPushButton->setGeometry(0, 150, 400, 30);
    addPushButton->setText("Adauga Zbor");

    QObject::connect(addPushButton, &QPushButton::clicked, this, &MainWindow::addFlight);
}

MainWindow::~MainWindow()
{

}

void MainWindow::addFlight()
{

}
