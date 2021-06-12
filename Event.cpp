#include "Event.h"

Event Event::constructEnemyKilled(const sf::Vector2f& position, int points)
{
    Event event;
    event.type = EventType::ENEMY_KILLED;
    EnemyKilled enemyKilled;
    enemyKilled.position = position;
    enemyKilled.points = points;
    event.eventData = enemyKilled;
    return event;
}

Event Event::constructItemSpawned(EntityType type,
                                  const sf::Vector2f& position,
                                  float blockTop)
{
    Event event;
    event.type = EventType::ITEM_SPAWNED;
    ItemSpawned itemSpawned;
    itemSpawned.position = position;
    itemSpawned.type = type;
    itemSpawned.blockTop = blockTop;
    event.eventData = itemSpawned;
    return event;
}

Event Event::constructBlockShattered(const sf::Vector2f& position)
{
    Event event;
    event.type = EventType::BLOCK_SHATTERED;
    BlockShattered blockShattered;
    blockShattered.position = position;
    event.eventData = blockShattered;
    return event;
}

Event::EnemyKilled Event::asEnemyKilled() const
{
    return std::get<Event::EnemyKilled>(eventData);
}

Event::ItemSpawned Event::asItemSpawned() const
{
    return std::get<Event::ItemSpawned>(eventData);
}

Event::BlockShattered Event::asBlockShattered() const
{
    return std::get<Event::BlockShattered>(eventData);
}
