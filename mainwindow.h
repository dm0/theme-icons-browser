#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QComboBox>
#include <QItemSelection>


#include "themeiconsmodel.h"
#include "icondelegate.h"
#include "settingsdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void show_settings();

protected:
    void load_themes(QString current_theme);
    void selection_changed(const QItemSelection &current, const QItemSelection &prev);

private:
    Ui::MainWindow *ui;
    ThemeIconsModel * model;
    IconDelegate * view_delegate;
    SettingsDialog * settings_dialog = nullptr;
    QSettings * settings;
    QStringList default_theme_paths;
    QComboBox * themes_combo;
};

#endif // MAINWINDOW_H
