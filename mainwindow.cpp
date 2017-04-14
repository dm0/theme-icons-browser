#include <QStyledItemDelegate>
#include <QSortFilterProxyModel>
#include <QLineEdit>
#include <QComboBox>

#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "icontheme.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QHash<QString, IconTheme> themes;
	QStringList theme_list = IconTheme::themes();
	theme_list.sort(Qt::CaseInsensitive);
	for (const QString& theme: theme_list) {
        qDebug() << "Loading: " << theme;
        themes.insert(theme, IconTheme(theme));
    }
	QString current_theme = QIcon::themeName();
	if (current_theme.isNull()) {
		current_theme = theme_list[0];
		QIcon::setThemeName(current_theme);
	}
	model = new ThemeIconsModel(themes, current_theme, this);
    QSortFilterProxyModel * proxy_model = new QSortFilterProxyModel(this);
    proxy_model->setSortCaseSensitivity(Qt::CaseInsensitive);
    proxy_model->setSourceModel(model);
    proxy_model->sort(0);
	ui->listView->setModel(proxy_model);
    view_delegate = new IconDelegate(ui->listView);
    view_delegate->set_size_hint({160, 128});
    ui->listView->setItemDelegate(view_delegate);
    QLineEdit * filter_edit = new QLineEdit(this);
    connect(filter_edit, &QLineEdit::textChanged,
            proxy_model, &QSortFilterProxyModel::setFilterFixedString);
    ui->mainToolBar->addWidget(filter_edit);
	QComboBox * themes_combo = new QComboBox(this);
	themes_combo->addItems(theme_list);
	themes_combo->setCurrentText(current_theme);
	connect(themes_combo, &QComboBox::currentTextChanged,
			model, &ThemeIconsModel::set_current_theme);
	ui->mainToolBar->addWidget(themes_combo);
//    QMenu * view_type_menu = new QMenu(this);
//    view_type_menu
}

MainWindow::~MainWindow()
{
    delete ui;
}
