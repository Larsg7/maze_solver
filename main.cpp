#include <iostream>
#include "Maze.h"
#include "FillSolver.h"
#include "AStarSolver.h"

int main ()
{
#ifdef linux
    std::string maze_file = "/home/lars/Documents/programming/cpp/maze_solver/maze.dat";
#endif
#ifdef _WIN32
	std::string maze_file = "C:/Users/lars/Source/Repos/maze_solver/maze.dat";
#endif

    Maze m;
    m.load_textFile( maze_file );
    std::cout << m << std::endl;

//    FillSolver f ( &m );
//    f.solve();

    AStarSolver a ( &m );
    a.solve();

	char c;
	//std::cin >> c;

    return 0;
}