#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include "service.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Service& service, QWidget* parent = Q_NULLPTR);
    ~MainWindow();

    /**
     * @brief addTask
     */
    void addTask();

    /**
     * @brief filterTable
     */
    void filterTable();

private:
    Service& service;
    QTableWidget* tasksTableWidget;
    QLineEdit* idLineEdit;
    QLineEdit* descriptionLineEdit;
    QLineEdit* stateLineEdit;
    QLineEdit* programmersLineEdit;
    QLineEdit* filterLineEdit;
    QPushButton* addPushButton;

    /**
     * @brief fillTable fills the table with the repository contents
     */
    void fillTable();

    /**
     * @brief showError print a message box with the encountered error
     * @param details
     */
    void showError(QString details);
};

#endif // MAINWINDOW_H
