#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

class Ui_Dialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *nameField;
    QLabel *nameLabel;
    QLabel *typeLabel;
    QLineEdit *typeField;
    QLineEdit *professorField;
    QLabel *professorLabel;
    QLabel *hperwLabel;
    QPushButton *crudButton;
    QSpinBox *hperwField;
    QListWidget *operationLog;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(320, 320);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Dialog->sizePolicy().hasHeightForWidth());
        Dialog->setSizePolicy(sizePolicy);
        Dialog->setMinimumSize(QSize(320, 320));
        Dialog->setMaximumSize(QSize(320, 320));
        Dialog->setStyleSheet(QLatin1String("QLabel {\n"
"	font-size: 12px;\n"
"	background: rgba(88,88,88,75%);\n"
"	border-radius: 12px;\n"
"    border-bottom-right-radius: 0px;\n"
"}\n"
""));
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(10, 279, 301, 31));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);
        buttonBox->setCenterButtons(true);
        nameField = new QLineEdit(Dialog);
        nameField->setObjectName(QStringLiteral("nameField"));
        nameField->setGeometry(QRect(90, 10, 221, 31));
        nameLabel = new QLabel(Dialog);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));
        nameLabel->setGeometry(QRect(10, 10, 81, 31));
        nameLabel->setAlignment(Qt::AlignCenter);
        typeLabel = new QLabel(Dialog);
        typeLabel->setObjectName(QStringLiteral("typeLabel"));
        typeLabel->setGeometry(QRect(10, 60, 81, 31));
        typeLabel->setAlignment(Qt::AlignCenter);
        typeField = new QLineEdit(Dialog);
        typeField->setObjectName(QStringLiteral("typeField"));
        typeField->setGeometry(QRect(90, 60, 221, 31));
        professorField = new QLineEdit(Dialog);
        professorField->setObjectName(QStringLiteral("professorField"));
        professorField->setGeometry(QRect(90, 110, 221, 31));
        professorLabel = new QLabel(Dialog);
        professorLabel->setObjectName(QStringLiteral("professorLabel"));
        professorLabel->setGeometry(QRect(10, 110, 81, 31));
        professorLabel->setAlignment(Qt::AlignCenter);
        hperwLabel = new QLabel(Dialog);
        hperwLabel->setObjectName(QStringLiteral("hperwLabel"));
        hperwLabel->setGeometry(QRect(10, 160, 81, 31));
        hperwLabel->setAlignment(Qt::AlignCenter);
        crudButton = new QPushButton(Dialog);
        crudButton->setObjectName(QStringLiteral("crudButton"));
        crudButton->setGeometry(QRect(10, 203, 81, 71));
        hperwField = new QSpinBox(Dialog);
        hperwField->setObjectName(QStringLiteral("hperwField"));
        hperwField->setGeometry(QRect(90, 160, 221, 31));
        hperwField->setMaximum(60);
        operationLog = new QListWidget(Dialog);
        operationLog->setObjectName(QStringLiteral("operationLog"));
        operationLog->setGeometry(QRect(90, 200, 221, 71));

        retranslateUi(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "CRUD Dialog", nullptr));
        nameLabel->setText(QApplication::translate("Dialog", "Name", nullptr));
        typeLabel->setText(QApplication::translate("Dialog", "Type", nullptr));
        professorLabel->setText(QApplication::translate("Dialog", "Professor", nullptr));
        hperwLabel->setText(QApplication::translate("Dialog", "Hours/Week", nullptr));
        crudButton->setText(QApplication::translate("Dialog", "PushButton", nullptr));
    } // retranslateUi

};

#endif // UI_DIALOG_H
