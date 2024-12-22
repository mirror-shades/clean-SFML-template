#pragma once

class Menu
{
public:
    int selection;
    int updateSelection(int options, int change, Menu &menu);
};