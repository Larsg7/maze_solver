#include <iostream>
#include <cassert>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include "AStarSolver.h"

AStarSolver::AStarSolver ( Maze* _maze )
        : Solver( _maze ), _steps ( 0 )
{}

void AStarSolver::solve ()
{
    generate_nodes();
    //delete_endpoints();

    // find start node
    auto it = std::find_if( _mNodes.begin(), _mNodes.end(), [this]( MNode m ) {
        return m.get_pos() == this->_maze->get_start();
    } );
    assert( it != _mNodes.end() );

    std::unordered_map<MNode*,MNode*> parentNodes;

    {
        // current_node = start
        AStarNode current_node( &( *it ), 0 );

        std::vector<AStarNode> paths;

        std::unordered_set<MNode*> visitedNodes;

        while ( current_node.node->get_pos() != _maze->get_end() )
        {
            visitedNodes.insert( current_node.node );
            for ( int i = 0; i < current_node.node->num_conn(); ++i )
            {
                MNode* new_node = current_node.node->get_conn( i );
                if ( visitedNodes.count( new_node ) == 0 )
                {
                    AStarNode new_aNode( new_node, 0 );
                    new_aNode.cost = current_node.cost + calc_conn_cost( current_node, new_aNode );
                    paths.push_back( new_aNode );
                    parentNodes.insert( std::make_pair( new_node, current_node.node ) );
                }
            }

            // sort, lowest cost last
            std::sort( paths.begin(), paths.end(), [this] ( AStarNode t1, AStarNode t2 ) {
                return calc_cost( t1 ) > calc_cost( t2 );
            } );

            if ( paths.size() == 0 )
            {
                std::cout << "Cannot solve maze!" << std::endl;
                return;
            }

            current_node = paths.back();
            paths.pop_back();
            _steps++;
        }
        std::cout << "Solved maze in " << _steps << " steps!" << std::endl;
    }

    std::cout << "Drawing solution..." << std::endl << std::endl;

    // find end node
    auto it_end = std::find_if( _mNodes.begin(), _mNodes.end(), [this]( MNode m ) {
        return m.get_pos() == this->_maze->get_end();
    } );
    assert( it_end != _mNodes.end() );

    MNode* c_node = &(*it_end);

    while ( c_node->get_pos() != _maze->get_start() )
    {
        MNode* target_node = parentNodes[c_node];
        assert( target_node->get_pos() != c_node->get_pos() );
        int x_steps = std::abs( target_node->x - c_node->x );
        int y_steps = std::abs( target_node->y - c_node->y );
        int steps = x_steps + y_steps;
        int x_sign = x_steps > 0 ? (target_node->x - c_node->x) / x_steps : 0;
        int y_sign = y_steps > 0 ? (target_node->y - c_node->y) / y_steps : 0;

        Pos pos = c_node->get_pos();
        for ( int i = 0; std::abs( i ) < steps; i += x_sign + y_sign )
        {
            pos.first += x_sign;
            pos.second += y_sign;
            if ( pos != _maze->get_start() )
            {
                _maze->set_tile( pos, Tiles::Solution );
            }
        }
        assert( pos == target_node->get_pos() );
        c_node = target_node;
    }
    std::cout << *_maze << std::endl;
}

void AStarSolver::generate_nodes ()
{
    std::vector<std::unordered_set<Dir>> dirSets;

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

            std::unordered_set<Dir> dirs;

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

    /*for ( auto&& node : _mNodes )
    {
        _maze->set_tile( make_pos( node.x, node.y ), Tiles::Solution );
    }*/

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

void AStarSolver::delete_endpoints ()
{
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

float AStarSolver::calc_cost ( AStarNode n ) const
{
    Pos a = n.node->get_pos();
    Pos b = _maze->get_end();
    return std::sqrt( std::pow( static_cast<float>(a.first - b.first), 2.0 ) + std::pow( static_cast<float>(a.second - b.second), 2.0 ) ) + static_cast<float>(n.cost);
}

float AStarSolver::calc_conn_cost ( AStarNode a, AStarNode b ) const
{
    Pos e = a.node->get_pos();
    Pos f = b.node->get_pos();
    return std::abs( e.first - f.first ) + std::abs( e.second - f.second );
}
