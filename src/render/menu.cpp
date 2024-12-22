#include "menu.h"
#include <SFML/Graphics.hpp>

int Menu::updateSelection(int options, int change)
{
    return (selection + change) % options;
}
