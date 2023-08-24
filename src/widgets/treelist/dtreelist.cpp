#include "dtreelist.h"

#include <QStandardItemModel>
#include <QMenu>
#include <QDebug>

DStandartItemModel::DStandartItemModel(QObject *parent) : QStandardItemModel(parent)
{

}

DStandartItemModel::~DStandartItemModel()
{

}

void DStandartItemModel::setHorizontalHeaderItem(int column, const QString &text)
{
    QStandardItemModel::setHorizontalHeaderItem(column, new QStandardItem(text));
}

DTreeList::DTreeList(QWidget *parent) : QTreeView(parent),
    contextMenu(nullptr)
{
    DStandartItemModel* model = new DStandartItemModel();
    setModel(model);
}

DTreeList::~DTreeList()
{
    if(contextMenu) contextMenu->deleteLater();
}

void DTreeList::setMenu(QMenu *const menu)
{
    if (contextMenu) {
        contextMenu->deleteLater();
        disconnect(this, SIGNAL(customContextMenuRequested(const QPoint)), this, SLOT(slotTreeMenu(const QPoint)));
    }
    if (!menu) return;

    contextMenu = menu;

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint)), this, SLOT(slotTreeMenu(const QPoint)));
}

void DTreeList::slotTreeMenu(const QPoint &/*pos*/)
{
    if (!contextMenu) return;

//    QMenu menu;
//    menu.addAction (QStringLiteral ("Expand"), this, SLOT (test()));
//    menu.addSeparator (); // Добавляем разделитель
//    menu.addAction (QStringLiteral ("сворачивание"), this, SLOT (test()));
    contextMenu->exec(QCursor::pos());
}

void DTreeList::removeSelectedRows()
{
    qDebug() << "removeSelectedRows";
    QModelIndexList idx = selectionModel()->selectedIndexes();
    QModelIndexList::iterator index = idx.begin();
    while (index!=idx.end())
    {
        model()->removeRow((*index).row(), (*index).parent());
        index++;
    }
//    while(!selectionModel()->selectedIndexes().isEmpty()) {
//        const QModelIndex idx = selectionModel()->selectedIndexes().first();
//        model()->removeRow(idx.row(), idx.parent());
//    }
}

