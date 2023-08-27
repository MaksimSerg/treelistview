#include "wframe1.h"
#include "ui_wframe1.h"

#include "src/widgets/treelist/dtreedelegate.h"

#include <QDebug>

WFrame1::WFrame1(QWidget *parent, Qt::WindowFlags f):
    DDialog(parent, f),
    ui(new Ui::WFrame1)
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
    }
    catch(...)
    {
        delete tree1;
        delete tree2;
        delete tree3;

        throw;
    }

    ui->splitter->setSizes(QList<int>({INT_MAX, INT_MAX}));
    ui->splitter_2->setSizes(QList<int>({INT_MAX, INT_MAX}));

    initTree1();
    initTree2();
    initTree3();
}

WFrame1::~WFrame1()
{
    if (tree1) tree1->deleteLater();
    if (tree2) tree2->deleteLater();
    if (tree3) tree3->deleteLater();

    delete ui;
}

QString WFrame1::defaultCellValue(const int r, const int c)
{
    return QString("Col%1 Row %2").arg(c+1).arg(r+1);
}

void WFrame1::initTree1()
{
    DStandartItemModel* pModel = tree1->sourceModel();
    if (!pModel) return;
    int treeColumnCount = 33;
    pModel->setColumnCount(treeColumnCount);

    tree1->setSelectionBehavior(QAbstractItemView::SelectRows);
    tree1->setSelectionMode(QAbstractItemView::MultiSelection);
    tree1->setSelectionMode(QAbstractItemView::ExtendedSelection);
    tree1->setSortingEnabled(true);

    // generate test data
    for(int i=0;i<treeColumnCount;++i)
    {
        pModel->setHorizontalHeaderItem(i, QString(tr("Col%1")).arg(i+1));
    }

    int &row = tree1->lastRowIndex;
    for(int i=0;i<10;++i)
    {
        QList<QStandardItem *> items0;
        for (int c=0;c<treeColumnCount;++c)
        {
            QStandardItem *item = new QStandardItem(defaultCellValue(row,c));
            if (c == 2)
            {
                item->setIcon(QIcon(":/images/images/1.png"));
            }
            if (c%3 == 0)
            {
                item->setData(QColor(Qt::white), Qt::ForegroundRole);
                item->setData(QColor(Qt::darkCyan), Qt::BackgroundRole);
            }
            if (c%4 == 0)
            {
                QFont font = item->font();
                font.setBold(true);
                item->setData(font, Qt::FontRole);
            }
            items0.append(item);
        }
        // add icon to row
        items0[0]->setData(QIcon(":/images/images/3.png"), DTreeList::DATA_ROW_ICON);
        row++;

        for(int j=0;j<10;++j)
        {
            QList<QStandardItem *> items1;
            for (int c=0;c<treeColumnCount;++c)
                items1.append(new QStandardItem(defaultCellValue(row,c)));
            items1[0]->setData(QIcon(":/images/images/1.png"), DTreeList::DATA_ROW_ICON);
            items0[0]->appendRow(items1);

            for(int k=0;k<10;++k)
            {
                row++;
                QList<QStandardItem *> items2;
                for (int c=0;c<treeColumnCount;++c)
                    items2.append(new QStandardItem(defaultCellValue(row,c)));
                items1[0]->appendRow(items2);
            }
            row++;
        }
        pModel->appendRow(items0);
    }

}

void WFrame1::initTree2()
{
    DStandartItemModel* pModel = tree2->sourceModel();
    if (!pModel) return;
    int treeColumnCount = 32;
    pModel->setColumnCount(treeColumnCount);

    tree2->setSelectionBehavior(QAbstractItemView::SelectRows);
    tree2->setSelectionMode(QAbstractItemView::MultiSelection);
    tree2->setSelectionMode(QAbstractItemView::ExtendedSelection);
    tree2->setSortingEnabled(true);

    // generate test data
    for(int i=0;i<treeColumnCount;++i)
    {
        pModel->setHorizontalHeaderItem(i, QString(tr("Col%1")).arg(i+1));
    }

    int &row = tree2->lastRowIndex;
    QList<QStandardItem *> items0;
    for (int c=0;c<treeColumnCount;++c)
    {
        QStandardItem *item = new QStandardItem(defaultCellValue(row,c));
        items0.append(item);
    }
    row++;

    for (int r=0; r<30;++r)
    {
        QList<QStandardItem *> items1;
        for (int c=0; c<treeColumnCount; ++c)
        {
            QStandardItem *item = new QStandardItem(defaultCellValue(row,c));
            items1.append(item);
            if (c==3)
            {
                item->setCheckable(true);
                item->setCheckState(r%2 ? Qt::Checked : Qt::Unchecked);
                item->setEditable(false);
            }
        }
        items0[0]->appendRow(items1);
        row++;
    }

    pModel->appendRow(items0);


    // delegates
    QStringList comboBoxItems = {"one","two","three"};
    tree2->setItemDelegateForColumn(1, new DTreeDelegateComboBox(tree1,comboBoxItems));
    // setCheckable

    tree2->header()->resizeSection(0, 150);
    tree2->expandAll();

}

QList<QStandardItem *> WFrame1::createRowsRecursive(int columnCount, int &r, int depth)
{
    QList<QStandardItem *> items;
    for (int c=0; c<columnCount; ++c)
    {
        QStandardItem *item = new QStandardItem(defaultCellValue(r,c));
        items.append(item);
    }
    r++;
    depth--;
    if (depth)
    {
        items[0]->appendRow(createRowsRecursive(columnCount, r, depth));
    }
    return items;
}

void WFrame1::initTree3()
{
    DStandartItemModel* pModel = tree3->sourceModel();
    if (!pModel) return;
    int treeColumnCount = 32;
    pModel->setColumnCount(treeColumnCount);

    tree3->setSelectionBehavior(QAbstractItemView::SelectRows);
    tree3->setSelectionMode(QAbstractItemView::MultiSelection);
    tree3->setSelectionMode(QAbstractItemView::ExtendedSelection);
    tree3->setSortingEnabled(true);

    // generate test data
    for(int i=0;i<treeColumnCount;i++)
    {
        pModel->setHorizontalHeaderItem(i, QString(tr("Col%1")).arg(i+1));
    }

    QList<QStandardItem *> items = createRowsRecursive(treeColumnCount, tree3->lastRowIndex, 100);
    pModel->appendRow(items);

    tree3->header()->resizeSection(0, 600);

    tree3->expandAll();
}

void WFrame1::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}
