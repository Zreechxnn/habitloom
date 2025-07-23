#include "ThemeManager.h"

void ThemeManager::applyTheme(Theme theme)
{
    switch (theme)
    {
    case Kantian:
        applyKantian();
        break;
    case NietzscheanRage:
        applyNietzscheanRage();
        break;
    case MinimalisPalsu:
        applyMinimalisPalsu();
        break;
    }
}

void ThemeManager::applyKantian()
{
    QFile file(":/styles/kantian.qss");
    if (file.open(QFile::ReadOnly))
    {
        QString styleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(styleSheet);
    }
}

void ThemeManager::applyNietzscheanRage()
{
    QFile file(":/styles/nietzschean_rage.qss");
    if (file.open(QFile::ReadOnly))
    {
        QString styleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(styleSheet);
    }
}

void ThemeManager::applyMinimalisPalsu()
{
    QFile file(":/styles/minimalis_palsu.qss");
    if (file.open(QFile::ReadOnly))
    {
        QString styleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(styleSheet);
    }
}