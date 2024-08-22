#include "doodlebug.hpp"
#include "grid.hpp"
#include "ant.hpp"
#include <ncurses.h>
#include <cstdlib>
#include <algorithm>
using std::max;
using std::min;

Doodlebug::Doodlebug(int x, int y) : Critter(x, y), moves_since_meal(0) {}

void Doodlebug::move(Grid &grid)
{
    int new_x_posn = x;
    int new_y_posn = y;

    if (!moveToAdjacentAnt(grid, new_x_posn, new_y_posn))
    {
        int direction = (moves_since_meal + 1) % 8;
        calcDirection(direction, new_x_posn, new_y_posn);
        if (isValidPosition(grid, new_x_posn, new_y_posn))
        {
            moveToPosition(grid, new_x_posn, new_y_posn);
        }
        else
        {
            bounceOffWall(grid, new_x_posn, new_y_posn);
        }

        moves_since_meal++;
    }
}

bool Doodlebug::moveToAdjacentAnt(Grid &grid, int &new_x_posn, int &new_y_posn)
{
    const int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    for (const auto &direction : directions)
    {
        int adjX = x + direction[0];
        int adjY = y + direction[1];

        if (isValidPosition(grid, adjX, adjY))
        {
            Critter *critter = grid.getCell(adjX, adjY);
            if (dynamic_cast<Ant *>(critter) != nullptr)
            {
                moveToPosition(grid, adjX, adjY);
                new_x_posn = adjX;
                new_y_posn = adjY;
                moves_since_meal = 0;
                delete critter;
                return true;
            }
        }
    }
    return false;
}

void Doodlebug::calcDirection(int direction, int &new_x_posn, int &new_y_posn)
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

bool Doodlebug::isValidPosition(const Grid &grid, int new_x_posn, int new_y_posn)
{
    return new_x_posn >= 0 && new_x_posn < grid.getDimension() && new_y_posn >= 0 && new_y_posn < grid.getDimension();
}

void Doodlebug::moveToPosition(Grid &grid, int new_x_posn, int new_y_posn)
{
    grid.setCell(x, y, nullptr);
    grid.setCell(new_x_posn, new_y_posn, this);
    x = new_x_posn;
    y = new_y_posn;
}

void Doodlebug::bounceOffWall(Grid &grid, int &new_x_posn, int &new_y_posn)
{
    new_x_posn = max(1, min(new_x_posn, grid.getDimension() - 2));
    new_y_posn = max(1, min(new_y_posn, grid.getDimension() - 2));

    if (isValidPosition(grid, new_x_posn, new_y_posn))
    {
        moveToPosition(grid, new_x_posn, new_y_posn);
    }
}

void Doodlebug::breed(Grid &grid)
{
    if (age >= 10)
    {
        spawnOffspring(grid);
    }
}

void Doodlebug::spawnOffspring(Grid &grid)
{
    const int directions[8][2] = {{-2, -2}, {-2, 0}, {-2, 2}, {0, -2}, {0, 2}, {2, -2}, {2, 0}, {2, 2}};

    for (const auto &direction : directions)
    {
        int new_x_posn = x + direction[0];
        int new_y_posn = y + direction[1];

        if (isValidPosition(grid, new_x_posn, new_y_posn) && grid.getCell(new_x_posn, new_y_posn) == nullptr)
        {
            grid.setCell(new_x_posn, new_y_posn, new Doodlebug(new_x_posn, new_y_posn));
            return;
        }
    }
}

void Doodlebug::starve(Grid &grid)
{
    if (moves_since_meal >= 20)
    {
        grid.setCell(x, y, nullptr);
        delete this;
    }
}

void Doodlebug::draw()
{
    mvaddch(y, x, 'X');
}