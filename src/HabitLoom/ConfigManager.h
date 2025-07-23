#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QObject>
#include "../nlohmann/json.hpp"

class ConfigManager : public QObject
{
    Q_OBJECT
public:
    explicit ConfigManager(QObject *parent = nullptr);

    void loadConfig(const QString &filePath);
    void saveConfig(const QString &filePath);

    bool getBrutalMode() const { return brutalMode; }
    int getNotificationInterval() const { return notificationInterval; }
    QString getCurrentTheme() const { return currentTheme; }
    int getSarcasmLevel() const { return sarcasmLevel; }

    void setBrutalMode(bool mode) { brutalMode = mode; }
    void setNotificationInterval(int minutes) { notificationInterval = minutes; }
    void setCurrentTheme(const QString &theme) { currentTheme = theme; }
    void setSarcasmLevel(int level) { sarcasmLevel = level; }

private:
    bool brutalMode = false;
    int notificationInterval = 60; // minutes
    QString currentTheme = "nietzschean_rage";
    int sarcasmLevel = 2;
};

#endif // CONFIGMANAGER_H