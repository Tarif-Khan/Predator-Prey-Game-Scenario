// HW5 Tarif Khan
#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include "grid.hpp"
using namespace std;

int main()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);

    // Initialize everything I will need.
    int grid_size;
    int num_queens;
    int num_female;
    int num_male;
    int num_doodle;

    // Take in and set all the parameters I will need.
    cout << "Please input the size of the grid. The size you choose will be both length and width.: ";
    cin >> grid_size;
    cout << "The size of the grid is " << grid_size << endl;
    cout << endl;
    cout << "Please enter the number of doodlebugs for your game: ";
    cin >> num_doodle;
    cout << "The number of doodlebugs in your game is: " << num_doodle << endl;
    cout << "Enter the number of queens: ";
    cin >> num_queens;
    cout << "Number of queens: " << num_queens << endl;
    cout << endl;
    cout << "Please enter the number of male ants for your game: ";
    cin >> num_male;
    cout << "Number of male ants: " << num_male << endl;
    cout << endl;
    cout << "Enter the number of female ants: ";
    cin >> num_female;
    cout << "Number of female ants: " << num_female << endl;
    cout << endl;

    // Create the grid
    Grid grid(grid_size);
    srand(static_cast<unsigned int>(time(0)));
    grid.placeCritters(num_doodle, num_queens, num_male, num_female);

    // This is the loop for the game to run
    while (grid.hasCritters<Doodlebug>() && grid.hasCritters<Ant>())
    {
        clear();
        grid.update();
        grid.draw();
        refresh();
        napms(1000);
    }
    endwin();

    // Game end conditional explained.
    if (!grid.hasCritters<Doodlebug>())
    {
        cout << "The game ended because all the doodlebugs were eliminated." << endl;
    }
    else if (!grid.hasCritters<Ant>())
    {
        cout << "The game ended because all the ants were eliminated." << endl;
    }

    return 0;
}