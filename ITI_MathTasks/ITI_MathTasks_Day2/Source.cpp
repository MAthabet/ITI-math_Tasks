#include <SFML/Graphics.hpp>

#define PI 3.14159265

template<class T>T lerp(const T& start, const T& end, float alpha = 0.5)
{
    if (alpha <= 0) return T(start);
    if (alpha >= 1) return T(end);
    return (1 - alpha) * start  + alpha * end ;
}
//in deg
float angleBetween(sf::Vector2f a, sf::Vector2f b)
{
    return -(180/PI) * atan2( a.y-b.y,a.x-b.x ); //+Y is pointing down in sfml
}
float distanceBetween(sf::Vector2f a, sf::Vector2f b)
{
    return sqrt((a.x - b.x)* (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
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
int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "FOV Window");
    int r = 30;
    int FOVr = 10 * r;
    sf::CircleShape taregetCircle(r);
    taregetCircle.setOrigin(r, r);
    taregetCircle.setFillColor(sf::Color::Cyan);
    taregetCircle.setPosition(600,150);
    sf::Vector2f edges[] =
    {
        sf::Vector2f(0, -r),
        sf::Vector2f(0, r),
        sf::Vector2f(-r, 0),
        sf::Vector2f(r, 0)
    };
    sf::CircleShape radarCircle = taregetCircle;
    radarCircle.setFillColor(sf::Color::Green);
    radarCircle.setPosition(200,450);

    sf::ConvexShape FOV(30);
    
    float deltaTime = 0;
    sf::Clock clock;
    float speed = 10000;
    float arcAngle = 45;
    float angle;
    // Run the program as long as the window is open
    while (window.isOpen())
    {
        // Check for all window events
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                case sf::Keyboard::W:
                    radarCircle.move(0,-speed*deltaTime);
                    break;
                case sf::Keyboard::Down:
                case sf::Keyboard::S:
                    radarCircle.move(0, speed * deltaTime);
                    break;
                case sf::Keyboard::Right:
                case sf::Keyboard::D:
                    radarCircle.move(speed * deltaTime, 0);
                    break;
                case sf::Keyboard::Left:
                case sf::Keyboard::A:
                    radarCircle.move(-speed * deltaTime, 0);
                    break;
                case sf::Keyboard::Q:
                    if(arcAngle < 180-5)
                    arcAngle += 5;
                    break;
                case sf::Keyboard::E:
                    if (arcAngle > 5)
                    arcAngle -= 5;
                    break;
                default:
                    break;
                }
            }
        }
        
        angle = angleBetween((sf::Vector2f)sf::Mouse::getPosition(window), radarCircle.getPosition());
        updateArc(FOV, radarCircle.getPosition(),FOVr,angle-arcAngle,angle+arcAngle);
        FOV.setFillColor(sf::Color::White);
        //check collision
        if (distanceBetween(radarCircle.getPosition(), taregetCircle.getPosition()) <= (FOVr + r))
        {
            float fov;
            for (int i = 0; i < 4;i++)
            {
                fov = angleBetween(taregetCircle.getPosition()+edges[i], radarCircle.getPosition());
                if (fov > angle - arcAngle && fov < angle + arcAngle)
                {
                    FOV.setFillColor(sf::Color(255,0,0,125));
                    break;
                }
            }
        }


        window.clear();
        window.draw(taregetCircle);
        window.draw(FOV);
        window.draw(radarCircle);
        deltaTime = clock.restart().asSeconds();
        window.display();
    }

    return 0;
}