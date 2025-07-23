#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QCheckBox>
#include <QCalendarWidget>
#include <QPushButton>
#include <QStatusBar>
#include <QProgressBar>
#include <QVBoxLayout>      // <--- TAMBAHKAN
#include <QHBoxLayout>      // <--- TAMBAHKAN
#include <QComboBox>        // <--- TAMBAHKAN
#include <QSpinBox>         // <--- TAMBAHKAN
#include <QDialog>          // <--- TAMBAHKAN
#include <QDialogButtonBox> // <--- TAMBAHKAN
#include <QFormLayout>      // <--- TAMBAHKAN

#include "HabitLoom/HabitTracker.h"
#include "HabitLoom/SarcasmEngine.h"
#include "HabitLoom/NotificationSystem.h"
#include "HabitLoom/ThemeManager.h"
#include "HabitLoom/ConfigManager.h"
#include "AddHabitDialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onHabitToggled(bool checked);
    void onAddHabit();
    void onRemoveHabit();
    void onToggleBrutalMode();
    void updateStatistics();
    void applyTheme();
    void showSettings();

private:
    void setupUI();
    void loadHabits();
    void refreshHabitList();

    HabitTracker habitTracker;
    SarcasmEngine sarcasmEngine;
    NotificationSystem notificationSystem;
    ConfigManager configManager;

    // UI Components
    QWidget *centralWidget;
    QVBoxLayout *mainLayout; // <--- SEKARANG SEHARUSNYA TIDAK ERROR
    QListWidget *habitList;
    QCalendarWidget *calendar;
    QPushButton *addHabitButton;
    QPushButton *removeHabitButton;
    QPushButton *brutalModeButton;
    QPushButton *settingsButton;
    QProgressBar *progressBar;
    QStatusBar *statusBar;
};

#endif // MAINWINDOW_H