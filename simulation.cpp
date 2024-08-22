#include "simulation.hpp"
#include "doodlebug.hpp"
#include "ant.hpp"
#include "queen.hpp"
#include <ncurses.h>
#include <algorithm>
#include <random>

using namespace std;

Simulation::Simulation(int size, int numDoodlebugs, int numQueens, int numMaleAnts, int numFemaleAnts)
    : gridSize(size), grid(size, vector<unique_ptr<Critter>>(size)) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, gridSize - 1);

    auto placeCritter = [&](int count, auto createCritter) {
        for (int i = 0; i < count; ++i) {
            int x, y;
            do {
                x = dis(gen);
                y = dis(gen);
            } while (grid[x][y]);
            grid[x][y] = createCritter(x, y);
        }
    };

    placeCritter(numDoodlebugs, [](int x, int y) { return make_unique<Doodlebug>(x, y); });
    placeCritter(numQueens, [](int x, int y) { return make_unique<Queen>(x, y); });
    placeCritter(numMaleAnts, [](int x, int y) { return make_unique<Ant>(x, y, Ant::MALE); });
    placeCritter(numFemaleAnts, [](int x, int y) { return make_unique<Ant>(x, y, Ant::FEMALE); });
}

void Simulation::run() {
    while (hasAnts() && hasDoodlebugs()) {
        clear();
        update();
        draw();
        refresh();
        napms(1000);
    }
}

void Simulation::update() {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (grid[i][j]) {
                grid[i][j]->move(grid, i, j);
            }
        }
    }

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (grid[i][j]) {
                grid[i][j]->breed(grid, i, j);
                grid[i][j]->starve(grid, i, j);
            }
        }
    }
}

void Simulation::draw() {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (grid[i][j]) {
                grid[i][j]->draw(i, j);
            } else {
                mvaddch(i, j, ' ');
            }
        }
    }
}

bool Simulation::hasAnts() {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (dynamic_cast<Ant*>(grid[i][j].get())) {
                return true;
            }
        }
    }
    return false;
}

bool Simulation::hasDoodlebugs() {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (dynamic_cast<Doodlebug*>(grid[i][j].get())) {
                return true;
            }
        }
    }
    return false;
}
