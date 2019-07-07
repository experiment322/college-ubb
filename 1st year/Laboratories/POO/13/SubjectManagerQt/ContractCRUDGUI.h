#ifndef CONTRACTCRUDGUI_H
#define CONTRACTCRUDGUI_H

#include <QDialog>

#include "Ui_ContractCRUDGUI.h"
#include "ContractManager.h"
#include "Observer.h"

class SubjectListModel : public QAbstractListModel, public Observer
{
    Q_OBJECT
public:
    SubjectListModel(ContractManager& manager, QObject* parent = nullptr) : QAbstractListModel{ parent }, manager{ manager }
    {
        manager.Attach(this);
    }

    ~SubjectListModel()
    {
        manager.Detach(this);
    }

    void Update()
    {
        emit dataChanged(createIndex(0, 0), createIndex(0, 0));
    }

    int rowCount(const QModelIndex&) const
    {
        return int(manager.subjects.size());
    }

    int columnCount(const QModelIndex&) const
    {
        return  1;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const
    {
        switch (role)
        {
        case Qt::DisplayRole:
            return QString::fromStdString(manager.subjects[size_t(index.row())].toString());
        default:
            return QVariant{};
        }
    }

private:
    ContractManager& manager;
};

class ContractCRUDGUI : public QDialog/*, public Observer*/
{
    Q_OBJECT

public:
    explicit ContractCRUDGUI(ContractManager& manager, QWidget* parent = nullptr);
    ~ContractCRUDGUI();

    void addSubject();
    void removeSubject();
    void generateContract();

private:
    Ui_ContractCRUDGUI* ui;
    ContractManager& manager;
    SubjectListModel listModel;

    void showErrorMessageBox();
};

#endif // CONTRACTCRUDGUI_H
