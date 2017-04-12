#include <QStyledItemDelegate>

#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "icontheme.h"
#include "icondelegate.h"

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
    ui->listView->setModel(model);
    IconDelegate * delegate = new IconDelegate(ui->listView);
    ui->listView->setItemDelegate(delegate);
}

MainWindow::~MainWindow()
{
    delete ui;
}
