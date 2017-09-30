#include <QIcon>
#include <QSet>
#include <QDir>

#include <QDebug>

#include "themeiconsmodel.h"

ThemeIconsModel::ThemeIconsModel(QHash<QString, IconTheme> themes, const QString &theme_name,
                                 QObject *parent):
    QAbstractListModel(parent),
    icon_themes(std::move(themes))
{
    set_current_theme(theme_name.isNull() ? QIcon::themeName() : theme_name);
}

ThemeIconsModel::ThemeIconsModel(QObject *parent): QAbstractListModel(parent)
{

}

int ThemeIconsModel::rowCount(const QModelIndex &) const
{
    return icon_names.size();
}

QVariant ThemeIconsModel::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    if (row < 0 || row >= icon_names.size() || index.column() != 0) {
        return QVariant();
    }
    switch(role) {
        case Qt::DisplayRole:
        case Qt::StatusTipRole:
        case Qt::ToolTipRole:
            return icon_names.at(row);
        case Qt::DecorationRole: {
            const QString &name = icon_names.at(row);
            // TODO: implement cache with limited amount of memory
            // TODO: implement async loading
            if (icon_cache.contains(name))
                return icon_cache[name];
            QIcon icon = icon_by_name(name);
            icon_cache[name] = icon;
            return icon;
        }
        default:
            return QVariant();
    }
}

void ThemeIconsModel::set_themes(const QHash<QString, IconTheme> &themes, const QString &theme_name)
{
    icon_themes=themes;
    set_current_theme(theme_name.isNull() ? QIcon::themeName() : theme_name);
}

void ThemeIconsModel::set_current_theme(QString theme)
{
    if (!icon_themes.contains(theme) || theme == selected_theme)
        return;

    beginResetModel();
    selected_theme = theme;
    icon_cache.clear();
    // build list of icons from selected theme and parent themes
    QSet<QString> theme_icons;
    QStringList theme_chain{selected_theme};
    for (int i = 0; i < theme_chain.size(); i++) {
        const IconTheme &theme = icon_themes[theme_chain[i]];
        theme_chain.append(theme.parents());
        theme_icons.unite(QSet<QString>::fromList(theme.icons().keys()));
    }
    icon_names = theme_icons.toList();
    qDebug() << "selected_theme: " << selected_theme;
    endResetModel();
}

QIcon ThemeIconsModel::icon_by_name(const QString &name) const
{
    static_assert(IconTheme::FileExtension::PNG == 0, "IconTheme::FileExtension::PNG != 0");
    static_assert(IconTheme::FileExtension::SVG == 1, "IconTheme::FileExtension::SVG != 1");
    static_assert(IconTheme::FileExtension::XPM == 2, "IconTheme::FileExtension::XPM != 2");
    static const char * extensions[IconTheme::FileExtension::LENGTH] = {
        "png",
        "svg",
        "xpm"
    };

    QStringList theme_chain{selected_theme};
    for (int i = 0; i < theme_chain.size(); i++) {
        const IconTheme &theme = icon_themes[theme_chain[i]];
        theme_chain.append(theme.parents());
        if (!theme.icons().contains(name))
            continue;
        QIcon icon;
        const QVector<IconTheme::Directory> &dirs = theme.dirs();
        // load files
        for (const IconTheme::IconInfo& icon_info: theme.icons()[name]) {
            QString file_path = QString("%1/%2/%3.%4")
                    .arg(theme.path())
                    .arg(dirs[icon_info.first].path)
                    .arg(name)
                    .arg(extensions[icon_info.second]);
            icon.addFile(file_path);
        }
        return icon;
    }
    qDebug() << "Icon " << name << " not found";
    return QIcon();
}
