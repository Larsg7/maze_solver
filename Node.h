#ifndef MAZESOLVER_NODE_H
#define MAZESOLVER_NODE_H

#include <utility>
#include <algorithm>
#include <vector>

struct MNode
{
    MNode () : x ( 0 ), y ( 0 )
    {}

    MNode ( int x, int y ) : x ( x ), y ( y )
    {}

    MNode ( Pos p ) : x ( p.first ), y ( p.second )
    {}

    int x;
    int y;

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
        auto it = std::find_if( connections.begin(), connections.end(), [m]( MNode* M ) {
            return m == M;
        } );
        if ( it != connections.end() )
        {
            connections.erase( it );
        }
    }

    bool operator== ( MNode m )
    {
        return this->x == m.x && this->y == m.y;
    }

    bool operator== ( MNode* m )
    {
        return this->x == m->x && this->y == m->y;
    }

private:
    std::vector<MNode*> connections;
};

#endif //MAZESOLVER_NODE_H
