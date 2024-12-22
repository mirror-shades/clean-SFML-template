#pragma once
#include "tile.h"
#include "player.h"

class Map
{
public:
    // Size of each square/tile in pixels
    static constexpr int SQUARE_SIZE = 50;
    // Map dimensions in tiles
    static constexpr int MAP_WIDTH = 24;
    static constexpr int MAP_HEIGHT = 16;

    Tile currentMap[MAP_WIDTH][MAP_HEIGHT];

    Tile getCurrentTile(Player &player);
    bool isValidMove(int x, int y);
};