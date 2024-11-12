#include <SFML/Graphics.hpp>
#include "DraggabelPoint.h"

float operator*(sf::Vector2f a, sf::Vector2f b)
{
    return a.x * b.x + a.y * b.y;
}
float mag(sf::Vector2f a)
{
    return sqrt(a.x * a.x + a.y * a.y);
}
sf::Vector2f norm(sf::Vector2f a)
{
    return a/sqrt(a.x * a.x + a.y * a.y);
}
sf::Vector2f reflect(sf::Vector2f point, sf::VertexArray mirror)
{
    sf::Vector2f mirrorVec = mirror[1].position - mirror[0].position;
    sf::Vector2f vecMP(point.x - mirror[0].position.x, point.y - mirror[0].position.y);
    // normalized vector perpendicular to mirror
    sf::Vector2f mirrorNormal(norm(mirrorVec).y, -norm(mirrorVec).x);

    return point - (2.0f * (vecMP * mirrorNormal) * mirrorNormal);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mirror");

    DraggabelPoint points[5] = {
    DraggabelPoint(sf::Vector2f(200,100)),
    DraggabelPoint(sf::Vector2f(100,200)),
    DraggabelPoint(sf::Vector2f(100,300)),
    DraggabelPoint(sf::Vector2f(300,200)),
    DraggabelPoint(sf::Vector2f(300,400))
    };

    //just playing with colors
    sf::VertexArray triangle(sf::LineStrip, 4);
    points[0].shape.setFillColor(sf::Color::Magenta);
    points[1].shape.setFillColor(sf::Color::Cyan);
    points[2].shape.setFillColor(sf::Color::Green);

    sf::VertexArray mirror(sf::LineStrip, 2);
    mirror[0].color = sf::Color(212,225,236);
    mirror[1].color = sf::Color(212, 225, 236);

    points[3].shape.setFillColor(sf::Color(212, 225, 236));
    points[4].shape.setFillColor(sf::Color(212, 225, 236));

    sf::VertexArray reflectedTriangle(sf::Triangles, 3);
    reflectedTriangle[0].color = sf::Color::Magenta;
    reflectedTriangle[1].color = sf::Color::Cyan;
    reflectedTriangle[2].color = sf::Color::Green;

    // Run the program as long as the window is open
    while (window.isOpen())
    {
        // Check for all window events
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                for (int i = 0; i < 5; i++)
                {
                    points[i].beginDrag(sf::Mouse::getPosition(window));
                }
                break;
            case sf::Event::MouseButtonReleased:
                for (int i = 0; i < 5; i++)
                {
                    points[i].endDrag();
                }
                break;
            }
        }
        if (sf::Mouse::isButtonPressed)
        {
            for (int i = 0; i < 5; i++)
            {
                points[i].drag(sf::Mouse::getPosition(window));
                if(i<3)
                    triangle[i].position = points[i].getPosition();
                else
                    mirror[i-3].position = points[i].getPosition();
            }
            triangle[3].position = points[0].getPosition();
        }
        for (int i = 0;i < 3; i++)
        {
            reflectedTriangle[i].position = reflect(points[i].getPosition(), mirror);
        }
        window.clear();
        window.draw(mirror);
        window.draw(triangle);
        window.draw(reflectedTriangle);
        for (int i = 0;i < 5; i++)
        {
            window.draw(points[i].shape);
        }
        window.display();
    }
    main();

    return 0;
}