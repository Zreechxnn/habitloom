#include "ConfigManager.h"
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QTextStream>
#include <fstream>

using json = nlohmann::json;

ConfigManager::ConfigManager(QObject *parent) : QObject(parent) {}

void ConfigManager::loadConfig(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning() << "Failed to open config file:" << filePath;
        return;
    }

    try
    {
        json data = json::parse(file.readAll().toStdString());
        brutalMode = data.value("brutal_mode", false);
        notificationInterval = data.value("notification_interval", 60);
        currentTheme = QString::fromStdString(data.value("current_theme", "nietzschean_rage"));
        sarcasmLevel = data.value("sarcasm_level", 2);
    }
    catch (const json::exception &e)
    {
        qCritical() << "JSON error:" << e.what();
    }
}

void ConfigManager::saveConfig(const QString &filePath)
{
    json data;
    data["brutal_mode"] = brutalMode;
    data["notification_interval"] = notificationInterval;
    data["current_theme"] = currentTheme.toStdString();
    data["sarcasm_level"] = sarcasmLevel;

    QDir().mkpath(QFileInfo(filePath).absolutePath());
    std::ofstream file(filePath.toStdString());
    if (file.is_open())
    {
        file << data.dump(4);
    }
    else
    {
        qWarning() << "Failed to save config to" << filePath;
    }
}