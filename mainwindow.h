#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "themeiconsmodel.h"
#include "icondelegate.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ThemeIconsModel * model;
    IconDelegate * view_delegate;
};

#endif // MAINWINDOW_H
