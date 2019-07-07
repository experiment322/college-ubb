#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Ui_MainWindow.h"
#include "Observer.h"
#include "Dialog.h"
#include "List.h"
#include "Subject.h"
#include "SubjectManager.h"
#include "ContractManager.h"

class MainWindow: public QMainWindow, public Observer
{
Q_OBJECT

public:
    explicit MainWindow(ContractManager& manager, SubjectManager& service, QWidget* parent = nullptr);
    ~MainWindow();

public slots:
    void readSubjects();

    void showCreateDialog();
    void showUpdateDialog();
    void showDeleteDialog();

    void showContractCRUDDialog();
    void showContractRODialog();

    void sortSubjectsByName();
    void sortSubjectsByHperw();
    void sortSubjectsByProfessorType();

    void filterByHperw();
    void filterByProfessor();

    void Update();

private:
    Ui_MainWindow* ui;
    SubjectManager& service;
    ContractManager& manager;

    void fillTable(const List<Subject>& subjects, bool reverse = false);
};

#endif // MAINWINDOW_H
