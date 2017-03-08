//
// Created by lars on 3/7/17.
//

#ifndef MAZESOLVER_FILLSOLVER_H
#define MAZESOLVER_FILLSOLVER_H


#include "Solver.h"


class FillSolver : public Solver
{
public:
    FillSolver ( Maze* _maze );

    virtual void solve () override;

private:

    void fill_solution ();

    std::vector<std::vector<bool>> _visited;
    std::stack<Pos> _crossings;
    std::vector<std::pair<Pos,Dir>> _solCrossingsDir;

    Pos _pos;
    int _steps;
};


#endif //MAZESOLVER_FILLSOLVER_H
