#ifndef CONTRACTREADONLYGUI_H
#define CONTRACTREADONLYGUI_H

#include <QDialog>
#include "Ui_ContractReadOnlyGUI.h"
#include "ContractManager.h"
#include "Observer.h"

class ContractReadOnlyGUI : public QDialog, public Observer
{
    Q_OBJECT

public:
    explicit ContractReadOnlyGUI(ContractManager& manager, QWidget* parent = nullptr);
    ~ContractReadOnlyGUI();

    void drawSubjects();

    // observer interface
    void Update();

protected:
    void paintEvent(QPaintEvent* event);

private:
    Ui_ContractReadOnlyGUI* ui;
    ContractManager& manager;
};

#endif // CONTRACTREADONLYGUI_H
