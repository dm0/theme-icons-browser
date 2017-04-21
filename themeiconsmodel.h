#ifndef THEMEICONSMODEL_H
#define THEMEICONSMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <QIcon>

#include "icontheme.h"
// TODO: Document
class ThemeIconsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ThemeIconsModel(QHash<QString, IconTheme> themes, const QString &theme_name=QString(),
                    QObject *parent=nullptr);
    ThemeIconsModel(QObject *parent=nullptr);
    virtual int rowCount(const QModelIndex &parent=QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const override;
    void set_themes(const QHash<QString, IconTheme> &themes, const QString &theme_name=QString());
public slots:
    void set_current_theme(QString theme);
protected:
    QIcon icon_by_name(const QString &name) const;

    QHash<QString, IconTheme> icon_themes;
    QList<QString> icon_names;
    QString selected_theme;
    mutable QHash<QString, QIcon> icon_cache;
};

#endif // THEMEICONSMODEL_H
