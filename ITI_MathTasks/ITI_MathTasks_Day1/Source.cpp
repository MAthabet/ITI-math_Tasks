#include <SFML/Graphics.hpp>
#include <math.h>
#define Window_W 800
#define Window_H 600
#define PI 22/7

float easeInOutCirc(float t, float b, float c, float d);

//to simplify the function reuse
sf::Vector2f positionEaseInOutSine(sf::Vector2f startPosition, sf::Vector2f endPosition, float time, float duartion);

int main()
{
    sf::RenderWindow window(sf::VideoMode(Window_W,Window_H), "Main Window");
    window.setFramerateLimit(30);

    int r = 20;
    float d = 3;
    float frameTime = 1 / 30;
    // this will use Sine easing
    sf::CircleShape sineCircle(2*r);
    sineCircle.setOrigin(r, r);
    sineCircle.setFillColor(sf::Color::Red);
    sineCircle.setPosition(0, 0);
    //this will use Circular easing
    sf::CircleShape circleCirc(2 * r);
    circleCirc.setOrigin(r, r);
    circleCirc.setFillColor(sf::Color::Blue);
    circleCirc.setPosition(0, 0);

    sf::Vector2f startPositionSine;
    sf::Vector2f startPositionCric;
    sf::Vector2f clickPosition;

    sf::Clock clock;
    float t;
    // Run the program as long as the window is open
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
            case sf::Event::MouseButtonReleased:
                clickPosition = (sf::Vector2f)sf::Mouse::getPosition(window);
                startPositionSine = sineCircle.getPosition();
                startPositionCric = circleCirc.getPosition();
                clock.restart();
                break;
            default:
                break;
            }
        }

        
        t = clock.getElapsedTime().asSeconds();
        if (t < d)
        {
            sineCircle.setPosition(positionEaseInOutSine(startPositionSine, clickPosition, t, d));
            float cX = clickPosition.x - startPositionCric.x;
            float cY = clickPosition.y - startPositionCric.y;
            circleCirc.setPosition(easeInOutCirc(t, startPositionCric.x, cX, d), easeInOutCirc(t, startPositionCric.y, cY, d));
        }
        sf::Vector2f a = circleCirc.getPosition();
        window.clear();

        window.draw(sineCircle);
        window.draw(circleCirc);

        window.display();
    }

    return 0;
}
float easeInOutCirc(float t, float b, float c, float d) 
{
    if ((t /= d / 2) < 1) return -c / 2 * (sqrt(1 - t * t) - 1) + b;
    return c / 2 * (sqrt(1 - t * (t -= 2)) + 1) + b;
}

sf::Vector2f positionEaseInOutSine(sf::Vector2f start, sf::Vector2f end, float time, float duration)
{
    sf::Vector2f distance = end - start;
    sf::Vector2f result;
    result.x = (distance.x / 2) * (1 - cos(PI * (time / duration))) + start.x;
    result.y = (distance.y / 2) * (1 - cos(PI * (time / duration))) + start.y;

    return result;
}