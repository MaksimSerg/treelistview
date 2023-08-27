#ifndef DTREEDELEGATE_H
#define DTREEDELEGATE_H

#include <QItemDelegate>

class DTreeDelegateComboBox: public QItemDelegate
{
public:
    explicit DTreeDelegateComboBox(QObject *parent = Q_NULLPTR, QStringList items = QStringList()):
        QItemDelegate(parent), m_items(items) {}
    void setItems(QStringList &items) {m_items = items;}
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

private:
    QStringList m_items;
};


#endif // DTREEDELEGATE_H
