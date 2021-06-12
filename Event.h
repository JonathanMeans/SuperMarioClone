#ifndef SUPERMARIOBROS_EVENT_H
#define SUPERMARIOBROS_EVENT_H

#include <Entity.h>
#include <variant>

enum class EventType
{
    ENEMY_KILLED,
    ITEM_SPAWNED
};

class Event
{
public:
    EventType type;

    static Event constructEnemyKilled(const sf::Vector2f& position, int points);


    struct EnemyKilled
    {
        sf::Vector2f position;
        int points;
    };

    struct ItemSpawned
    {
        sf::Vector2f position;
        EntityType type;
    };

    [[nodiscard]] EnemyKilled asEnemyKilled() const;
    [[nodiscard]] ItemSpawned asItemSpawned() const;

private:
    std::variant<EnemyKilled, ItemSpawned> eventData;
};

#endif  // SUPERMARIOBROS_EVENT_H
