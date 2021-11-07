#include "Event.h"

Event Event::constructPointsEarned(const sf::Vector2f& position, int points)
{
    Event event;
    event.type = EventType::POINTS_EARNED;
    PointsEarned pointsEarned;
    pointsEarned.position = position;
    pointsEarned.points = points;
    event.eventData = pointsEarned;
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

Event Event::constructAnimationCompleted(const std::string& animationType)
{
    Event event;
    event.type = EventType::ANIMATION_COMPLETED;
    AnimationCompleted animationCompleted;
    animationCompleted.animationType = animationType;
    event.eventData = animationCompleted;
    return event;
}

Event Event::constructFireball(const sf::Vector2f& position, int direction)
{
    Event event;
    event.type = EventType::FIREBALL_SPAWNED;
    FireballSpawned fireballSpawned;
    fireballSpawned.position = position;
    fireballSpawned.direction = direction;
    event.eventData = fireballSpawned;
    return event;
}


Event::PointsEarned Event::asPointsEarned() const
{
    return std::get<Event::PointsEarned>(eventData);
}

Event::ItemSpawned Event::asItemSpawned() const
{
    return std::get<Event::ItemSpawned>(eventData);
}

Event::BlockShattered Event::asBlockShattered() const
{
    return std::get<Event::BlockShattered>(eventData);
}

Event::AnimationCompleted Event::asAnimationCompleted() const
{
    return std::get<Event::AnimationCompleted>(eventData);
}

Event::FireballSpawned Event::asFireballSpawned() const
{
    return std::get<Event::FireballSpawned>(eventData);
}
