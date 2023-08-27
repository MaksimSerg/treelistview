#ifndef DTREELIST_H
#define DTREELIST_H

#include <QObject>
#include <QTreeView>
#include <QStandardItemModel>
#include <QItemDelegate>
#include <QSortFilterProxyModel>

#include "dstandartitemmodel.h"
#include "dverticalheaderitemdelegate.h"
#include "dsortfilterproxymodel.h"


class DTreeList : public QTreeView
{
    Q_OBJECT

public:
    enum {
        DATA_ROW_ICON = Qt::UserRole+1001
    };

    explicit DTreeList(QWidget *parent = Q_NULLPTR);
    virtual ~DTreeList();

    void setContextMenu(QMenu *const menu);
    void setRowIcon(QModelIndex *index, QIcon &icon);
    DStandartItemModel *sourceModel();

protected:
    void drawBranches(QPainter *painter, const QRect &rect, const QModelIndex &index) const override;
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    enum CMD_SET_STYLE
    {
        CELL_SET_FONT,
        CELL_SET_FONT_COLOR,
        CELL_SET_BACKGROUND_COLOR
    };

public Q_SLOTS:
    void test();
    void setRowStyle(CMD_SET_STYLE cmd, QVariant param=QVariant());
    void removeSelectedRows();
    void addMultiRows(bool isSubRow=false);
    void addMultiSubRows();
    void slotTreeMenu(const QPoint &pos);
    void slotHeaderMenu(const QPoint &pos);
    void headerMenuActionTriggerd();

public:
    int lastRowIndex;

private:
    static const int MAX_ROWS_FOR_ADD = 10000;
    QSize m_rowIconSize;
    QMenu *contextMenu;
    DStandartItemModel *m_sourceModel;
};

#endif // DTREELIST_H
