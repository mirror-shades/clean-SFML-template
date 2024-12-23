#include "tile.h"
#include "player.h"
#include "map.h"

#define SQUARE_SIZE 50

const int MAP_WIDTH = 24;
const int MAP_HEIGHT = 16;

Tile currentMap[MAP_WIDTH][MAP_HEIGHT] = {};

// get current tile based on player position
Tile Map::getCurrentTile(Player &player)
{
    return currentMap[player.getPosition().first][player.getPosition().second];
}

bool Map::isValidMove(int x, int y)
{
    // Check bounds
    if (x < 0 || x >= 24 || y < 0 || y >= 16)
    {
        return false;
    }
    // Check if tile is walkable
    return currentMap[x][y].walkable;
}