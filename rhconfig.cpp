#include "rhconfig.h"

RHConfig::RHConfig()
{

}

QString RHConfig::asPhotoPath(const QString &filename)
{
    return QStringLiteral("testicons/") + filename;
}
