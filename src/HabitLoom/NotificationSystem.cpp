#include "NotificationSystem.h"

NotificationSystem::NotificationSystem(QObject *parent) : QObject(parent)
{
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/icons/app_icon.png"));
    trayIcon->show();

    notificationTimer = new QTimer(this);
    connect(notificationTimer, &QTimer::timeout, this, &NotificationSystem::showRandomNotification);
    notificationTimer->start(60 * 60 * 1000); // Default: setiap jam
}

void NotificationSystem::setBrutalMode(bool brutalMode)
{
    sarcasmEngine.setBrutalMode(brutalMode);
}

void NotificationSystem::setInterval(int minutes)
{
    notificationTimer->setInterval(minutes * 60 * 1000);
}

void NotificationSystem::showRandomNotification()
{
    QString message = sarcasmEngine.getRandomNotification();
    trayIcon->showMessage("HabitLoom", message);
}

void NotificationSystem::showHabitResultNotification(bool isCompleted)
{
    QString message = isCompleted ? sarcasmEngine.getRewardMessage() : sarcasmEngine.getPunishmentMessage();
    trayIcon->showMessage("HabitLoom", message);
}