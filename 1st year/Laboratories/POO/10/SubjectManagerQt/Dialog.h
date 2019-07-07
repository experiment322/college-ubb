#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "Ui_Dialog.h"
#include "SubjectManager.h"

class Dialog: public QDialog
{
Q_OBJECT

public:
    explicit Dialog(SubjectManager& service, QWidget* parent = nullptr);
    ~Dialog();

public slots:
    void showCreate();
    void showUpdate();
    void showDelete();

    void createSubject();
    void updateSubject();
    void deleteSubject();

private:
    Ui_Dialog* ui;
    SubjectManager& service;
};

#endif // DIALOG_H
