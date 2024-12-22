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
    return currentMap[player.x][player.y];
}