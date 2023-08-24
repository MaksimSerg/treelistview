#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardItemModel>
#include <QMenu>
#include <QDebug>

#include "src/widgets/treelist/dtreelist.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    DTreeList *tree1 = new DTreeList(this);
    ui->tree1->layout()->addWidget(tree1);

    // ?
    DStandartItemModel* model = dynamic_cast<DStandartItemModel*>(tree1->model());
    int tree1ColumnCount = 23;
    model->setColumnCount(tree1ColumnCount);
    for(int i=0;i<tree1ColumnCount;i++)
    {
        model->setHorizontalHeaderItem(i, QString(tr("Fr1 Tr1 Col%1")).arg(i));
    }

    for(int i=0;i<10;i++)
    {
        QList<QStandardItem *> items0;
        items0.append(new QStandardItem("cr1"));
        items0.append(new QStandardItem("cr1"));
        for(int j=0;j<10;j++)
        {
            QList<QStandardItem *> items1;
            items1.append(new QStandardItem("cr2"));
            items1.append(new QStandardItem("cr2"));
            items0[0]->appendRow(items1);
            for(int k=0;k<10;k++)
            {
                QList<QStandardItem *> items2;
                items2.append(new QStandardItem("cr3"));
                items2.append(new QStandardItem("cr3"));
                items1[0]->appendRow(items2);
            }
        }
        model->appendRow(items0);
    }

    QMenu *tree1Menu = new QMenu;
//    tree1Menu->addAction(tr("Delete"), tree1, SLOT (test()));
//    tree1Menu->addSeparator (); // Добавляем разделитель
    tree1Menu->addAction (QStringLiteral("Delete"), tree1, SLOT(removeSelectedRows()), QKeySequence::Delete);
    tree1->setMenu(tree1Menu);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::test()
{
    qDebug() << "MainWindow::test";
}



