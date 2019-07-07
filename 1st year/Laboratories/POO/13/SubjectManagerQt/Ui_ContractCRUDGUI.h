#ifndef UI_CONTRACTCRUDGUI_H
#define UI_CONTRACTCRUDGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

class Ui_ContractCRUDGUI
{
public:
    QDialogButtonBox *buttonBox;
    QListView *subjectListView;
    QPushButton *addPushButton;
    QLineEdit *subjectLineEdit;
    QPushButton *removePushButton;
    QSpinBox *amountSpinBox;
    QPushButton *generatePushButton;

    void setupUi(QDialog *ContractCRUDGUI)
    {
        if (ContractCRUDGUI->objectName().isEmpty())
            ContractCRUDGUI->setObjectName(QStringLiteral("ContractCRUDGUI"));
        ContractCRUDGUI->resize(240, 320);
        buttonBox = new QDialogButtonBox(ContractCRUDGUI);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(10, 291, 221, 27));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);
        buttonBox->setCenterButtons(true);
        subjectListView = new QListView(ContractCRUDGUI);
        subjectListView->setObjectName(QStringLiteral("subjectListWidget"));
        subjectListView->setGeometry(QRect(10, 10, 221, 191));
        addPushButton = new QPushButton(ContractCRUDGUI);
        addPushButton->setObjectName(QStringLiteral("addPushButton"));
        addPushButton->setGeometry(QRect(10, 230, 111, 34));
        subjectLineEdit = new QLineEdit(ContractCRUDGUI);
        subjectLineEdit->setObjectName(QStringLiteral("subjectLineEdit"));
        subjectLineEdit->setGeometry(QRect(10, 200, 221, 28));
        removePushButton = new QPushButton(ContractCRUDGUI);
        removePushButton->setObjectName(QStringLiteral("removePushButton"));
        removePushButton->setGeometry(QRect(10, 260, 111, 34));
        amountSpinBox = new QSpinBox(ContractCRUDGUI);
        amountSpinBox->setObjectName(QStringLiteral("amountSpinBox"));
        amountSpinBox->setGeometry(QRect(120, 230, 111, 26));
        amountSpinBox->setMaximum(1000);
        generatePushButton = new QPushButton(ContractCRUDGUI);
        generatePushButton->setObjectName(QStringLiteral("generatePushButton"));
        generatePushButton->setGeometry(QRect(120, 260, 111, 34));

        retranslateUi(ContractCRUDGUI);
        QObject::connect(buttonBox, SIGNAL(accepted()), ContractCRUDGUI, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ContractCRUDGUI, SLOT(reject()));

        QMetaObject::connectSlotsByName(ContractCRUDGUI);
    } // setupUi

    void retranslateUi(QDialog *ContractCRUDGUI)
    {
        ContractCRUDGUI->setWindowTitle(QApplication::translate("ContractCRUDGUI", "Contract CRUD GUI", nullptr));
        addPushButton->setText(QApplication::translate("ContractCRUDGUI", "Add", nullptr));
        removePushButton->setText(QApplication::translate("ContractCRUDGUI", "Delete", nullptr));
        generatePushButton->setText(QApplication::translate("ContractCRUDGUI", "Generate", nullptr));
    } // retranslateUi

};

#endif // UI_CONTRACTCRUDGUI_H
