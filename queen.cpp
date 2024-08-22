#include "queen.hpp"
#include "grid.hpp"
#include "ant.hpp"
#include <ncurses.h>
#include <cstdlib>
#include <algorithm>
using std::max;
using std::min;

Queen::Queen(int x, int y) : Critter(x, y), moves_since_mating(0) {}

void Queen::move(Grid &grid)
{
    if (moves_since_mating >= 30)
    {
        int new_x_posn = x;
        int new_y_posn = y;
        int direction = rand() % 8;

        calcDirection(direction, new_x_posn, new_y_posn);

        if (isValidPosition(grid, new_x_posn, new_y_posn))
        {
            moveToPosition(grid, new_x_posn, new_y_posn);
        }
        else
        {
            // Bounce off the wall
            bounceOffWall(grid, new_x_posn, new_y_posn);
        }
    }
}

void Queen::breed(Grid &grid)
{
    if (moves_since_mating >= 30)
    {
        spawnOffspring(grid);
        moves_since_mating = 0;
    }
    else
    {
        moves_since_mating++;
    }

    if (moves_since_mating >= 90)
    {
        grid.setCell(x, y, nullptr);
        delete this;
    }
}

void Queen::calcDirection(int direction, int &new_x_posn, int &new_y_posn)
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

bool Queen::isValidPosition(const Grid &grid, int new_x_posn, int new_y_posn)
{
    return new_x_posn >= 0 && new_x_posn < grid.getDimension() && new_y_posn >= 0 && new_y_posn < grid.getDimension() && grid.getCell(new_x_posn, new_y_posn) == nullptr;
}

void Queen::moveToPosition(Grid &grid, int new_x_posn, int new_y_posn)
{
    grid.setCell(x, y, nullptr);
    grid.setCell(new_x_posn, new_y_posn, this);
    x = new_x_posn;
    y = new_y_posn;
}

void Queen::bounceOffWall(Grid &grid, int &new_x_posn, int &new_y_posn)
{
    new_x_posn = max(1, min(new_x_posn, grid.getDimension() - 2));
    new_y_posn = max(1, min(new_y_posn, grid.getDimension() - 2));

    if (isValidPosition(grid, new_x_posn, new_y_posn))
    {
        moveToPosition(grid, new_x_posn, new_y_posn);
    }
}

void Queen::spawnOffspring(Grid &grid)
{
    int num_offspring = 0;

    for (int i = -2; i <= 2; ++i)
    {
        for (int j = -2; j <= 2; ++j)
        {
            int new_y_posn = y + i;
            int new_x_posn = x + j;
            if (isValidPosition(grid, new_x_posn, new_y_posn))
            {
                double percentChance = static_cast<double>(rand()) / RAND_MAX;
                int range = static_cast<int>(percentChance * 100);
                switch (range)
                {
                case 60 ... 98:
                    grid.setCell(new_x_posn, new_y_posn, new Ant(new_x_posn, new_y_posn, Ant::male));
                    break;
                case 0 ... 59:
                    grid.setCell(new_x_posn, new_y_posn, new Ant(new_x_posn, new_y_posn, Ant::female));
                    break;
                default:
                    grid.setCell(new_x_posn, new_y_posn, new Queen(new_x_posn, new_y_posn));
                    break;
                }
                num_offspring++;
                if (num_offspring >= 10)
                {
                    return;
                }
            }
        }
    }
}

void Queen::starve(Grid &grid)
{
}

void Queen::draw()
{
    mvaddch(y, x, 'Q');
}
