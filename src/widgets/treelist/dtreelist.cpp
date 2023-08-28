#include "dtreelist.h"

#include <QStandardItemModel>
#include <QMenu>
#include <QMessageBox>
#include <QInputDialog>
#include <QMenu>
#include <QColorDialog>
#include <QFontDialog>
#include <QHeaderView>
#include <QPaintEvent>
#include <QPainter>
#include <QStyle>
#include <QSortFilterProxyModel>
#include <QDebug>


DTreeList::DTreeList(QWidget *parent) : QTreeView(parent),
    lastRowIndex(0),
    m_rowIconSize(8,8),
    contextMenu(nullptr),
    m_sourceModel(nullptr)
{
    QSortFilterProxyModel *proxy = nullptr;
    QMenu *menuStyle = nullptr;
    QMenu *cMenu = nullptr;
    try
    {
        m_sourceModel = new DStandartItemModel(this);
        proxy = new DSortFilterProxyModel(this);
        menuStyle = new QMenu(tr("Style"));
        cMenu = new QMenu;
    }
    catch(...)
    {
        delete proxy;
        delete menuStyle;
        delete cMenu;
        throw;
    }

    proxy->setSourceModel(m_sourceModel);
    setModel(proxy);

    // context menu
    menuStyle->addAction(tr("Font"),        this, std::bind(&DTreeList::setRowStyle, this, CELL_SET_FONT, QVariant()));
    menuStyle->addAction(tr("Color"),       this, std::bind(&DTreeList::setRowStyle, this, CELL_SET_FONT_COLOR, QVariant()));
    menuStyle->addAction(tr("Background"),  this, std::bind(&DTreeList::setRowStyle, this, CELL_SET_BACKGROUND_COLOR, QVariant()));

    cMenu->addAction(tr("Add rows..."), this, SLOT(addMultiRows()));
    cMenu->addAction(tr("Add subrows..."), this, SLOT(addMultiSubRows()));
    cMenu->addSeparator();
    cMenu->addMenu(menuStyle);
    cMenu->addSeparator();
    cMenu->addAction(tr("Delete"), this, SLOT(removeSelectedRows()));

    setContextMenu(cMenu);

    // delegate for row icon
    setItemDelegateForColumn(0, new DVerticalHeaderItemDelegate(this, m_rowIconSize));

    // header context menu
    header()->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(header(), SIGNAL(customContextMenuRequested(const QPoint)), this , SLOT(slotHeaderMenu(const QPoint)));

    this->setStyleSheet("QTreeView{border: 1px solid transparent;}");

    setUniformRowHeights(true);
}

DTreeList::~DTreeList()
{
    if (contextMenu) contextMenu->deleteLater();
    if (m_sourceModel) m_sourceModel->deleteLater();
}

void DTreeList::setContextMenu(QMenu *const menu)
{
    if (contextMenu) {
        disconnect(this, SIGNAL(customContextMenuRequested(const QPoint)), this, SLOT(slotTreeMenu(const QPoint)));
        contextMenu->deleteLater();
    }
    if (!menu) return;

    contextMenu = menu;

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint)), this, SLOT(slotTreeMenu(const QPoint)));
}

void DTreeList::setRowIcon(QModelIndex *index, QIcon &icon)
{
    model()->setData(*index, QVariant(icon), DATA_ROW_ICON);
}

DStandartItemModel *DTreeList::sourceModel()
{
    return m_sourceModel;
}

void DTreeList::drawBranches(QPainter *painter, const QRect &rect, const QModelIndex& index) const
{
    QRect bRect(rect);
    bRect.setWidth(bRect.width()+m_rowIconSize.width());
    QTreeView::drawBranches(painter, bRect, index);
}

void DTreeList::focusInEvent(QFocusEvent */*event*/)
{
    this->setStyleSheet("QTreeView{border: 1px solid blue;}");
}

void DTreeList::focusOutEvent(QFocusEvent */*event*/)
{
    this->setStyleSheet("QTreeView{border: 1px solid transparent;}");
}

void DTreeList::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_PageDown: // scroll to right
        if (e->modifiers() & Qt::AltModifier)
        {
            QPoint tlPoint = rect().topRight();
            QModelIndex curIndex = indexAt(tlPoint);
            tlPoint.setX(tlPoint.x()+rect().width());
            QModelIndex nextIndex = indexAt(tlPoint);
            if (nextIndex.isValid())
                nextIndex = model()->index(curIndex.row(), nextIndex.column()-1, curIndex.parent());
            if (!nextIndex.isValid())
                nextIndex = model()->index(curIndex.row(), model()->columnCount()-1, curIndex.parent());
            if (nextIndex.isValid())
                scrollTo(nextIndex);
            return;
        }
        break;
    case Qt::Key_PageUp: // scroll to left
        if (e->modifiers() & Qt::AltModifier)
        {
            QPoint tlPoint = rect().topLeft();
            QModelIndex curIndex = indexAt(tlPoint);
            tlPoint.setX(tlPoint.x()-rect().width());
            QModelIndex prevIndex = indexAt(tlPoint);
            if (prevIndex.isValid())
                prevIndex = model()->index(curIndex.row(), prevIndex.column()+1, curIndex.parent());
            if (!prevIndex.isValid())
                prevIndex = model()->index(curIndex.row(), 0, curIndex.parent());
            if (prevIndex.isValid())
                scrollTo(prevIndex);
            return;
        }
        break;
    case Qt::Key_Right: // select next column
        if(e->modifiers() & Qt::ControlModifier)
        {
            QModelIndex curIndex = currentIndex();
            if (curIndex.column()==model()->columnCount()-1)
                return;
            clearSelection();
            QAbstractItemView::SelectionBehavior sb = selectionBehavior();
            setSelectionBehavior(QAbstractItemView::SelectItems);
            QModelIndex nextIndex = model()->index(curIndex.row(), curIndex.column()+1, curIndex.parent());
            if (nextIndex.isValid())
                setCurrentIndex(nextIndex);
            setSelectionBehavior(sb);
            return;
        }
        break;
    case Qt::Key_Left: // select prev column
        if(e->modifiers() & Qt::ControlModifier)
        {
            QModelIndex curIndex = currentIndex();
            if (curIndex.column()==0)
                return;
            clearSelection();
            QAbstractItemView::SelectionBehavior sb = selectionBehavior();
            setSelectionBehavior(QAbstractItemView::SelectItems);
            QModelIndex prevIndex = model()->index(curIndex.row(), curIndex.column()-1, curIndex.parent());
            if (prevIndex.isValid())
                setCurrentIndex(prevIndex);
            setSelectionBehavior(sb);
            return;
        }
        break;
    case Qt::Key_Plus: // sort
        if(e->modifiers() & Qt::ControlModifier)
        {
            if (selectionModel()->selectedIndexes().size() == 1)
                sortByColumn(currentIndex().column(), Qt::DescendingOrder);
            return;
        }
        break;
    case Qt::Key_Minus: // sort
        if(e->modifiers() & Qt::ControlModifier)
        {
            if (selectionModel()->selectedIndexes().size() == 1)
                sortByColumn(currentIndex().column(), Qt::AscendingOrder);
            return;
        }
        break;
    default:
        break;
    }

    QTreeView::keyPressEvent(e);
}

void DTreeList::slotTreeMenu(const QPoint &/*pos*/)
{
    if (!contextMenu) return;

    contextMenu->exec(QCursor::pos());
}

void DTreeList::slotHeaderMenu(const QPoint &/*pos*/)
{
    QMenu hMenu;
    QStandardItemModel* pModel = sourceModel();
    if (!pModel) return;
    for (int c=1; c<pModel->columnCount(); ++c)
    {
        QStandardItem *cItem = pModel->horizontalHeaderItem(c);
        if (!cItem) continue;
        QString cText = cItem->text();

        QAction *action = new QAction(cText);
        action->setCheckable(true);
        action->setChecked(!isColumnHidden(c));
        action->setData(c);
        connect(action, SIGNAL(triggered()), this, SLOT(headerMenuActionTriggerd()));
        hMenu.addAction(action);
    }

    hMenu.exec(QCursor::pos());
}

void DTreeList::headerMenuActionTriggerd()
{
    QObject *obj = sender();
    QAction *action = qobject_cast<QAction*>(obj);
    if (action && action->data().isValid())
    {
        int column = action->data().toInt();
        setColumnHidden(column, !action->isChecked());
    }
}

void DTreeList::setRowStyle(CMD_SET_STYLE cmd, QVariant param)
{
    QModelIndexList idx = selectionModel()->selectedIndexes();
    if (idx.size() == 0) return;

    QColor currentColor;
    QFont currentFont;

    if ((cmd == CELL_SET_FONT_COLOR || cmd == CELL_SET_BACKGROUND_COLOR))
    {
        if (param.isValid())
        {
            if (param.canConvert<QColor>())
            {
                currentColor = param.value<QColor>();
            }
        }
        else
        {
            QColorDialog colorDlg(this);
            colorDlg.setOption(QColorDialog::DontUseNativeDialog);
            if (colorDlg.exec() != QColorDialog::Accepted) return;
            currentColor = colorDlg.currentColor();
        }
    }
    else if (cmd == CELL_SET_FONT)
    {
        if (param.isValid())
        {
            if (param.canConvert<QFont>())
            {
                currentFont = param.value<QFont>();
            }
        }
        else
        {
            QVariant vFont = model()->data(idx[0],Qt::FontRole);
            QFont cFont = vFont.canConvert<QFont>() ? vFont.value<QFont>() : QFont();

            QFontDialog fontDlg(this);
            fontDlg.setOptions(QFontDialog::DontUseNativeDialog);
            fontDlg.setCurrentFont(cFont);
            if (fontDlg.exec() != QFontDialog::Accepted) return;
            currentFont = fontDlg.currentFont();
        }
    }

    for (QModelIndexList::iterator iCell=idx.begin(); iCell!=idx.end(); ++iCell)
    {
        switch (cmd) {
        case CELL_SET_FONT:
        {
            model()->setData(*iCell, currentFont, Qt::FontRole);
            break;
        }
        case CELL_SET_FONT_COLOR:
            model()->setData(*iCell, currentColor, Qt::ForegroundRole);
            break;
        case CELL_SET_BACKGROUND_COLOR:
            model()->setData(*iCell, currentColor, Qt::BackgroundRole);
            break;
        }
    }
}

void DTreeList::test()
{
    printf("DTreeList::test()\n");
}

void DTreeList::removeSelectedRows()
{
    int res = QMessageBox::warning(this,
                         tr("Deleting rows"),
                         tr("Delete selected rows?"),
                         QMessageBox::StandardButton::Ok|QMessageBox::StandardButton::No,
                         QMessageBox::StandardButton::No);

    if (res != QMessageBox::Ok) return;

    while(!selectionModel()->selectedIndexes().isEmpty()) {
        const QModelIndex idx = selectionModel()->selectedIndexes().first();
        model()->removeRow(idx.row(), idx.parent());
    }
}

void DTreeList::addMultiRows(bool isSubRow)
{
    QModelIndexList idx = selectionModel()->selectedRows();
    if (idx.size() > 1)
    {
        QMessageBox::warning(this,
                             tr("Error"),
                             tr("Select one row"),
                             QMessageBox::StandardButton::Ok,
                             QMessageBox::StandardButton::Ok);
        return;
    }


    QInputDialog *iDialog = new QInputDialog(this);
    iDialog->setInputMode(QInputDialog::IntInput);
    iDialog->setIntMinimum(1);
    iDialog->setIntMaximum(MAX_ROWS_FOR_ADD);
    iDialog->setLabelText(tr("Enter rows count")+QString(" (0-%1)").arg(MAX_ROWS_FOR_ADD));

    int rowCount = 0;
    if (iDialog->exec() == QDialog::Accepted)
    {
        rowCount = iDialog->intValue();
    }
    iDialog->deleteLater();

    if (rowCount == 0) return;

    QStandardItemModel *indexModel = sourceModel();
    if (!indexModel) return;
    QSortFilterProxyModel *proxy = dynamic_cast<QSortFilterProxyModel*>(model());
    if (!proxy) return;
    QModelIndex index = idx.size() == 0 ? rootIndex() : proxy->mapToSource(idx[0]);
    int newRowIndex = index.row()+1; // next before current
    int columnCount = model()->columnCount();
    QStandardItem *indexItem = indexModel->itemFromIndex(index);
    if (!isSubRow)
    {
        if (indexItem) indexItem = indexItem->parent();
        if(!indexItem) {
            indexItem = indexModel->invisibleRootItem();
            if (idx.size() == 0)
            {
                newRowIndex = indexModel->rowCount();
            }
        }
    }
    if (!indexItem) return;

    for (int r = 0; r < rowCount; ++r) {
        lastRowIndex++;
        QList<QStandardItem *> items;
        for (int c = 0; c < columnCount; ++c) {
            items.append(new QStandardItem(QString("Col%1 Row %2").arg(c+1).arg(lastRowIndex)));
        }

        if (isSubRow)
        {
            indexItem->appendRow(items);
        }
        else
        {
            indexItem->insertRow(newRowIndex + r, items);
        }
    }
}

void DTreeList::addMultiSubRows()
{
    QModelIndexList idx = selectionModel()->selectedRows();
    if (idx.size() == 0)
    {
        QMessageBox::warning(this,
                             tr("Error"),
                             tr("Select one row"),
                             QMessageBox::StandardButton::Ok,
                             QMessageBox::StandardButton::Ok);
        return;
    }

    return addMultiRows(true);
}

