#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QString>
#include <QFile>
#include <QApplication>
#include <QPalette>

class ThemeManager
{
public:
    enum Theme
    {
        Kantian,
        NietzscheanRage,
        MinimalisPalsu
    };

    static void applyTheme(Theme theme);

private:
    static void applyKantian();
    static void applyNietzscheanRage();
    static void applyMinimalisPalsu();
};

#endif // THEMEMANAGER_H