#include <SFML/Graphics.hpp>

#define Window_W 800
#define Window_H 600

#define PI 3.14159265
// this function gets angle in degrees
// 90 deg is the +y axis (-y axis is sfml)
void updateArc(sf::ConvexShape& shape, const sf::Vector2f& center, float radius, float startAngle, float endAngle)
{
    int pointCount = shape.getPointCount()-1;
    float deltaAngle = (startAngle - endAngle) / pointCount;
    deltaAngle *= (PI / 180);
    endAngle *= (PI / 180);

    sf::Vector2f point = center;
    for (;pointCount > -1; pointCount--)
    {
        point.x = center.x + radius * cos(endAngle);
        // inverted the y axis
        point.y = center.y - radius * sin(endAngle);
        shape.setPoint(pointCount, point);
        printf("angel %f , %f, %f, sin: %f\n", endAngle,point.x, point.y, sin(endAngle));
        endAngle += deltaAngle;
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(Window_W, Window_H), "Main Window");

    sf::ConvexShape arc(30);

    int r = 150;
    arc.setOrigin(r, r);
    arc.setPosition(Window_W / 2, Window_H / 2);

    updateArc(arc, arc.getOrigin(), r, 90, 270);

    arc.setFillColor(sf::Color::Yellow);
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
        window.draw(arc);
        window.display();
    }

    return 0;
}