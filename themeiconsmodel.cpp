#include <QIcon>
#include <QSet>

#include <QDebug>

#include "themeiconsmodel.h"

ThemeIconsModel::ThemeIconsModel(QHash<QString, IconTheme> themes, const QString &theme_name,
                                 QObject *parent):
    QAbstractListModel(parent),
	icon_themes(std::move(themes))
{
	set_current_theme(theme_name.isNull() ? QIcon::themeName() : theme_name);
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
            if (icon_cache.contains(name))
                return icon_cache[name];
            QIcon icon(QIcon::fromTheme(name));
            icon_cache[name] = icon;
            return icon;
        }
        default:
            return QVariant();
	}
}

void ThemeIconsModel::set_current_theme(QString theme)
{
	if (!icon_themes.contains(theme) || theme == selected_theme) {
		return;
	}
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
