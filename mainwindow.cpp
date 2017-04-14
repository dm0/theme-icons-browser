#include <QStyledItemDelegate>
#include <QSortFilterProxyModel>
#include <QLineEdit>

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
    for (const QString& theme: IconTheme::themes()) {
        qDebug() << "Loading: " << theme;
        themes.insert(theme, IconTheme(theme));
    }
    model = new ThemeIconsModel(themes, QString(), this);
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
//    QMenu * view_type_menu = new QMenu(this);
//    view_type_menu
}

MainWindow::~MainWindow()
{
    delete ui;
}
