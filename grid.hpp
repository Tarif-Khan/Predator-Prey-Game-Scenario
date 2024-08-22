#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include "critter.hpp"
#include "ant.hpp"
#include "queen.hpp"
#include "doodlebug.hpp"


class Grid
{
private:
    int width;
    int height;
    std::vector<std::vector<Critter *>> cells;

public:
    Grid(int dimension);
    ~Grid();
    void placeCritters(int numDoodlebugs, int numMaleAnts, int numFemaleAnts, int numQueens);
    void update();
    void draw();
    int getDimension() const;
    void breedStarve();
    void setCell(int x, int y, Critter *critter);
    Critter *getCell(int x, int y) const;
    template <typename CreateCritterFn>
    void placeCrittersOfType(int count, CreateCritterFn createCritter);
    template <typename CritterType>
    void updateCritters();
    template <typename CritterType>
bool hasCritters() const
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (dynamic_cast<CritterType *>(cells[i][j]) != nullptr)
            {
                return true;
            }
        }
    }
    return false;
}
};
#endif
