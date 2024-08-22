#ifndef DOODLEBUG_HPP
#define DOODLEBUG_HPP

#include "critter.hpp"

class Doodlebug : public Critter
{
private:
    int moves_since_meal;

public:
    Doodlebug(int x, int y);
    void move(Grid &grid) override;
    bool moveToAdjacentAnt(Grid &grid, int &new_x_posn, int &new_y_posn);
    void calcDirection(int direction, int &new_x_posn, int &new_y_posn);
    bool isValidPosition(const Grid &grid, int new_x_posn, int new_y_posn);
    void moveToPosition(Grid &grid, int new_x_posn, int new_y_posn);
    void bounceOffWall(Grid &grid, int &new_x_posn, int &new_y_posn);
    void breed(Grid &grid) override;
    void spawnOffspring(Grid &grid);
    void starve(Grid &grid) override;
    void draw() override;
};

#endif