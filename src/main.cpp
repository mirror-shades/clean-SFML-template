// Copyright 2024. mirror-shades. GPL-2.0 License.
/**
 * Tamerlane Chess - A historical chess variant from medieval Persia
 *
 * This is the main entry point for the Tamerlane Chess game, an implementation of a medieval
 * chess variant featuring unique pieces and rules. The game uses SFML for graphics rendering
 * and window management.
 *
 * The game implements an AI opponent using minimax with alpha-beta pruning and piece-square
 * tables for evaluation. Players can play against the AI or another human player.
 *
 * SFML dependencies are included in the external folder and configured in CMakeLists.txt
 */

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
