#include "ContractReadOnlyGUI.h"
#include <cstdlib>
#include <QPainter>

ContractReadOnlyGUI::ContractReadOnlyGUI(ContractManager& manager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui_ContractReadOnlyGUI),
    manager{ manager }
{
    ui->setupUi(this);

    manager.Attach(this);

    repaint();
}

ContractReadOnlyGUI::~ContractReadOnlyGUI()
{
    manager.Detach(this);
    delete ui;
}

void ContractReadOnlyGUI::paintEvent(QPaintEvent*)
{
    QPainter p{ this };
    const QImage& book = QImage(":/images/book.png");
    int columns = geometry().width() / book.width();
    int col = 0, row = 0;
    for (auto s : manager.getSubjects())
    {
//        int rand_x = min(rand() % geometry().width(), geometry().width() - book.width());
//        int rand_y = min(rand() % geometry().height(), geometry().height() - book.height());
        p.setPen({ rand() % 256, rand() % 256, rand() % 256 });
        p.drawImage(col * book.width(), row * book.height(), book);
        p.drawEllipse(col * book.width(), row * book.height(), book.width(), book.height());
        col = (col + 1) % columns;
        row += col == 0 ? 1 : 0;
    }
}

void ContractReadOnlyGUI::Update()
{
    repaint();
}
