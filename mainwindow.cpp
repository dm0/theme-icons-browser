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
}

MainWindow::~MainWindow()
{
    delete ui;
}
