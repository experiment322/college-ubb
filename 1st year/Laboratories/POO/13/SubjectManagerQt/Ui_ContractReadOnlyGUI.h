#ifndef UI_CONTRACTREADONLYGUI_H
#define UI_CONTRACTREADONLYGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

class Ui_ContractReadOnlyGUI
{
public:

    void setupUi(QDialog *ContractReadOnlyGUI)
    {
        if (ContractReadOnlyGUI->objectName().isEmpty())
            ContractReadOnlyGUI->setObjectName(QStringLiteral("ContractReadOnlyGUI"));
        ContractReadOnlyGUI->resize(480, 640);

        retranslateUi(ContractReadOnlyGUI);

        QMetaObject::connectSlotsByName(ContractReadOnlyGUI);
    } // setupUi

    void retranslateUi(QDialog *ContractReadOnlyGUI)
    {
        ContractReadOnlyGUI->setWindowTitle(QApplication::translate("ContractReadOnlyGUI", "Dialog", nullptr));
    } // retranslateUi

};

#endif // UI_CONTRACTREADONLYGUI_H
