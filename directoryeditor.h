#ifndef DIRECTORYEDITOR_H
#define DIRECTORYEDITOR_H

#include <QObject>
#include <QLineEdit>
#include <QDir>

class DirectoryEditor : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(QString directory READ directory WRITE set_directory USER true)
public:
    DirectoryEditor(QWidget * parent);
    QString directory() const;
    void set_directory(const QString& directory);
protected:
    void browse();
};

#endif // DIRECTORYEDITOR_H
