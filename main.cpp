#include <iostream>
#include "Maze.h"
#include "FillSolver.h"
#include "AStarSolver.h"

int main ()
{
    std::string maze_file = "/home/lars/Documents/programming/maze_solver/maze.dat";

    Maze m;
    m.load_textFile( maze_file );
    std::cout << m << std::endl;

//    FillSolver f ( &m );
//    f.solve();

    AStarSolver a ( &m );
    a.solve();

    return 0;
}