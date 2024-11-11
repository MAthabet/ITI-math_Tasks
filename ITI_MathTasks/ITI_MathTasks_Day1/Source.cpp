#include <SFML/Graphics.hpp>

#define Window_W 800
#define Window_H 600

#define PI 3.14159265
enum MouthDir {
    MouthRight = 0,
    MouthUp = 90,
    MouthLeft = 180,
    MouthDown = 270
};
// this function gets angle in degrees
// 90 deg is the +y axis (-y axis is sfml)
void updateArc(sf::ConvexShape& shape, const sf::Vector2f& center, float radius, float startAngle, float endAngle)
{
    int pointCount = shape.getPointCount() - 1;
    float deltaAngle = (startAngle - endAngle) / (pointCount - 1);
    deltaAngle *= (PI / 180);
    endAngle *= (PI / 180);

    sf::Vector2f point = center;
    for (;pointCount > 0; pointCount--)
    {
        point.x = center.x + radius * cos(endAngle);
        // inverted the y axis
        point.y = center.y - radius * sin(endAngle);
        shape.setPoint(pointCount, point);
        endAngle += deltaAngle;
    }
    shape.setPoint(0, center);
}
void PackMan(float Time, sf::ConvexShape& shape, const sf::Vector2f& center, float radius, float mouthAngle, MouthDir mouthDir, float frequency = 0.2)
{
    float startAngle = mouthAngle* abs(sin(Time* frequency * (180/PI)));

    updateArc(shape, center, radius, mouthDir +startAngle, 360+mouthDir-startAngle);
    
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(Window_W, Window_H), "Main Window");
    sf::ConvexShape arc(50);
    int r = 150;
    arc.setOrigin(r, r);
    arc.setPosition(Window_W / 2, Window_H / 2);

    arc.setFillColor(sf::Color::Yellow);
    sf::Clock clock;

    MouthDir mouthDir = MouthRight;

    while (window.isOpen())
    {
        // Check for all window events
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type)
            {
            case sf::Event::Closed :
                window.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Up :
                case sf::Keyboard::W :
                    mouthDir = MouthUp;
                    break;
                case sf::Keyboard::Down :
                case sf::Keyboard::S :
                    mouthDir = MouthDown;
                    break;
                case sf::Keyboard::Right :
                case sf::Keyboard::D :
                    mouthDir = MouthRight;
                    break;
                case sf::Keyboard::Left :
                case sf::Keyboard::A :
                    mouthDir = MouthLeft;
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }

        window.clear(sf::Color::Blue);
        PackMan(clock.getElapsedTime().asSeconds(), arc, arc.getOrigin(), r, 30, mouthDir);
        window.draw(arc);
        window.display();
    }

    return 0;
}