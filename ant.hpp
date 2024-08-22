#ifndef ANT_HPP
#define ANT_HPP

#include "critter.hpp"

class Ant : public Critter
{
public:
    enum ant_type
    {
        male,
        female
    };
    ant_type type;

private:
        int stepsWithoutMoving;

public:
    Ant(int x, int y, ant_type type);
    void move(Grid &grid) override;
    void calcDirection(int direction, int &newX, int &newY);
    bool isValidPosition(const Grid &grid, int newX, int newY);
    void moveToPosition(Grid &grid, int newX, int newY);
    void bounceOffWall(Grid &grid, int &newX, int &newY);
    void breed(Grid &grid) override;
    void starve(Grid &grid) override;
    void draw() override;
};

#endif