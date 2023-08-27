#include "dtreedelegate.h"

#include <QComboBox>
#include <QCheckBox>
#include <QStyleOptionViewItem>


// ComoboBox
QWidget *DTreeDelegateComboBox::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/) const
{
//    check show delegate
//    if (false) {
//        return QItemDelegate::createEditor(parent, option, index);
//    }
    return new QComboBox(parent);
}

void DTreeDelegateComboBox::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox* comboBox = qobject_cast<QComboBox*>(editor);
    if (!comboBox) {
        return QItemDelegate::setEditorData(editor, index);
    }
    QStringList options = index.data(Qt::UserRole).toStringList();
    comboBox->addItems(m_items);
    QString value = index.data().toString();
    int current = m_items.indexOf(value);
    if (current > -1) {
        comboBox->setCurrentIndex(current);
    }
    comboBox->showPopup();
}

void DTreeDelegateComboBox::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox* comboBox = qobject_cast<QComboBox*>(editor);
    if (!comboBox) {
        return QItemDelegate::setModelData(editor, model, index);
    }
    model->setData(index, comboBox->currentText());
}

