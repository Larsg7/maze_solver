#ifndef MAZESOLVER_MAZE_H
#define MAZESOLVER_MAZE_H


#include <vector>
#include <string>
#include <stack>
#include <map>

#define WALL_SYMBOL 'W'
#define FLOOR_SYMBOL '_'
#define START_SYMBOL 'S'
#define END_SYMBOL 'E'
#define SOLUTION_SYMBOL 'x'



enum class Tiles : char
{
    Wall = WALL_SYMBOL,
    Floor = FLOOR_SYMBOL,
    Start = START_SYMBOL,
    End = END_SYMBOL,
    Solution = SOLUTION_SYMBOL
};

typedef std::pair<int, int> Pos;
Pos make_pos ( int x, int y );

class Maze
{
public:
    Maze ();

    void load_textFile ( std::string& file );

    const std::vector<std::vector<Tiles>>& get_maze () const;

    const Pos& get_start () const;

    const Pos& get_end () const;

    void set_tile ( Pos p, Tiles t );

    friend std::ostream& operator<< ( std::ostream& io, Maze& m );

private:

    std::vector<std::vector<Tiles>> _maze;
    Pos _start;
    Pos _end;
};


#endif //MAZESOLVER_MAZE_H
