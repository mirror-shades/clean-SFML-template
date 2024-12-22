#pragma once
#include "colors.h"

class Tile
{
public:
    char symbol;
    Color color;
    bool walkable;

    Tile(char symbol = ' ', Color color = Color::WHITE, bool walkable = true)
        : symbol(symbol), color(color), walkable(walkable) {}
};