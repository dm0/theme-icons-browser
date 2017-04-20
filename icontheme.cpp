#include <QtGlobal>
#include <QDir>
#include <QFileInfo>
#include <QSettings>
#include <QDebug>
#include <QIcon>

#include "icontheme.h"

QStringList IconTheme::base_dirs = QIcon::themeSearchPaths();

IconTheme::IconTheme(const QString &theme_name): theme_name(theme_name)
{
    if (theme_name.isNull()) {
        return;
    }
    for (const QString &dir: base_dirs) {
        if (!QFileInfo::exists(QString("%1/%2/index.theme").arg(dir).arg(theme_name))) {
            continue;
        }
        base_path = dir + "/" + theme_name;
        break;
    }
    // theme directory not found or doesn't contain index.theme file
    if (base_path.isNull()) {
        qDebug() << "index.theme not found";
        return;
    }
    QSettings theme_index(base_path + "/index.theme", QSettings::IniFormat);
    theme_index.beginGroup("Icon Theme");
    display_name = theme_index.value("Name").toString();
    parent_themes = theme_index.value("Inherits").toStringList();
    QStringList dir_list = theme_index.value("Directories").toStringList();
    theme_dirs.reserve(dir_list.size());
    for (const QString &dir: dir_list) {
        theme_index.beginGroup(dir);
        int size = theme_index.value("Size", 0).toInt();
        theme_dirs.append(Directory{
            size,
            theme_index.value("Scale", 1).toInt(),
            theme_index.value("Context", "").toString(),
            theme_index.value("Type", "Threshold").toString(),
            theme_index.value("MaxSize", size).toInt(),
            theme_index.value("MinSize", size).toInt(),
            theme_index.value("Threshold", 2).toInt(),
            dir
        });
        theme_index.endGroup();
    }
    // load icons
    for (int i = 0, len = theme_dirs.size(); i < len; i++) {
        QDir dir(base_path + "/" + theme_dirs[i].path);
        for (const QFileInfo &icon: dir.entryInfoList({"*.png", "*.svg", "*.xpm"}, QDir::Files | QDir::Readable)) {
            QString icon_name = icon.completeBaseName();
            theme_icons[icon_name] += static_cast<uint>(i);
        }
    }
}

QStringList IconTheme::themes()
{
    QSet<QString> themes;
    for (QDir dir: base_dirs) {
        // skip embedded themes
        if (dir.path().startsWith(':'))
            continue;
        for (const QString& theme: dir.entryList(QDir::Dirs | QDir::Readable |
                                                 QDir::NoDotAndDotDot))
        {
            if (!QFileInfo::exists(dir.filePath(theme + "/index.theme")))
                continue;
            themes += theme;
        }
    }
    return themes.toList();
}

void IconTheme::add_themes_dir(const QString &path)
{
    base_dirs.append(path);
    QIcon::setThemeSearchPaths(base_dirs);
}

void IconTheme::add_themes_dirs(const QStringList &paths)
{
    base_dirs.append(paths);
    QIcon::setThemeSearchPaths(base_dirs);
}

void IconTheme::set_themes_dirs(const QStringList &paths)
{
    base_dirs = paths;
    QIcon::setThemeSearchPaths(base_dirs);
}


