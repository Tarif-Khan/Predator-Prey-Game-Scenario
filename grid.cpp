#include "grid.hpp"
#include <ncurses.h>
#include <cstdlib>

Grid::Grid(int dimension) : width(dimension), height(dimension)
{
    cells.resize(height, std::vector<Critter *>(width, nullptr));
}

Grid::~Grid()
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            delete cells[i][j];
        }
    }
}

int Grid::getDimension() const
{
    return width;
}

void Grid::setCell(int x, int y, Critter *critter)
{
    cells[y][x] = critter;
}

Critter *Grid::getCell(int x, int y) const
{
    return cells[y][x];
}

void Grid::placeCritters(int num_doodlebugs, int num_queens, int num_male, int num_female)
{
    placeCrittersOfType(num_doodlebugs, [](int x, int y)
                        { return new Doodlebug(x, y); });
    placeCrittersOfType(num_queens, [](int x, int y)
                        { return new Queen(x, y); });
    placeCrittersOfType(num_male, [](int x, int y)
                        { return new Ant(x, y, Ant::male); });
    placeCrittersOfType(num_female, [](int x, int y)
                        { return new Ant(x, y, Ant::female); });
}

template <typename CreateCritterFn>
void Grid::placeCrittersOfType(int count, CreateCritterFn createCritter)
{
    for (int i = 0; i < count; ++i)
    {
        int x, y;
        do
        {
            x = rand() % width;
            y = rand() % height;
        } while (cells[y][x] != nullptr);
        cells[y][x] = createCritter(x, y);
    }
}

void Grid::update()
{
    updateCritters<Doodlebug>();
    updateCritters<Ant>();
    breedStarve();
}

template <typename CritterType>
void Grid::updateCritters()
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (dynamic_cast<CritterType *>(cells[i][j]) != nullptr)
            {
                cells[i][j]->move(*this);
            }
        }
    }
}

void Grid::breedStarve()
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (cells[i][j] != nullptr)
            {
                cells[i][j]->breed(*this);
                cells[i][j]->starve(*this);
            }
        }
    }
}

void Grid::draw()
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (cells[i][j] != nullptr)
            {
                cells[i][j]->draw();
            }
            else
            {
                mvaddch(i, j, ' ');
            }
        }
    }
}

