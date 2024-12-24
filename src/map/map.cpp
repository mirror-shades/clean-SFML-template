#include "tile.h"
#include "player.h"
#include "map.h"

#define SQUARE_SIZE 50

Tile currentMap[MAP_WIDTH][MAP_HEIGHT] = {};

// get current tile based on player position
Tile MapHandler::getCurrentTile(int x, int y) const
{
    return currentMap.tiles[x][y];
}

void MapHandler::setCurrentMap(Map newMap)
{
    for (int i = 0; i < MAP_WIDTH; i++)
    {
        for (int j = 0; j < MAP_HEIGHT; j++)
        {
            currentMap.tiles[i][j] = newMap.tiles[i][j];
        }
    }
}

Map *MapHandler::getCurrentMap()
{
    return &currentMap;
}

bool MapHandler::isValidMove(int x, int y) const
{
    // Check bounds
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
    {
        return false;
    }
    // Check if tile is walkable
    return currentMap.tiles[x][y].walkable;
}