#include <fstream>
#include <iostream>
#include <sstream>
#include "Maze.h"


Pos make_pos ( int x, int y )
{
return std::make_pair( x, y );
}


Maze::Maze ()
        : _start( -1, -1 ), _end( -1, -1 )
{}

void Maze::load_textFile ( std::string& file )
{
    std::ifstream fileS( file, std::ios_base::in );
    if ( fileS.fail() )
    {
        std::cerr << "Could not open " << file << std::endl;
        exit( EXIT_FAILURE );
    }

    std::string s;
    std::stringstream ss;
    while ( std::getline( fileS, s ) )
    {
        char c;
        ss = std::stringstream( s );
        std::vector<Tiles> line;
        while ( ss >> c )
        {
            Tiles t;

            switch ( c )
            {
                case static_cast<char>(Tiles::Wall):
                    t = Tiles::Wall;
                    break;
                case static_cast<char>(Tiles::Floor):
                    t = Tiles::Floor;
                    break;
                case static_cast<char>(Tiles::Start):
                    t = Tiles::Start;
                    break;
                case static_cast<char>(Tiles::End):
                    t = Tiles::End;
                    break;
                default:
                    std::cerr << "Unknown symbol " << c << std::endl;
                    exit( EXIT_FAILURE );
            }
            line.push_back( t );
        }
        _maze.push_back( line );
    }

    for ( int i = 0; i < _maze.size(); ++i )
    {
        auto v = _maze[i];
        for ( int j = 0; j < v.size(); ++j )
        {
            if ( v[j] == Tiles::Start )
            {
                _start.first = i;
                _start.second = j;
            }
            else if ( v[j] == Tiles::End )
            {
                _end.first = i;
                _end.second = j;
            }
        }
    }

    if ( _start == std::make_pair( -1, -1 ) || _end == std::make_pair( -1, -1 ) )
    {
        std::cerr << "Could not find start or end point!" << std::endl;
        exit( EXIT_FAILURE );
    }
}

const std::vector<std::vector<Tiles>>& Maze::get_maze () const
{
    return _maze;
}

std::ostream& operator<< ( std::ostream& io, Maze& m )
{
    for ( auto v : m.get_maze() )
    {
        for ( auto e : v )
        {
            io << static_cast<char>(e) << ' ';
        }
        io << std::endl;
    }
    return io;
}

const Pos& Maze::get_start () const
{
    return _start;
}

const Pos& Maze::get_end () const
{
    return _end;
}

void Maze::set_tile ( Pos p, Tiles t )
{
    _maze[p.first][p.second] = t;
}
