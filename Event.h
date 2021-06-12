#ifndef SUPERMARIOBROS_EVENT_H
#define SUPERMARIOBROS_EVENT_H

#include <Entity.h>
#include <variant>

enum class EventType
{
    ENEMY_KILLED,
    ITEM_SPAWNED,
    BLOCK_SHATTERED
};

class Event
{
public:
    EventType type;

    static Event constructEnemyKilled(const sf::Vector2f& position, int points);
    static Event constructItemSpawned(EntityType type,
                                      const sf::Vector2f& position,
                                      float blockTop);
    static Event constructBlockShattered(const sf::Vector2f& position);

    struct EnemyKilled
    {
        sf::Vector2f position;
        int points;
    };

    struct ItemSpawned
    {
        sf::Vector2f position;
        EntityType type;
        float blockTop;
    };

    struct BlockShattered
    {
        sf::Vector2f position;
    };

    [[nodiscard]] EnemyKilled asEnemyKilled() const;
    [[nodiscard]] ItemSpawned asItemSpawned() const;
    [[nodiscard]] BlockShattered asBlockShattered() const;

private:
    std::variant<EnemyKilled, ItemSpawned, BlockShattered> eventData;
};

#endif  // SUPERMARIOBROS_EVENT_H
