#ifndef THEMEICONSMODEL_H
#define THEMEICONSMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <QIcon>

#include "icontheme.h"

class ThemeIconsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ThemeIconsModel(QHash<QString, IconTheme> themes, const QString &theme_name=QString(),
                    QObject *parent=nullptr);
    virtual int rowCount(const QModelIndex &parent=QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const override;
    // TODO: set new themes
    // TODO: set current theme
protected:
    QHash<QString, IconTheme> icon_themes;
    QList<QString> icon_names;
    QString selected_theme;
    mutable QHash<QString, QIcon> icon_cache;
};

#endif // THEMEICONSMODEL_H
