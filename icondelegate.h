#ifndef ICONDELEGATE_H
#define ICONDELEGATE_H

#include <QStyledItemDelegate>

class IconDelegate : public QStyledItemDelegate
{
//    Q_OBJECT
public:
    IconDelegate(QObject *parent=nullptr);
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // ICONDELEGATE_H
