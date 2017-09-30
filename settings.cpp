#include "settings.h"

Settings::Settings(QObject *parent) :
    QObject(parent),
    settings(new QSettings(this))
{

}
