#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTableWidget *subjectTable;
    QPushButton *sortProfessorTypeButton;
    QPushButton *sortHperwButton;
    QPushButton *sortNameButton;
    QComboBox *sortOrderBox;
    QPushButton *createButton;
    QPushButton *updateButton;
    QPushButton *deleteButton;
    QPushButton *filterHperwButton;
    QPushButton *filterProfessorButton;
    QLineEdit *filterField;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(800, 600));
        MainWindow->setMaximumSize(QSize(800, 600));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        subjectTable = new QTableWidget(centralWidget);
        if (subjectTable->columnCount() < 4)
            subjectTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        subjectTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        subjectTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignCenter);
        subjectTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setTextAlignment(Qt::AlignCenter);
        subjectTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        subjectTable->setObjectName(QStringLiteral("subjectTable"));
        subjectTable->setGeometry(QRect(10, 10, 781, 411));
        subjectTable->horizontalHeader()->setDefaultSectionSize(150);
        subjectTable->horizontalHeader()->setStretchLastSection(true);
        sortProfessorTypeButton = new QPushButton(centralWidget);
        sortProfessorTypeButton->setObjectName(QStringLiteral("sortProfessorTypeButton"));
        sortProfessorTypeButton->setGeometry(QRect(500, 550, 291, 34));
        sortHperwButton = new QPushButton(centralWidget);
        sortHperwButton->setObjectName(QStringLiteral("sortHperwButton"));
        sortHperwButton->setGeometry(QRect(500, 510, 291, 34));
        sortNameButton = new QPushButton(centralWidget);
        sortNameButton->setObjectName(QStringLiteral("sortNameButton"));
        sortNameButton->setGeometry(QRect(500, 470, 291, 34));
        sortOrderBox = new QComboBox(centralWidget);
        sortOrderBox->addItem(QString());
        sortOrderBox->addItem(QString());
        sortOrderBox->setObjectName(QStringLiteral("sortOrderBox"));
        sortOrderBox->setGeometry(QRect(500, 430, 291, 31));
        createButton = new QPushButton(centralWidget);
        createButton->setObjectName(QStringLiteral("createButton"));
        createButton->setGeometry(QRect(10, 510, 161, 71));
        updateButton = new QPushButton(centralWidget);
        updateButton->setObjectName(QStringLiteral("updateButton"));
        updateButton->setGeometry(QRect(170, 510, 161, 71));
        deleteButton = new QPushButton(centralWidget);
        deleteButton->setObjectName(QStringLiteral("deleteButton"));
        deleteButton->setGeometry(QRect(330, 510, 161, 71));
        filterHperwButton = new QPushButton(centralWidget);
        filterHperwButton->setObjectName(QStringLiteral("filterHperwButton"));
        filterHperwButton->setGeometry(QRect(10, 470, 241, 41));
        filterProfessorButton = new QPushButton(centralWidget);
        filterProfessorButton->setObjectName(QStringLiteral("filterProfessorButton"));
        filterProfessorButton->setGeometry(QRect(250, 470, 241, 41));
        filterField = new QLineEdit(centralWidget);
        filterField->setObjectName(QStringLiteral("filterField"));
        filterField->setGeometry(QRect(10, 430, 481, 31));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Subject Manager Qt", nullptr));
        QTableWidgetItem *___qtablewidgetitem = subjectTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "NAME", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = subjectTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "TYPE", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = subjectTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "PROFESSOR", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = subjectTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "HOURS/WEEK", nullptr));
        sortProfessorTypeButton->setText(QApplication::translate("MainWindow", "Sort by Professor + Type", nullptr));
        sortHperwButton->setText(QApplication::translate("MainWindow", "Sort by Hours/Week", nullptr));
        sortNameButton->setText(QApplication::translate("MainWindow", "Sort by Name", nullptr));
        sortOrderBox->setItemText(0, QApplication::translate("MainWindow", "Ascending", nullptr));
        sortOrderBox->setItemText(1, QApplication::translate("MainWindow", "Descending", nullptr));

        createButton->setText(QApplication::translate("MainWindow", "Create", nullptr));
        updateButton->setText(QApplication::translate("MainWindow", "Update", nullptr));
        deleteButton->setText(QApplication::translate("MainWindow", "Delete", nullptr));
        filterHperwButton->setText(QApplication::translate("MainWindow", "Filter by Hours/Week", nullptr));
        filterProfessorButton->setText(QApplication::translate("MainWindow", "Filter by Professor", nullptr));
    } // retranslateUi

};

#endif // UI_MAINWINDOW_H
