#ifndef HABITTRACKER_H
#define HABITTRACKER_H

#include <QObject>
#include <QVector>
#include <QDate>
#include "../nlohmann/json.hpp"

struct Habit
{
    int id;
    QString name;
    QString description;
    QVector<bool> weeklyProgress;
};

class HabitTracker : public QObject
{
    Q_OBJECT
public:
    explicit HabitTracker(QObject *parent = nullptr);

    void loadHabits(const QString &filePath);
    void saveHabits(const QString &filePath);
    void addHabit(const Habit &habit);
    void removeHabit(int id);
    void updateHabitProgress(int habitId, int dayIndex, bool completed);

    const QVector<Habit> &getHabits() const { return habits; }
    Habit getHabit(int id) const;
    double calculateWeeklyCompletion() const;
    int getCurrentStreak() const { return currentStreak; }
    int getLongestStreak() const { return longestStreak; }

signals:
    void habitsUpdated();

private:
    QVector<Habit> habits;
    int currentStreak = 0;
    int longestStreak = 0;
    double completionRate = 0.0;
};

#endif // HABITTRACKER_H