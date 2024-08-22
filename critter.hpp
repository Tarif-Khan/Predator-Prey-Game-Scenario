#ifndef CRITTER_HPP
#define CRITTER_HPP

class Grid;

class Critter {
protected:
    int x;
    int y;
    int age;

public:
    Critter(int x, int y);
    virtual ~Critter();
    virtual void move(Grid& grid) = 0;
    virtual void breed(Grid& grid) = 0;
    virtual void starve(Grid& grid) = 0;
    virtual void draw() = 0;
};

#endif