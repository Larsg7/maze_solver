#ifndef MAZESOLVER_ASTARSOLVER_H
#define MAZESOLVER_ASTARSOLVER_H


#include "Solver.h"
#include "Node.h"

class AStarSolver : public Solver
{
public:
    AStarSolver ( Maze* _maze );

    virtual void solve () override;

private:
    void generate_nodes ();

    std::vector<MNode> _mNodes;

    int _steps;
};


#endif //MAZESOLVER_ASTARSOLVER_H
