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
