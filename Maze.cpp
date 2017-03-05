#include <fstream>
#include <iostream>
#include <sstream>
#include "Maze.h"

void Maze::load_textFile ( std::string& file )
{
    std::ifstream fileS ( file, std::ios_base::in );
    if ( fileS.fail() )
    {
        std::cerr << "Could not open " << file << std::endl;
        return;
    }

    std::string s;
    std::stringstream ss;
    while ( std::getline( fileS, s ) )
    {
        char c;
        ss = std::stringstream ( s );
        std::vector<bool> line;
        while ( ss >> c )
        {
            if ( c == WALL_SYMBOL )
            {
                line.push_back( false );
            }
            else if ( c == FLOOR_SYMBOL )
            {
                line.push_back( true );
            }
        }
        _maze.push_back( line );
    }
}

const std::vector<std::vector<bool>>& Maze::get_maze () const
{
    return _maze;
}
