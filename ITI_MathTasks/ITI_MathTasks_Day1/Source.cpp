#include <SFML/Graphics.hpp>

#define Window_W 800
#define Window_H 600

int main()
{
    sf::RenderWindow window(sf::VideoMode(Window_W, Window_H), "Main Window");
    window.setFramerateLimit(30);

    while (window.isOpen())
    {
        // Check for all window events
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }
        window.clear();

        window.display();
    }

    return 0;
}