#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QStringListModel>

// TODO: document

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SettingsDialog(QWidget *parent = 0);
	~SettingsDialog();
    virtual void open() override;
    virtual int exec() override;
    virtual void accept() override;

public slots:
    void remove_selected_path();
    void add_new_path();

protected:
    void load_config();

private:
	Ui::SettingsDialog *ui;
    QSettings * settings;
    QStringListModel * model;
};

#endif // SETTINGSDIALOG_H
