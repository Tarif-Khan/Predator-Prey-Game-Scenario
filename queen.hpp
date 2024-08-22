#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "critter.hpp"

class Queen : public Critter
{
private:
    int moves_since_mating;

public:
    Queen(int x, int y);
    void move(Grid &grid) override;
    void breed(Grid &grid) override;
    void calcDirection(int direction, int &newX, int &newY);
    bool isValidPosition(const Grid &grid, int newX, int newY);
    void moveToPosition(Grid &grid, int newX, int newY);
    void bounceOffWall(Grid &grid, int &newX, int &newY);
    void spawnOffspring(Grid &grid);
    void starve(Grid &grid) override;
    void draw() override;
};

#endif