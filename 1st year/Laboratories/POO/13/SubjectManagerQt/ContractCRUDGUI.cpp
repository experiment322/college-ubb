#include "ContractCRUDGUI.h"
#include <QtWidgets/QMessageBox>
#include <QAbstractListModel>

ContractCRUDGUI::ContractCRUDGUI(ContractManager& manager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui_ContractCRUDGUI),
    manager{ manager },
    listModel { manager }
{
    ui->setupUi(this);

    connect(ui->addPushButton, &QPushButton::clicked, this, &ContractCRUDGUI::addSubject);
    connect(ui->removePushButton, &QPushButton::clicked, this, &ContractCRUDGUI::removeSubject);
    connect(ui->generatePushButton, &QPushButton::clicked, this, &ContractCRUDGUI::generateContract);

    ui->subjectListView->setModel(&listModel);
}

ContractCRUDGUI::~ContractCRUDGUI()
{
    delete ui;
}

void ContractCRUDGUI::addSubject()
{
    if (!manager.addSubject(ui->subjectLineEdit->text().toStdString()))
    {
        showErrorMessageBox();
    }
}

void ContractCRUDGUI::removeSubject()
{
    if (!manager.removeSubject(ui->subjectLineEdit->text().toStdString()))
    {
        showErrorMessageBox();
    }
}

void ContractCRUDGUI::generateContract()
{
    manager.generateContract(size_t(ui->amountSpinBox->value()));
}

void ContractCRUDGUI::showErrorMessageBox()
{
    QMessageBox* msg = new QMessageBox;
    msg->setWindowTitle("Error");
    msg->setText("The subject doesn't exist in the database!");
    msg->setDetailedText(ui->subjectLineEdit->text());
    msg->show();
}
