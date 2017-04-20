#ifndef ICONTHEME_H
#define ICONTHEME_H

#include <QString>
#include <QStringList>
#include <QHash>
#include <QSet>
#include <QVector>

/**
 * @brief The IconTheme class contains information about single icon theme
 */
class IconTheme {

public:

    /**
     * @brief The Directory struct stores information about single icons directory from theme
     */
    struct Directory {
        int size; /**< icon size */
        int scale; /**< icon scale */
        QString context; /**< icon context */
        QString type; /**< type of icon sizes: Fixed, Scalable and Threshold */
        int max_size; /**< max size of Scalable icon */
        int min_size; /**< min size of Scalable icon */
        int threshold; /**< Threshold of a "Threshold" type icon */
        QString path; /**< path relative to theme root */
    };

    IconTheme(const QString &theme_name=QString());
    /**
     * @brief Parent theme name
     * @return Parent theme name (can be Null)
     */
    const QStringList & parents() const { return parent_themes; }

    /**
     * @brief Returns mapping of theme icons names to Directory indices.
     *
     * For each icon name in the mapping there is a set of directory indices. Each index is an
     * index of Directory object in the vector returned by the `dirs()` method.
     * @return Icon names to Directory indices
     */
    const QHash<QString, QSet<uint>> & icons() const { return theme_icons; }

    /**
     * @brief Return list of directories
     * @return list of theme search directories
     */
    const QVector<Directory> & dirs() const { return theme_dirs; }

    /**
     * @brief Returns list of installed icon themes
     * @return List of installed icon themes
     */
    static QStringList themes();

    /**
     * @brief Add theme search path
     * @param path Path to themes directory
     */
    static void add_themes_dir(const QString& path);

    /**
     * @brief Add several search paths at once
     * @param paths Additional serach paths
     */
    static void add_themes_dirs(const QStringList& paths);

    /**
     * @brief Set theme search paths
     * @param paths List of search paths
     */
    static void set_themes_dirs(const QStringList& paths);

protected:
    QStringList parent_themes; /**< parent theme name */
    QString theme_name; /**< theme name (directory name) */
    QString display_name; /**< theme display name */
    QString base_path; /**< path to the theme directory */
    QVector<Directory> theme_dirs; /**< theme directories */
    QHash<QString, QSet<uint>> theme_icons; /**< theme icons (names) to directories mapping */
    static QStringList base_dirs; /**< base directories */
};

#endif // ICONTHEME_H
