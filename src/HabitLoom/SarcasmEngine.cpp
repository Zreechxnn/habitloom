#include "SarcasmEngine.h"

SarcasmEngine::SarcasmEngine(bool brutalMode) : brutalMode(brutalMode)
{
    rng.seed(std::time(nullptr));
}

QString SarcasmEngine::getRewardMessage()
{
    std::uniform_int_distribution<int> dist(0, rewards.size() - 1);
    if (brutalMode)
    {
        dist = std::uniform_int_distribution<int>(0, brutalRewards.size() - 1);
        return brutalRewards[dist(rng)];
    }
    return rewards[dist(rng)];
}

QString SarcasmEngine::getPunishmentMessage()
{
    std::uniform_int_distribution<int> dist(0, punishments.size() - 1);
    if (brutalMode)
    {
        dist = std::uniform_int_distribution<int>(0, brutalPunishments.size() - 1);
        return brutalPunishments[dist(rng)];
    }
    return punishments[dist(rng)];
}

QString SarcasmEngine::getRandomNotification()
{
    std::uniform_int_distribution<int> dist(0, randomNotifications.size() - 1);
    return randomNotifications[dist(rng)];
}