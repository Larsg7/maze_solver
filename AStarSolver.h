#ifndef MAZESOLVER_ASTARSOLVER_H
#define MAZESOLVER_ASTARSOLVER_H


#include "Solver.h"
#include "Node.h"

struct AStarNode
{
    AStarNode ( MNode* nodePtr, float cost ) : node( nodePtr ), cost( cost )
    {}

    MNode* node;
    float cost;
};

class AStarSolver : public Solver
{
public:
    AStarSolver ( Maze* _maze );

    virtual void solve () override;

private:
    void generate_nodes ();

    void delete_endpoints ();

    float calc_cost ( AStarNode a ) const;

    float calc_conn_cost ( AStarNode a, AStarNode b ) const;

    std::vector<MNode> _mNodes;

    int _steps;
};


#endif //MAZESOLVER_ASTARSOLVER_H
