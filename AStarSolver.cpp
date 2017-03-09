#include <set>
#include <iostream>
#include <cassert>
#include <ostream>
#include "AStarSolver.h"

AStarSolver::AStarSolver ( Maze* _maze )
        : Solver( _maze )
{}

void AStarSolver::solve ()
{
    generate_nodes();

    // delete endpoints
    for ( auto it = _mNodes.begin(); it != _mNodes.end(); ++it )
    {
        if ( it->num_conn() == 1 && it->get_pos() != _maze->get_start() && it->get_pos() != _maze->get_end() )
        {
            MNode* n = it->get_conn( 0 );
            n->delete_node( &(*it) );
            _mNodes.erase( it );
        }
    }
    std::cout << _mNodes.size() << std::endl;
}

void AStarSolver::generate_nodes ()
{
    std::vector<std::set<Dir>> dirSets;

    std::cout << "Setting up nodes..." << std::endl;

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

    for ( auto&& node : _mNodes )
    {
        _maze->set_tile( make_pos( node.x, node.y ), Tiles::Solution );
    }

    std::cout << *_maze;

    std::cout << "Connecting nodes..." << std::endl;

    // connect nodes
    for ( int i = 0; i < _mNodes.size(); i++ )
    {
        MNode* n = &(_mNodes[i]);
        auto d = dirSets[i];
        if ( n->num_conn() != d.size() )
        {
            if ( d.count( Dir::E ) != 0 )
            {
                n->add_conn( &(_mNodes[i + 1]) );
                assert( dirSets[i + 1].count( Dir::W ) == 1 );
                _mNodes[i + 1].add_conn( n );
            }
            if ( d.count( Dir::S ) != 0 )
            {
                for ( int j = i + 1; j < _mNodes.size(); j++ )
                {
                    if ( _mNodes[j].y == n->y )
                    {
                        n->add_conn( &(_mNodes[j]) );
                        assert( dirSets[j].count( Dir::N ) == 1 );
                        _mNodes[j].add_conn( n );
                        break;
                    }
                }
            }
        }
    }

    for ( int i = 0; i < _mNodes.size(); i++ )
    {
        if ( _mNodes[i].num_conn() != dirSets[i].size() )
        {
            std::cerr << "Error applying connections: " << _mNodes[i].x << " " << _mNodes[i].y << std::endl;
        }
    }

    std::cout << "Done connecting " << _mNodes.size() << " nodes." << std::endl;
}
