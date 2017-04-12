#include <QDebug>

#include "icondelegate.h"

IconDelegate::IconDelegate(QObject *parent): QStyledItemDelegate(parent)
{

}

QSize IconDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    qDebug() << index.data(Qt::DisplayRole).toString() << "Size: " << size;
    return size;
}
