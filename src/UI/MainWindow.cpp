#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFile>
#include <QDate>
#include <QMessageBox>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QComboBox>
#include <QSpinBox>
#include <QFormLayout>
#include <QDialogButtonBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // Load config
    configManager.loadConfig("data/config.json");

    // Apply theme
    if (configManager.getCurrentTheme() == "kantian")
    {
        ThemeManager::applyTheme(ThemeManager::Kantian);
    }
    else if (configManager.getCurrentTheme() == "minimalis_palsu")
    {
        ThemeManager::applyTheme(ThemeManager::MinimalisPalsu);
    }
    else
    {
        ThemeManager::applyTheme(ThemeManager::NietzscheanRage);
    }

    // Setup sarcasm engine
    sarcasmEngine.setBrutalMode(configManager.getBrutalMode());
    notificationSystem.setBrutalMode(configManager.getBrutalMode());
    notificationSystem.setInterval(configManager.getNotificationInterval());

    setupUI();
    loadHabits();

    connect(&habitTracker, &HabitTracker::habitsUpdated, this, &MainWindow::refreshHabitList);
    connect(&habitTracker, &HabitTracker::habitsUpdated, this, &MainWindow::updateStatistics);
}

MainWindow::~MainWindow()
{
    configManager.saveConfig("data/config.json");
}

void MainWindow::setupUI()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    mainLayout = new QVBoxLayout(centralWidget);

    // Menu bar
    QMenuBar *menuBar = new QMenuBar();
    QMenu *settingsMenu = menuBar->addMenu("Pengaturan");
    QAction *themeAction = settingsMenu->addAction("Ganti Tema");
    connect(themeAction, &QAction::triggered, this, &MainWindow::showSettings);
    setMenuBar(menuBar);

    // Calendar
    calendar = new QCalendarWidget();
    mainLayout->addWidget(calendar);

    // Habit List
    habitList = new QListWidget();
    mainLayout->addWidget(new QLabel("Kebiasaan Harian:"));
    mainLayout->addWidget(habitList);

    // Progress bar
    progressBar = new QProgressBar();
    progressBar->setTextVisible(true);
    progressBar->setFormat("%p% Tercapai");
    mainLayout->addWidget(progressBar);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    addHabitButton = new QPushButton("Tambah Habit");
    removeHabitButton = new QPushButton("Hapus Habit");
    brutalModeButton = new QPushButton(configManager.getBrutalMode() ? "Mode Sarkasme: ON" : "Mode Sarkasme: OFF");
    settingsButton = new QPushButton("Pengaturan");

    buttonLayout->addWidget(addHabitButton);
    buttonLayout->addWidget(removeHabitButton);
    buttonLayout->addWidget(brutalModeButton);
    buttonLayout->addWidget(settingsButton);
    mainLayout->addLayout(buttonLayout);

    // Status Bar
    statusBar = new QStatusBar();
    setStatusBar(statusBar);

    // Connections
    connect(addHabitButton, &QPushButton::clicked, this, &MainWindow::onAddHabit);
    connect(removeHabitButton, &QPushButton::clicked, this, &MainWindow::onRemoveHabit);
    connect(brutalModeButton, &QPushButton::clicked, this, &MainWindow::onToggleBrutalMode);
    connect(settingsButton, &QPushButton::clicked, this, &MainWindow::showSettings);
}

void MainWindow::loadHabits()
{
    habitTracker.loadHabits("data/habits.json");
    refreshHabitList();
    updateStatistics();
}

void MainWindow::refreshHabitList()
{
    habitList->clear();

    for (const Habit &habit : habitTracker.getHabits())
    {
        QListWidgetItem *item = new QListWidgetItem();
        QCheckBox *cb = new QCheckBox(habit.name + " - " + habit.description);
        cb->setProperty("habitId", habit.id);

        // Set checked for today
        int dayOfWeek = QDate::currentDate().dayOfWeek() - 1; // Monday=0
        if (dayOfWeek < habit.weeklyProgress.size())
        {
            cb->setChecked(habit.weeklyProgress[dayOfWeek]);
        }

        connect(cb, &QCheckBox::toggled, this, &MainWindow::onHabitToggled);
        habitList->addItem(item);
        habitList->setItemWidget(item, cb);
    }
}

void MainWindow::onHabitToggled(bool checked)
{
    QCheckBox *cb = qobject_cast<QCheckBox *>(sender());
    if (!cb)
        return;

    int habitId = cb->property("habitId").toInt();
    int dayOfWeek = QDate::currentDate().dayOfWeek() - 1; // Monday=0
    habitTracker.updateHabitProgress(habitId, dayOfWeek, checked);
    notificationSystem.showHabitResultNotification(checked);
}

void MainWindow::onAddHabit()
{
    AddHabitDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        Habit newHabit;
        newHabit.id = QDateTime::currentSecsSinceEpoch(); // Simple unique ID
        newHabit.name = dialog.getName();
        newHabit.description = dialog.getDescription();
        newHabit.weeklyProgress = QVector<bool>(7, false);

        habitTracker.addHabit(newHabit);
    }
}

void MainWindow::onRemoveHabit()
{
    if (habitList->currentItem())
    {
        QCheckBox *cb = qobject_cast<QCheckBox *>(habitList->itemWidget(habitList->currentItem()));
        if (cb)
        {
            int habitId = cb->property("habitId").toInt();
            habitTracker.removeHabit(habitId);
        }
    }
}

void MainWindow::onToggleBrutalMode()
{
    bool brutalMode = !configManager.getBrutalMode();
    configManager.setBrutalMode(brutalMode);
    sarcasmEngine.setBrutalMode(brutalMode);
    notificationSystem.setBrutalMode(brutalMode);
    brutalModeButton->setText(brutalMode ? "Mode Sarkasme: ON" : "Mode Sarkasme: OFF");
}

void MainWindow::updateStatistics()
{
    double progress = habitTracker.calculateWeeklyCompletion();
    progressBar->setValue(static_cast<int>(progress * 100));

    QString message = QString("Statistik: Streak saat ini %1 hari | Streak terpanjang %2 hari - %3")
                          .arg(habitTracker.getCurrentStreak())
                          .arg(habitTracker.getLongestStreak())
                          .arg(progress > 0.5 ? sarcasmEngine.getRewardMessage() : sarcasmEngine.getPunishmentMessage());

    statusBar->showMessage(message);
}

void MainWindow::showSettings()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Pengaturan");
    QVBoxLayout layout(&dialog);

    // Theme selection
    QComboBox themeCombo; // <--- DEKLARASI BENAR
    themeCombo.addItem("Kantian", "kantian");
    themeCombo.addItem("Nietzschean Rage", "nietzschean_rage");
    themeCombo.addItem("Minimalis Palsu", "minimalis_palsu");

    // Set current theme
    QString currentTheme = configManager.getCurrentTheme();
    for (int i = 0; i < themeCombo.count(); ++i)
    {
        if (themeCombo.itemData(i).toString() == currentTheme)
        {
            themeCombo.setCurrentIndex(i);
            break;
        }
    }

    // Notification interval
    QSpinBox intervalSpin; // <--- DEKLARASI BENAR
    intervalSpin.setRange(15, 240);
    intervalSpin.setValue(configManager.getNotificationInterval());
    intervalSpin.setSuffix(" menit");

    // Sarcasm level
    QSlider sarcasmSlider(Qt::Horizontal);
    sarcasmSlider.setRange(1, 3);
    sarcasmSlider.setValue(configManager.getSarcasmLevel());

    QFormLayout form;
    form.addRow("Tema:", &themeCombo);
    form.addRow("Interval Notifikasi:", &intervalSpin);
    form.addRow("Tingkat Sarkasme:", &sarcasmSlider);

    QDialogButtonBox buttons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(&buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    layout.addLayout(&form);
    layout.addWidget(&buttons);

    if (dialog.exec() == QDialog::Accepted)
    {
        configManager.setCurrentTheme(themeCombo.currentData().toString());
        configManager.setNotificationInterval(intervalSpin.value());
        configManager.setSarcasmLevel(sarcasmSlider.value());

        applyTheme();
        notificationSystem.setInterval(configManager.getNotificationInterval());
        sarcasmEngine.setSarcasmLevel(configManager.getSarcasmLevel());
    }
}

void MainWindow::applyTheme()
{
    if (configManager.getCurrentTheme() == "kantian")
    {
        ThemeManager::applyTheme(ThemeManager::Kantian);
    }
    else if (configManager.getCurrentTheme() == "minimalis_palsu")
    {
        ThemeManager::applyTheme(ThemeManager::MinimalisPalsu);
    }
    else
    {
        ThemeManager::applyTheme(ThemeManager::NietzscheanRage);
    }
}