#ifndef SUPERMARIOBROS_EVENT_H
#define SUPERMARIOBROS_EVENT_H

#include <Entity.h>

#include <variant>

enum class EventType
{
    POINTS_EARNED,
    ITEM_SPAWNED,
    BLOCK_SHATTERED,
    ANIMATION_COMPLETED,
    FIREBALL_SPAWNED,
};

class Event
{
public:
    EventType type;

    static Event constructPointsEarned(const sf::Vector2f& position, int points);
    static Event constructItemSpawned(EntityType type,
                                      const sf::Vector2f& position,
                                      float blockBottom);
    static Event constructBlockShattered(const sf::Vector2f& position);
    static Event constructAnimationCompleted(const std::string& animationType);
    static Event constructFireball(const sf::Vector2f& position, int direction);

    struct PointsEarned
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

    struct AnimationCompleted
    {
        std::string animationType;
    };

    struct FireballSpawned
    {
	sf::Vector2f position;
	int direction;
    };

    [[nodiscard]] PointsEarned asPointsEarned() const;
    [[nodiscard]] ItemSpawned asItemSpawned() const;
    [[nodiscard]] BlockShattered asBlockShattered() const;
    [[nodiscard]] AnimationCompleted asAnimationCompleted() const;
    [[nodiscard]] FireballSpawned asFireballSpawned() const;

private:
    std::variant<PointsEarned, ItemSpawned, BlockShattered, AnimationCompleted, FireballSpawned>
            eventData;
};

#endif  // SUPERMARIOBROS_EVENT_H
