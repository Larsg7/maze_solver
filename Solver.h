#ifndef MAZESOLVER_SOLVER_H
#define MAZESOLVER_SOLVER_H


#include "Maze.h"

enum class Dir
{
    N,
    E,
    W,
    S,
    None
};

const std::vector<Dir> dirVector { Dir::N, Dir::S, Dir::W, Dir::E };


class Solver
{
public:
    Solver () {}

    Solver ( Maze* _maze ) : _maze( _maze ) {}

    virtual void solve() = 0;

    Pos step_dir ( Pos& pos, Dir d ) const
    {
        Pos p = pos;
        switch ( d )
        {
            case Dir::N:
                p.first--;
                break;
            case Dir::S:
                p.first++;
                break;
            case Dir::E:
                p.second++;
                break;
            case Dir::W:
                p.second--;
                break;
        }
        return p;
    }


protected:
    Maze* _maze;
};


#endif //MAZESOLVER_SOLVER_H
