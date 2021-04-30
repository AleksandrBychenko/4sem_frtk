#include "level.h"

int main()
{
    Level level;
    level.LoadFromFile("map.tmx");

    sf::RenderWindow window;
    window.create(sf::VideoMode(1000, 1000), "Level.h test");

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        level.Draw(window);
        window.display();
    }

    return 0;
}
