#include "HabitTracker.h"
#include <fstream>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <algorithm>

using json = nlohmann::json;

HabitTracker::HabitTracker(QObject *parent) : QObject(parent) {}

void HabitTracker::loadHabits(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning() << "Failed to open habits file:" << filePath;
        return;
    }

    try
    {
        json data = json::parse(file.readAll().toStdString());
        habits.clear();

        // Parse habits
        for (const auto &item : data["habits"])
        {
            Habit habit;
            habit.id = item["id"];
            habit.name = QString::fromStdString(item["name"]);
            habit.description = QString::fromStdString(item["description"]);

            for (bool day : item["weekly_progress"])
            {
                habit.weeklyProgress.append(day);
            }

            habits.append(habit);
        }

        // Parse statistics
        if (data.contains("statistics"))
        {
            json stats = data["statistics"];
            currentStreak = stats.value("current_streak", 0);
            longestStreak = stats.value("longest_streak", 0);
            completionRate = stats.value("completion_rate", 0.0);
        }

        emit habitsUpdated();
    }
    catch (const json::exception &e)
    {
        qCritical() << "JSON error:" << e.what();
    }
}

void HabitTracker::saveHabits(const QString &filePath)
{
    json data;
    data["habits"] = json::array();

    for (const Habit &habit : habits)
    {
        json habitJson;
        habitJson["id"] = habit.id;
        habitJson["name"] = habit.name.toStdString();
        habitJson["description"] = habit.description.toStdString();
        habitJson["weekly_progress"] = json::array();

        for (bool day : habit.weeklyProgress)
        {
            habitJson["weekly_progress"].push_back(day);
        }

        data["habits"].push_back(habitJson);
    }

    // Update statistics
    json stats;
    stats["current_streak"] = currentStreak;
    stats["longest_streak"] = longestStreak;
    stats["completion_rate"] = completionRate;
    data["statistics"] = stats;

    // Create directory if not exists
    QDir().mkpath(QFileInfo(filePath).absolutePath());

    std::ofstream file(filePath.toStdString());
    if (file.is_open())
    {
        file << data.dump(4);
    }
    else
    {
        qWarning() << "Failed to save habits to" << filePath;
    }
}

void HabitTracker::addHabit(const Habit &habit)
{
    habits.append(habit);
    saveHabits("data/habits.json");
    emit habitsUpdated();
}

void HabitTracker::removeHabit(int id)
{
    habits.erase(std::remove_if(habits.begin(), habits.end(),
                                [id](const Habit &h)
                                { return h.id == id; }),
                 habits.end());
    saveHabits("data/habits.json");
    emit habitsUpdated();
}

Habit HabitTracker::getHabit(int id) const
{
    for (const Habit &habit : habits)
    {
        if (habit.id == id)
            return habit;
    }
    return Habit{};
}

void HabitTracker::updateHabitProgress(int habitId, int dayIndex, bool completed)
{
    for (Habit &habit : habits)
    {
        if (habit.id == habitId)
        {
            if (dayIndex >= 0 && dayIndex < habit.weeklyProgress.size())
            {
                habit.weeklyProgress[dayIndex] = completed;
                saveHabits("data/habits.json");

                // Update streaks
                bool allCompleted = std::all_of(habit.weeklyProgress.begin(),
                                                habit.weeklyProgress.end(),
                                                [](bool val)
                                                { return val; });

                if (allCompleted)
                {
                    currentStreak++;
                    if (currentStreak > longestStreak)
                    {
                        longestStreak = currentStreak;
                    }
                }
                else
                {
                    currentStreak = 0;
                }

                emit habitsUpdated();
                return;
            }
        }
    }
}

double HabitTracker::calculateWeeklyCompletion() const
{
    if (habits.isEmpty())
        return 0.0;

    int totalDays = 0;
    int completedDays = 0;

    for (const Habit &habit : habits)
    {
        for (bool completed : habit.weeklyProgress)
        {
            totalDays++;
            if (completed)
                completedDays++;
        }
    }

    return static_cast<double>(completedDays) / totalDays;
}