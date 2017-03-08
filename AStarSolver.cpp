//
// Created by lars on 3/8/17.
//

#include <set>
#include <iostream>
#include "AStarSolver.h"

AStarSolver::AStarSolver ( Maze* _maze )
        : Solver( _maze )
{}

void AStarSolver::solve ()
{
    generate_nodes();
}

void AStarSolver::generate_nodes ()
{
    std::vector<std::set<Dir>> dirSets;

    // set up nodes
    // maze has walls all around
    for ( int i = 1; i < _maze->get_maze().size() - 1; ++i )
    {
        auto line = _maze->get_maze()[i];
        for ( int j = 1; j < line.size() - 1; ++j )
        {
            if ( line[j] == Tiles::Wall )
            {
                continue;
            }

            std::set<Dir> dirs;

            for ( auto d : dirVector )
            {
                Pos p = std::make_pair( i, j );
                p = step_dir( p, d );
                if ( _maze->get_maze()[p.first][p.second] != Tiles::Wall )
                {
                    dirs.insert( d );
                }
            }

            if ( std::make_pair( i, j ) == _maze->get_start()
                 || std::make_pair( i, j ) == _maze->get_end()
                 || dirs.size() != 2
                 || (dirs.count( Dir::N ) != 0 && (dirs.count( Dir::E ) != 0 || dirs.count( Dir::W ) != 0))
                 || (dirs.count( Dir::S ) != 0 && (dirs.count( Dir::E ) != 0 || dirs.count( Dir::W ) != 0)) )
            {
                _mNodes.emplace_back( i, j );
                dirSets.push_back( dirs );
            }
        }
    }

    std::cout << _mNodes.size() << std::endl;
    for ( auto&& node : _mNodes )
    {
        _maze->set_tile( make_pos( node.x, node.y ), Tiles::Solution );
    }

    std::cout << *_maze;

    // connect nodes

}
