#include "wframe2.h"
#include "ui_wframe2.h"

WFrame2::WFrame2(QWidget *parent, Qt::WindowFlags f):
    DDialog(parent, f),
    ui(new Ui::WFrame2)
{
    ui->setupUi(this);

    try
    {
        tree1 = new DTreeList(this);
        ui->containerTree1->layout()->addWidget(tree1);

        tree2 = new DTreeList(this);
        ui->containerTree2->layout()->addWidget(tree2);

        tree3 = new DTreeList(this);
        ui->containerTree3->layout()->addWidget(tree3);

        tree4 = new DTreeList(this);
        ui->containerTree4->layout()->addWidget(tree4);
    }
    catch(...)
    {
        delete tree1;
        delete tree2;
        delete tree3;
        delete tree4;
        throw;
    }

    ui->splitter->setSizes(QList<int>({INT_MAX, INT_MAX}));
    ui->splitter_2->setSizes(QList<int>({INT_MAX/3, INT_MAX/3, INT_MAX/3})); // 3 - fixed bug

    initTree(tree1);
    initTree(tree2);
    initTree(tree3);
    initTree(tree4);

}

WFrame2::~WFrame2()
{
    if (tree1) tree1->deleteLater();
    if (tree2) tree2->deleteLater();
    if (tree3) tree3->deleteLater();
    if (tree4) tree4->deleteLater();

    delete ui;
}

QString WFrame2::defaultCellValue(const int r, const int c)
{
    return QString("Col%1 Row %2").arg(c+1).arg(r+1);
}

void WFrame2::initTree(DTreeList *tree)
{
    DStandartItemModel* pModel = tree->sourceModel();
    if (!pModel) return;
    int treeColumnCount = 32;
    pModel->setColumnCount(treeColumnCount);

    tree->setSelectionBehavior(QAbstractItemView::SelectRows);
    tree->setSelectionMode(QAbstractItemView::MultiSelection);
    tree->setSelectionMode(QAbstractItemView::ExtendedSelection);
    tree->setSortingEnabled(true);

    // generate test data
    for(int i=0;i<treeColumnCount;++i)
    {
        pModel->setHorizontalHeaderItem(i, QString(tr("Col%1")).arg(i+1));
    }

    int &row = tree->lastRowIndex;
    for(int i=0;i<2;++i)
    {
        QList<QStandardItem *> items0;
        for (int c=0;c<treeColumnCount;++c)
        {
            QStandardItem *item = new QStandardItem(defaultCellValue(row,c));
            items0.append(item);
        }
        // add icon to row
        items0[0]->setData(QIcon(":/images/images/3.png"), DTreeList::DATA_ROW_ICON);
        row++;

        for(int j=0;j<2;++j)
        {
            QList<QStandardItem *> items1;
            for (int c=0;c<treeColumnCount;++c)
                items1.append(new QStandardItem(defaultCellValue(row,c)));
            items1[0]->setData(QIcon(":/images/images/1.png"), DTreeList::DATA_ROW_ICON);
            items0[0]->appendRow(items1);

            for(int k=0;k<2;++k)
            {
                row++;
                QList<QStandardItem *> items2;
                for (int c=1;c<treeColumnCount+1;++c)
                    items2.append(new QStandardItem(defaultCellValue(row,c)));
                items1[0]->appendRow(items2);
            }
            row++;
        }
        pModel->appendRow(items0);
    }

    tree->expandAll();
}

void WFrame2::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}
