#ifndef SUPERMARIOBROS_LEVEL_H
#define SUPERMARIOBROS_LEVEL_H

#include "Event.h"
#include "Input.h"
#include "Text.h"
#include "entities/Mario.h"

/*
 * Encapsulates the game logic and entities for a single level.
 */
class Level
{
public:
    /*
     * Construct a new level from Mario and the entities in the level.
     * Current, the Level has ownership of Mario and the entities
     */
    Level(std::unique_ptr<Mario> mario,
          std::vector<std::unique_ptr<Entity>>&& entities);

    void setMarioMovementFromController(const KeyboardInput& currentInput);

    void executeFrame(const KeyboardInput& input);

    void drawFrame(sf::RenderWindow& window);

    [[nodiscard]] const Mario& getMario() const;

private:
    void addHUDOverlay();

    std::vector<std::shared_ptr<Text>> mTextElements;

    std::unique_ptr<Mario> mMario;

    std::shared_ptr<Points> mPoints;

    [[nodiscard]] bool physicsAreOn() const;

    float setVerticalVelocityDueToJumpStart(const KeyboardInput& currentInput,
                                            const sf::Vector2f& velocity) const;
    float calculateVerticalAcceleration(const KeyboardInput& currentInput,
                                        float xVelocity) const;

    void onEnemyKilled(const Event::EnemyKilled&);
    void onItemSpawned(const Event::ItemSpawned&);
};

std::vector<Event>& getEventQueue();
void addEvent(Event event);

#endif  // SUPERMARIOBROS_LEVEL_H
