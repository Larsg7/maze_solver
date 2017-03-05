#ifndef MAZESOLVER_MAZE_H
#define MAZESOLVER_MAZE_H


#include <vector>
#include <string>

#define WALL 0
#define FLOOR 255

#define WALL_SYMBOL 'W'
#define FLOOR_SYMBOL '_'

class Maze
{
public:
    void load_textFile ( std::string& file );

    const std::vector<std::vector<bool>>& get_maze () const;

private:
    std::vector<std::vector<bool>> _maze;
};


#endif //MAZESOLVER_MAZE_H
