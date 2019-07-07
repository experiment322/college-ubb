#include "Dialog.h"
#include "Ui_Dialog.h"
#include "Validator.h"
#include "SubjectRepo.h"

Dialog::Dialog(SubjectManager& service, QWidget* parent):
    QDialog{parent},
    ui{new Ui_Dialog},
    service{service}
{
    ui->setupUi(this);

    // connect close button
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::showCreate()
{
    ui->crudButton->setText("Create");
    connect(ui->crudButton, &QPushButton::clicked, this, &Dialog::createSubject);
    this->show();
}

void Dialog::showUpdate()
{
    ui->crudButton->setText("Update");
    connect(ui->crudButton, &QPushButton::clicked, this, &Dialog::updateSubject);
    this->show();
}

void Dialog::showDelete()
{
    ui->crudButton->setText("Delete");
    connect(ui->crudButton, &QPushButton::clicked, this, &Dialog::deleteSubject);
    this->show();
}

void Dialog::createSubject()
{
    ui->operationLog->clear();
    try
    {
        service.addSubject(
                    ui->nameField->text().toStdString(),
                    ui->typeField->text().toStdString(),
                    ui->professorField->text().toStdString(),
                    ui->hperwField->value());
    }
    catch (const ValidateException& e)
    {
        ui->operationLog->addItem("Invalid subject");
        for (auto err : e.getErrors())
        {
            ui->operationLog->addItem(QString::fromStdString(err));
        }
    }
    catch (const SubjectRepoException& e)
    {
        ui->operationLog->addItem("Invalid subject");
        ui->operationLog->addItem(QString::fromStdString(e.getError()));
    }
}

void Dialog::updateSubject()
{
    ui->operationLog->clear();
    try
    {
        service.updateSubject(
                    ui->nameField->text().toStdString(),
                    ui->typeField->text().toStdString(),
                    ui->professorField->text().toStdString(),
                    ui->hperwField->value());
    }
    catch (const ValidateException& e)
    {
        ui->operationLog->addItem("Invalid subject");
        for (auto err : e.getErrors())
        {
            ui->operationLog->addItem(QString::fromStdString(err));
        }
    }
    catch (const SubjectRepoException& e)
    {
        ui->operationLog->addItem("Invalid subject");
        ui->operationLog->addItem(QString::fromStdString(e.getError()));
    }
}

void Dialog::deleteSubject()
{
    ui->operationLog->clear();
    try
    {
        service.removeSubject(ui->nameField->text().toStdString());
    }
    catch (const SubjectRepoException& e)
    {
        ui->operationLog->addItem("Invalid subject");
        ui->operationLog->addItem(QString::fromStdString(e.getError()));
    }
}
