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

    Pos get_pos()
    {
        return std::make_pair( x, y );
    }

    void add_conn ( MNode* m )
    {
        connections.push_back( m );
    }

    MNode* get_conn ( unsigned num )
    {
        return connections[num];
    }

    void delete_node( MNode* m )
    {
        auto it = std::find( connections.begin(), connections.end(), m );
        if ( it != connections.end() )
        {
            connections.erase( it );
        }
    }

private:
    std::vector<MNode*> connections;
};

#endif //MAZESOLVER_NODE_H
