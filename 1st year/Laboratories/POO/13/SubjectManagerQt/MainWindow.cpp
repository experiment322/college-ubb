#include "MainWindow.h"
#include "Ui_MainWindow.h"
#include "Dialog.h"
#include "List.h"
#include "Subject.h"
#include "ContractCRUDGUI.h"
#include "ContractReadOnlyGUI.h"

MainWindow::MainWindow(ContractManager& manager, SubjectManager& service, QWidget* parent):
    QMainWindow{parent},
    ui{new Ui_MainWindow},
    service{ service },
    manager{ manager }
{
    ui->setupUi(this);

    // connecting ui buttons to crud actions
    connect(ui->createButton, &QPushButton::clicked, this, &MainWindow::showCreateDialog);
    connect(ui->updateButton, &QPushButton::clicked, this, &MainWindow::showUpdateDialog);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::showDeleteDialog);

    // connecting contract manager buttons
    connect(ui->contractCRUDGUIButton, &QPushButton::clicked, this, &MainWindow::showContractCRUDDialog);
    connect(ui->contractReadOnlyGUIButton, &QPushButton::clicked, this, &MainWindow::showContractRODialog);

    // connecting ui buttons to sort actions
    connect(ui->sortNameButton, &QPushButton::clicked, this, &MainWindow::sortSubjectsByName);
    connect(ui->sortHperwButton, &QPushButton::clicked, this, &MainWindow::sortSubjectsByHperw);
    connect(ui->sortProfessorTypeButton, &QPushButton::clicked, this, &MainWindow::sortSubjectsByProfessorType);

    // connecting ui buttons to filter actions
    connect(ui->filterHperwButton, &QPushButton::clicked, this, &MainWindow::filterByHperw);
    connect(ui->filterProfessorButton, &QPushButton::clicked, this, &MainWindow::filterByProfessor);

    // attach to observable
    service.Attach(this);

    // get initial list of items
    readSubjects();
}

MainWindow::~MainWindow()
{
    service.Detach(this);
    delete ui;
}

void MainWindow::Update()
{
    readSubjects();
}

void MainWindow::fillTable(const List<Subject>& subjects, bool reverse)
{
    while (ui->subjectTable->rowCount() > 0)
    {
        ui->subjectTable->removeRow(0);
    }
    for (auto s : subjects)
    {
        int newRowIndex = reverse ? 0 : ui->subjectTable->rowCount();
        ui->subjectTable->insertRow(newRowIndex);
        QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(s.getName()));
        QTableWidgetItem* type = new QTableWidgetItem(QString::fromStdString(s.getType()));
        QTableWidgetItem* prof = new QTableWidgetItem(QString::fromStdString(s.getProfessor()));
        QTableWidgetItem* hperw = new QTableWidgetItem(QString::fromStdString(std::to_string(s.getHperw())));
        ui->subjectTable->setItem(newRowIndex, 0, name);
        ui->subjectTable->setItem(newRowIndex, 1, type);
        ui->subjectTable->setItem(newRowIndex, 2, prof);
        ui->subjectTable->setItem(newRowIndex, 3, hperw);
    }
}

void MainWindow::readSubjects()
{
    const List<Subject>& subjects = service.getAll();
    fillTable(subjects);
}

void MainWindow::showCreateDialog()
{
    Dialog* dialog = new Dialog{ service };
    dialog->showCreate();
}

void MainWindow::showUpdateDialog()
{
    Dialog* dialog = new Dialog{ service };
    dialog->showUpdate();
}

void MainWindow::showDeleteDialog()
{
    Dialog* dialog = new Dialog{ service };
    dialog->showDelete();
}

void MainWindow::showContractCRUDDialog()
{
    ContractCRUDGUI* dialog = new ContractCRUDGUI{ manager };
    dialog->show();
}

void MainWindow::showContractRODialog()
{
    ContractReadOnlyGUI* dialog = new ContractReadOnlyGUI{ manager };
    dialog->show();
}

void MainWindow::sortSubjectsByName()
{
    const List<Subject> subjects = service.sortByName();
    fillTable(subjects, ui->sortOrderBox->currentText() == "Descending");
}

void MainWindow::sortSubjectsByHperw()
{
    const List<Subject> subjects = service.sortByHperw();
    fillTable(subjects, ui->sortOrderBox->currentText() == "Descending");
}

void MainWindow::sortSubjectsByProfessorType()
{
    const List<Subject> subjects = service.sortByProfessorType();
    fillTable(subjects, ui->sortOrderBox->currentText() == "Descending");
}

void MainWindow::filterByHperw()
{
    const List<Subject> subjects = ui->filterField->text().size() != 0
            ? service.filtrareHperw(ui->filterField->text().toInt())
            : service.getAll();
    fillTable(subjects);
}

void MainWindow::filterByProfessor()
{
    const List<Subject> subjects = ui->filterField->text().size() != 0
            ? service.filtrareProfessor(ui->filterField->text().toStdString())
            : service.getAll();
    fillTable(subjects);
}
