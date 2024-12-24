#pragma once
#include "tile.h"
#include "player.h"

static constexpr int SQUARE_SIZE = 50;
static constexpr int MAP_WIDTH = 24;
static constexpr int MAP_HEIGHT = 16;

struct Map
{
    Tile tiles[MAP_WIDTH][MAP_HEIGHT];
};

class MapHandler
{
public:
    Tile getCurrentTile(int x, int y) const;
    bool isValidMove(int x, int y) const;
    Map *getCurrentMap();
    void setCurrentMap(Map newMap);

private:
    Map currentMap;
};