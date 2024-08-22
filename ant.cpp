#include "ant.hpp"
#include "grid.hpp"
#include <ncurses.h>
#include <cstdlib>
#include <algorithm>
using std::max;
using std::min;

Ant::Ant(int x, int y, ant_type type) : Critter(x, y), type(type), stepsWithoutMoving(0) {}

void Ant::move(Grid &grid)
{
    int new_x_posn = x;
    int new_y_posn = y;
    int direction = rand() % 8;
    calcDirection(direction, new_x_posn, new_y_posn);
    if (isValidPosition(grid, new_x_posn, new_y_posn) && grid.getCell(new_x_posn, new_y_posn) == nullptr)
    {
        moveToPosition(grid, new_x_posn, new_y_posn);
        stepsWithoutMoving = 0;
    }
    else
    {
        bounceOffWall(grid, new_x_posn, new_y_posn);
        if (grid.getCell(new_x_posn, new_y_posn) == nullptr)
        {
            moveToPosition(grid, new_x_posn, new_y_posn);
            stepsWithoutMoving = 0;
        }
    }
    stepsWithoutMoving++;
}

void Ant::calcDirection(int direction, int &new_x_posn, int &new_y_posn)
{
    if (direction == 0)
    {
        new_x_posn++;
    }
    else if (direction == 1)
    {
        new_y_posn++;
        new_x_posn++;
    }
    else if (direction == 2)
    {
        new_y_posn++;
    }
    else if (direction == 3)
    {
        new_y_posn++;
        new_x_posn--;
    }
    else if (direction == 4)
    {
        new_x_posn--;
    }
    else if (direction == 5)
    {
        new_y_posn--;
        new_x_posn--;
    }
    else if (direction == 6)
    {
        new_y_posn--;
    }
    else if (direction == 7)
    {
        new_y_posn--;
        new_x_posn++;
    }
}

bool Ant::isValidPosition(const Grid &grid, int new_x_posn, int new_y_posn)
{
    return new_x_posn >= 0 && new_x_posn < grid.getDimension() && new_y_posn >= 0 && new_y_posn < grid.getDimension();
}

void Ant::moveToPosition(Grid &grid, int new_x_posn, int new_y_posn)
{
    grid.setCell(x, y, nullptr);
    grid.setCell(new_x_posn, new_y_posn, this);
    x = new_x_posn;
    y = new_y_posn;
}

void Ant::bounceOffWall(Grid &grid, int &new_x_posn, int &new_y_posn)
{
    new_x_posn = max(1, min(new_x_posn, grid.getDimension() - 2));
    new_y_posn = max(1, min(new_y_posn, grid.getDimension() - 2));

    if (isValidPosition(grid, new_x_posn, new_y_posn))
    {
        moveToPosition(grid, new_x_posn, new_y_posn);
    }
}

void Ant::breed(Grid &grid)
{
}

void Ant::starve(Grid &grid)
{
    if (stepsWithoutMoving >= 5)
    {
        grid.setCell(x, y, nullptr);
        delete this;
    }
}

void Ant::draw()
{
    if (type == female)
    {
        mvaddch(y, x, 'w');
    }
    else
    {
        mvaddch(y, x, 'o');
    }
}
