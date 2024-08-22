#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include <memory>
#include "critter.hpp"

using namespace std;

class Simulation {
private:
    int gridSize;
    vector<vector<unique_ptr<Critter>>> grid;

public:
    Simulation(int size, int numDoodlebugs, int numQueens, int numMaleAnts, int numFemaleAnts);
    void run();
    void update();
    void draw();
    bool hasAnts();
    bool hasDoodlebugs();
};

#endif
