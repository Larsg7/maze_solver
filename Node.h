#ifndef MAZESOLVER_NODE_H
#define MAZESOLVER_NODE_H

#include <utility>
#include <vector>

struct MNode
{
    MNode ( int x, int y ) : x ( x ), y ( y )
    {}

    const int x;
    const int y;

    unsigned long num_conn ()
    {
        return connections.size();
    }

    void add_conn ( MNode* m )
    {
        connections.push_back( m );
    }

    MNode* get_conn ( unsigned num )
    {
        return connections[num];
    }

private:
    std::vector<MNode*> connections;
};

#endif //MAZESOLVER_NODE_H
