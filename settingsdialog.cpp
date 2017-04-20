#include <QItemEditorFactory>
#include <QFileDialog>

#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "directoryeditor.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog),
    settings(new QSettings(this)),
    model(new QStringListModel(this))
{
    ui->setupUi(this);
    QItemEditorFactory *factory = new QItemEditorFactory;

    QItemEditorCreatorBase *directory_editor_creator =
            new QStandardItemEditorCreator<DirectoryEditor>();

    factory->registerEditor(QVariant::String, directory_editor_creator);

    QItemEditorFactory::setDefaultFactory(factory);

    ui->listView->setModel(model);

}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::load_config()
{
    model->setStringList(settings->value("additional-theme-dirs").toStringList());
}

void SettingsDialog::open()
{
    load_config();
    QDialog::open();
}

int SettingsDialog::exec()
{
    load_config();
    return QDialog::exec();
}

void SettingsDialog::accept()
{
    settings->setValue("additional-theme-dirs", model->stringList());
    QDialog::accept();
}

void SettingsDialog::remove_selected_path()
{
    model->removeRow(ui->listView->selectionModel()->currentIndex().row());
}

void SettingsDialog::add_new_path()
{
    QString path = QFileDialog::getExistingDirectory(this, "Choose directory");
    if (path.isNull())
        return;
    int num_rows = model->rowCount();
    model->insertRow(num_rows);
    QModelIndex index = model->index(num_rows);
    model->setData(index, path);
    ui->listView->setCurrentIndex(index);
}
