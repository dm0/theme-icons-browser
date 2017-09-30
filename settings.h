#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QSize>

class Settings : public QObject
{
    Q_OBJECT
public:
    enum ViewMode {Icons, List};
    Q_ENUM(ViewMode);
    explicit Settings(QObject *parent = 0);

    Q_PROPERTY(QStringList theme_pathes MEMBER m_theme_search_pathes NOTIFY theme_pathes_changed)
    Q_PROPERTY(ViewMode view_mode MEMBER m_view_mode NOTIFY view_mode_changed)
    Q_PROPERTY(QSize list_view_icon_size MEMBER m_list_view_icon_size
               NOTIFY list_view_icon_size_changed)
    Q_PROPERTY(QSize list_view_item_size MEMBER m_list_view_item_size
               NOTIFY list_view_item_size_changed)
    Q_PROPERTY(QSize icon_view_icon_size MEMBER m_icon_view_icon_size
               NOTIFY icon_view_icon_size_changed)
    Q_PROPERTY(QSize icon_view_item_size MEMBER m_icon_view_item_size
               NOTIFY icon_view_item_size_changed)

signals:
    void theme_pathes_changed(QStringList);
    void view_mode_changed(ViewMode);
    void list_view_icon_size_changed(QSize);
    void list_view_item_size_changed(QSize);
    void icon_view_icon_size_changed(QSize);
    void icon_view_item_size_changed(QSize);
protected:
    void load();

    QSettings * settings;

    QStringList m_theme_search_pathes;
    ViewMode m_view_mode;
    QSize m_list_view_icon_size;
    QSize m_list_view_item_size;
    QSize m_icon_view_icon_size;
    QSize m_icon_view_item_size;
};

#endif // SETTINGS_H
