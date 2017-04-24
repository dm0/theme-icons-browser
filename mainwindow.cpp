#include <QStyledItemDelegate>
#include <QSortFilterProxyModel>
#include <QLineEdit>

#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "icontheme.h"

#include <sys/resource.h>
#include <sys/time.h>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    settings(new QSettings(this))
{
    if (QIcon::themeName().isNull())
        QIcon::setThemeName("built-in-theme");
    ui->setupUi(this);

    default_theme_paths = QIcon::themeSearchPaths();
    IconTheme::add_themes_dirs(settings->value("additional-theme-dirs").toStringList());

    model = new ThemeIconsModel(this);
    QSortFilterProxyModel * proxy_model = new QSortFilterProxyModel(this);
    proxy_model->setSortCaseSensitivity(Qt::CaseInsensitive);
    proxy_model->setSourceModel(model);
    proxy_model->sort(0);
    proxy_model->setFilterCaseSensitivity(Qt::CaseInsensitive);
    ui->listView->setModel(proxy_model);
    view_delegate = new IconDelegate(ui->listView);
    view_delegate->set_size_hint({160, 128});
    ui->listView->setItemDelegate(view_delegate);

    QWidget * expander = new QWidget(this);
    expander->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);
    ui->mainToolBar->addWidget(expander);

    QLineEdit * filter_edit = new QLineEdit(this);
    filter_edit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    filter_edit->setClearButtonEnabled(true);
    filter_edit->addAction(QIcon::fromTheme("view-filter-symbolic"),
                           QLineEdit::LeadingPosition);
    connect(filter_edit, &QLineEdit::textChanged,
            proxy_model, &QSortFilterProxyModel::setFilterFixedString);
    ui->mainToolBar->addWidget(filter_edit);
    themes_combo = new QComboBox(this);
    connect(themes_combo, &QComboBox::currentTextChanged,
            model, &ThemeIconsModel::set_current_theme);
    ui->mainToolBar->addWidget(themes_combo);

    // following call changes current icon theme
    struct rusage before, after;
    getrusage(RUSAGE_SELF, &before);
    load_themes(QIcon::themeName());
    for (int i = 0, len = model->rowCount(); i < len; i++)
        model->data(model->index(i), Qt::DecorationRole);
    getrusage(RUSAGE_SELF, &after);
    double start_time = before.ru_utime.tv_sec + before.ru_utime.tv_usec * 1e-6;
    double end_time = after.ru_utime.tv_sec + after.ru_utime.tv_usec * 1e-6;
    std::cout << "time: " << end_time - start_time << std::endl;
    std::cout << "Memory:" << (after.ru_maxrss - before.ru_maxrss) << std::endl;
//    QMenu * view_type_menu = new QMenu(this);
//    view_type_menu
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show_settings()
{
    if (settings_dialog == nullptr)
        settings_dialog = new SettingsDialog(this);
    if (settings_dialog->exec() != QDialog::Accepted)
        return;
    IconTheme::set_themes_dirs(default_theme_paths);
    IconTheme::add_themes_dirs(settings->value("additional-theme-dirs").toStringList());
    load_themes(QIcon::themeName());
}

void MainWindow::load_themes(QString current_theme)
{
    QHash<QString, IconTheme> themes;
    QStringList theme_list = IconTheme::themes();
    theme_list.sort(Qt::CaseInsensitive);
    for (const QString& theme: theme_list) {
        qDebug() << "Loading: " << theme;
        themes.insert(theme, IconTheme(theme));
    }
    if (current_theme.isNull() || !theme_list.contains(current_theme)) {
        current_theme = theme_list.value(0);
    }
    model->set_themes(themes, current_theme);
    themes_combo->clear();
    themes_combo->addItems(theme_list);
    themes_combo->setCurrentText(current_theme);
}
