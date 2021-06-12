#ifndef SUPERMARIOBROS_EVENT_H
#define SUPERMARIOBROS_EVENT_H

#include <Entity.h>
#include <variant>

class Event
{
public:
    enum class EventType
    {
        ENEMY_KILLED,
        ITEM_SPAWNED
    };
    EventType type;

    static Event constructEnemyKilled(const sf::Vector2f& position, int points);

private:
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

    std::variant<EnemyKilled, ItemSpawned> eventData;

};

#endif  // SUPERMARIOBROS_EVENT_H
