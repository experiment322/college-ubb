#include "mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(Service& service, QWidget* parent)
    : QMainWindow(parent), service(service)
{
    resize(800, 600);
    tasksTableWidget = new QTableWidget(this);
    tasksTableWidget->resize(800, 400);
    tasksTableWidget->setColumnCount(4);
    tasksTableWidget->setColumnWidth(0, 100);
    tasksTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("ID"));
    tasksTableWidget->setColumnWidth(1, 200);
    tasksTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Descriere"));
    tasksTableWidget->setColumnWidth(2, 200);
    tasksTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Stare"));
    tasksTableWidget->setColumnWidth(3, 200);
    tasksTableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Numar de programatori"));
    idLineEdit = new QLineEdit(this);
    idLineEdit->setGeometry(0, 400, 200, 25);
    idLineEdit->setPlaceholderText("ID");
    descriptionLineEdit = new QLineEdit(this);
    descriptionLineEdit->setGeometry(200, 400, 200, 25);
    descriptionLineEdit->setPlaceholderText("Descriere");
    stateLineEdit = new QLineEdit(this);
    stateLineEdit->setGeometry(400, 400, 200, 25);
    stateLineEdit->setPlaceholderText("Stare");
    programmersLineEdit = new QLineEdit(this);
    programmersLineEdit->setGeometry(600, 400, 200, 25);
    programmersLineEdit->setPlaceholderText("Programatori (maxim 4)");
    addPushButton = new QPushButton(this);
    addPushButton->setGeometry(0, 425, 400, 25);
    addPushButton->setText("Adauga");
    filterLineEdit = new QLineEdit(this);
    filterLineEdit->setGeometry(400, 425, 400, 25);
    filterLineEdit->setPlaceholderText("Filtrare dupa programator");
    connect(addPushButton, &QPushButton::clicked, this, &MainWindow::addTask);
    connect(filterLineEdit, &QLineEdit::textChanged, this, &MainWindow::filterTable);
    fillTable();
}

MainWindow::~MainWindow()
{
}

void MainWindow::addTask()
{
    bool ok = true;
    int id = idLineEdit->text().toInt(&ok);
    if (!ok)
    {
        showError("Invalid ID!");
        return;
    }
    auto errorMessage = service.add(id,
                                    descriptionLineEdit->text().toStdString(),
                                    stateLineEdit->text().toStdString(),
                                    programmersLineEdit->text().toStdString());
    if (errorMessage.size())
    {
        showError(errorMessage.c_str());
        return;
    }
    fillTable();
}

void MainWindow::filterTable()
{
    if (filterLineEdit->text().size() == 0) fillTable();
    else
    {
        while (tasksTableWidget->rowCount()) tasksTableWidget->removeRow(0);
        for (auto t : service.getAll())
        {
            for (auto p : t.getProgrammers())
            {
                if (p.find(filterLineEdit->text().toStdString()) != std::string::npos)
                {
                    tasksTableWidget->insertRow(tasksTableWidget->rowCount());
                    tasksTableWidget->setItem(tasksTableWidget->rowCount() - 1, 0,
                                              new QTableWidgetItem(QString::fromStdString(std::to_string(t.getId()))));
                    tasksTableWidget->setItem(tasksTableWidget->rowCount() - 1, 1,
                                              new QTableWidgetItem(QString::fromStdString(t.getDescription())));
                    tasksTableWidget->setItem(tasksTableWidget->rowCount() - 1, 2,
                                              new QTableWidgetItem(QString::fromStdString(t.getState())));
                    tasksTableWidget->setItem(tasksTableWidget->rowCount() - 1, 3,
                                              new QTableWidgetItem(QString::fromStdString(std::to_string(t.getProgrammers().size()))));
                    break;
                }
            }
        }
    }
}

void MainWindow::fillTable()
{
    while (tasksTableWidget->rowCount()) tasksTableWidget->removeRow(0);
    for (auto t : service.getAll())
    {
        tasksTableWidget->insertRow(tasksTableWidget->rowCount());
        tasksTableWidget->setItem(tasksTableWidget->rowCount() - 1, 0,
                                  new QTableWidgetItem(QString::fromStdString(std::to_string(t.getId()))));
        tasksTableWidget->setItem(tasksTableWidget->rowCount() - 1, 1,
                                  new QTableWidgetItem(QString::fromStdString(t.getDescription())));
        tasksTableWidget->setItem(tasksTableWidget->rowCount() - 1, 2,
                                  new QTableWidgetItem(QString::fromStdString(t.getState())));
        tasksTableWidget->setItem(tasksTableWidget->rowCount() - 1, 3,
                                  new QTableWidgetItem(QString::fromStdString(std::to_string(t.getProgrammers().size()))));
    }
}

void MainWindow::showError(QString details)
{
    QMessageBox* errorMessageBox = new QMessageBox(this);
    errorMessageBox->setText(details);
    errorMessageBox->show();
}
