#ifndef THEMEICONSMODEL_H
#define THEMEICONSMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <QIcon>

#include "icontheme.h"

/**
 * @brief The Model/View architecture-based model class providing theme icons model
 */
class ThemeIconsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    /**
     * @brief Data roles
     */
    enum Roles {
        IconInfoRole = Qt::UserRole /**< Icon information role */
    };

    /**
     * @brief Information about icon
     */
    struct IconInfo {
        QString name; /**< Icon name */
        QStringList sizes; /**< Icon sizes */
        QStringList contexts; /**< Icon contexts **/
        QStringList themes; /**< Icon themes **/
    };

    ThemeIconsModel(QHash<QString, IconTheme> themes, const QString &theme_name=QString(),
                    QObject *parent=nullptr);
    ThemeIconsModel(QObject *parent=nullptr);

    /**
     * @brief Returns number of items in this model
     * @param parent Parent index
     * @return Number of items
     */
    virtual int rowCount(const QModelIndex &parent=QModelIndex()) const override;

    /**
     * @brief Returns data with requested role
     * @param index Item index
     * @param role Data role
     * @return Requested data
     */
    virtual QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const override;

    /**
     * @brief Set themes served by this model
     * @param themes Themes
     * @param theme_name Current theme
     */
    void set_themes(const QHash<QString, IconTheme> &themes, const QString &theme_name=QString());
public slots:

    /**
     * @brief Set current theme (must be one of the htemes his model serves)
     * @param theme Theme name
     */
    void set_current_theme(QString theme);
protected:

    /**
     * @brief Return QIcon for the icon name
     * @param name Icon name
     * @return QIcon
     */
    QIcon icon_by_name(const QString &name) const;

    /**
     * @brief Returns the first theme that defines requested icon
     * @param name Icon name
     * @return Theme name
     */
    QString get_icon_theme(const QString &name) const;

    /**
     * @brief Get list of themes that define requested icon
     * @param name Icon name
     * @return List of themes (ordered from descendants to anchestors)
     */
    QStringList get_icon_theme_chain(const QString &name) const;

    QHash<QString, IconTheme> icon_themes; /**< Served icon themes */
    QList<QString> icon_names; /**< List of all icons of the current theme */
    QString selected_theme; /**< Current theme name */
    mutable QHash<QString, QIcon> icon_cache; /**< Cache of the icons */
};

Q_DECLARE_METATYPE(ThemeIconsModel::IconInfo)

#endif // THEMEICONSMODEL_H
