#ifndef DTREELIST_H
#define DTREELIST_H

#include <QObject>
#include <QTreeView>
#include <QStandardItemModel>

class DStandartItemModel: public QStandardItemModel
{
    Q_OBJECT
public:
    explicit DStandartItemModel(QObject *parent = Q_NULLPTR);
    virtual ~DStandartItemModel();

    void setHorizontalHeaderItem(int column, const QString &text);
};

class DTreeList : public QTreeView
{
    Q_OBJECT
public:
    explicit DTreeList(QWidget *parent = Q_NULLPTR);
    virtual ~DTreeList();

    void setMenu(QMenu *const menu);

public Q_SLOTS:
    void removeSelectedRows();
    void slotTreeMenu(const QPoint &pos);

private:
    QMenu *contextMenu;
};

#endif // DTREELIST_H
