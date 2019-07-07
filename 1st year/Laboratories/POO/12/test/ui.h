#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qmainwindow.h>
#include <qwidget.h>
#include <qlineedit.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include "controller.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    FlightController& controller;

    QWidget* mainWidget;
    QLineEdit* idLineEdit;
    QLineEdit* durationLineEdit;
    QLineEdit* freeSeatsLineEdit;
    QLineEdit* departureCityLineEdit;
    QLineEdit* arrivalCityLineEdit;
    QPushButton* addPushButton;
public:
    MainWindow(FlightController& Controller, QWidget* Parent = Q_NULLPTR);
    ~MainWindow();

public slots:
    void addFlight();
};

#endif // MAINWINDOW_H
