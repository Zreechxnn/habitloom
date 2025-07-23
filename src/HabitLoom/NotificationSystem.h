#ifndef NOTIFICATIONSYSTEM_H
#define NOTIFICATIONSYSTEM_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QTimer>
#include "SarcasmEngine.h"

class NotificationSystem : public QObject
{
    Q_OBJECT
public:
    explicit NotificationSystem(QObject *parent = nullptr);
    void setBrutalMode(bool brutalMode);
    void setInterval(int minutes);

public slots:
    void showRandomNotification();
    void showHabitResultNotification(bool isCompleted);

private:
    QSystemTrayIcon *trayIcon;
    QTimer *notificationTimer;
    SarcasmEngine sarcasmEngine;
};

#endif // NOTIFICATIONSYSTEM_H