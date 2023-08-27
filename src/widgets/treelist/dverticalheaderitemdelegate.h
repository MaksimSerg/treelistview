#ifndef DVERTICALHEADERITEMDELEGATE_H
#define DVERTICALHEADERITEMDELEGATE_H

#include <QObject>
#include <QItemDelegate>

class DVerticalHeaderItemDelegate : public QItemDelegate
{
    Q_OBJECT

    public:
        DVerticalHeaderItemDelegate( QObject *parent) = delete;
        DVerticalHeaderItemDelegate( QObject *parent, QSize &rowIconSize);
        void paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const;

    private:
        QSize m_iconSize;
};

#endif // DVERTICALHEADERITEMDELEGATE_H
