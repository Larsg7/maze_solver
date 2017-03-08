#include <iostream>
#include <cassert>
#include <algorithm>
#include "FillSolver.h"

FillSolver::FillSolver ( Maze* _maze )
        : Solver( _maze )
{}

void FillSolver::solve ()
{
    // empty containers
    _visited.erase( _visited.begin(), _visited.end() );
    {
        decltype( _crossings ) empty;
        decltype( _solCrossingsDir ) empty2;
        _crossings.swap( empty );
        _solCrossingsDir.swap( empty2 );
    }

    // set up _visited
    for ( int i = 0; i < _maze->get_maze().size(); ++i )
    {
        _visited.push_back( std::vector<bool>( _maze->get_maze()[i].size() ) );
        std::fill( _visited[i].begin(), _visited[i].end(), false );
    }

    _pos = _maze->get_start();
    _steps = 0;

    while ( _pos != _maze->get_end() )
    {
        Dir new_dir;
        unsigned count = 0;
        for ( auto&& d : dirVector )
        {
            Pos p = step_dir( _pos, d );
            if ( _maze->get_maze()[p.first][p.second] != Tiles::Wall
                 && ! _visited[p.first][p.second] )
            {
                new_dir = d;
                count++;
            }
            if ( _maze->get_maze()[p.first][p.second] == Tiles::End )
            {
                new_dir = d;
            }
        }

        if ( count == 0 )
        {
            if ( _crossings.size() == 0 )
            {
                std::cout << "Cannot solve maze!" << std::endl;
                return;
            }
            if ( _pos == _crossings.top() )
            {
                _solCrossingsDir.pop_back();
                _crossings.pop();
            }
            _pos = _crossings.top();
        }
        else
        {
            if ( count > 1 )
            {
                if ( _crossings.size() == 0 || _pos != _crossings.top() )
                {
                    _crossings.push( _pos );
                    _solCrossingsDir.push_back( std::make_pair( _pos, new_dir ) );
                }
            }
            else if ( _solCrossingsDir.size() > 0 && _pos == _solCrossingsDir.back().first )
            {
                _solCrossingsDir.back().second = new_dir;
            }
            else if ( _pos == _maze->get_start() )
            {
                _solCrossingsDir.push_back( std::make_pair( _pos, new_dir ) );
            }

            _pos = step_dir( _pos, new_dir );
            _steps++;
        }
        _visited[_pos.first][_pos.second] = true;
    }
    fill_solution();
    std::cout << "Solved maze in " << _steps << " steps!" << std::endl << std::endl;
    std::cout << *_maze;
}



void FillSolver::fill_solution ()
{
    decltype( _solCrossingsDir ) revSolCrossing ( _solCrossingsDir.size() );
    std::reverse_copy( _solCrossingsDir.begin(), _solCrossingsDir.end(), revSolCrossing.begin() );
    _pos = step_dir( revSolCrossing.back().first, revSolCrossing.back().second );
    revSolCrossing.pop_back();

    while ( _pos != _maze->get_end() )
    {
        Dir new_dir = Dir::None;
        if ( revSolCrossing.size() > 0 && _pos == revSolCrossing.back().first )
        {
            new_dir = revSolCrossing.back().second;
            revSolCrossing.pop_back();
        }
        else
        {
            unsigned count = 0;
            for ( auto&& d : dirVector )
            {
                Pos p = step_dir( _pos, d );
                if ( _maze->get_maze()[p.first][p.second] != Tiles::Wall
                     && _maze->get_maze()[p.first][p.second] != Tiles::Solution )
                {
                    new_dir = d;
                    count++;
                }
                if ( _maze->get_maze()[p.first][p.second] == Tiles::End )
                {
                    new_dir = d;
                }
            }
            if ( new_dir == Dir::None || count != 1 )
            {
                std::cerr << "Error when trying to fill solution!" << std::endl;
                return;
            }
        }

        _maze->set_tile( _pos, Tiles::Solution );
        _pos = step_dir( _pos, new_dir );
        //std::cout << *_maze;
    }
}
