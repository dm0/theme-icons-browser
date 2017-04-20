#include <QIcon>
#include <QFileDialog>
#include <QAction>

#include "directoryeditor.h"

DirectoryEditor::DirectoryEditor(QWidget *parent): QLineEdit(parent)
{
    QAction * browse_action = addAction(QIcon::fromTheme("folder-open"),
                                        QLineEdit::TrailingPosition);
    connect(browse_action, &QAction::triggered, this, &DirectoryEditor::browse);
}

QString DirectoryEditor::directory() const
{
    return text();
}

void DirectoryEditor::set_directory(const QString &directory)
{
    setText(directory);
}

void DirectoryEditor::browse()
{
    QString directory = QFileDialog::getExistingDirectory(
                this, "Choose directory", text());
    if (directory.isEmpty()) {
        return;
    }
    setText(directory);
}
