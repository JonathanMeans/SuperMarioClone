#ifndef SUPERMARIOBROS_FALLABLE_H
#define SUPERMARIOBROS_FALLABLE_H

#include <cstdlib>

class Fallable
{
public:
    virtual ~Fallable();

    size_t getBottomPosition();
    void setBottomPosition(size_t newBottomY);

    virtual size_t getY() const = 0;
    virtual size_t getX() const = 0;
    virtual size_t getHeight() const = 0;
    virtual void setPosition(size_t x, size_t y) = 0;


};

#endif  // SUPERMARIOBROS_FALLABLE_H
