#include <SFML/Graphics.hpp>
#include "DraggabelPoint.h"
#include "Bernstein.h"

//numper of control points in bezierCurve
#define curvePoints 30

sf::Color operator*(float value, sf::Color color)
{
    return sf::Color(color.r * value, color.g * value, color.b * value);
}

template<class T>T lerp(const T& start, const T& end, float alpha = 0.5)
{
    if (alpha <= 0) return T(start);
    if (alpha >= 1) return T(end);
    return (1 - alpha) * start  + alpha * end ;
}

//this can be optimized using "de Casteljau Algorithm"
void updateCurve(sf::VertexArray& curve, const std::vector<DraggabelPoint>& points)
{
    float curvePointsCount = curve.getVertexCount();
    float delta = 1 / (curvePointsCount-1);
    std::vector<sf::Vector2f> controlPoints;

    for (int j = 0; j < points.size(); j++)
    {
        controlPoints.push_back(points[j].shape.getPosition());
    }
    float t = 0;
    for (int i = 0; i < curvePointsCount; i++)
    {
        curve[i].position = bezierCurve(controlPoints, t);
        curve[i].color = lerp(sf::Color(254, 138, 24), sf::Color(0, 255, 255), t);
        t += delta;
    }
}

int main()
{

    int pointsCount;
    printf("enter 0 to quit\nEnter controling points count: ");
    scanf_s("%d", &pointsCount);
    if (pointsCount == 0)return 0;

    sf::RenderWindow window(sf::VideoMode(800,600), "Bezier Curve Visualization");
    
    std::vector<DraggabelPoint> points;

    sf::VertexArray curve(sf::LineStrip, curvePoints);

    for(int i = 0;i < pointsCount; i++)
    {
        points.push_back(DraggabelPoint(sf::Vector2f( 400/(pointsCount+1) *(i+1) , 300/(pointsCount+1) * (i+1))));
    }

    sf::VertexArray line(sf::LineStrip, pointsCount);

    sf::Clock clock;
    float deltaTime;
    float circleSpeed = 20;
    sf::CircleShape circle(20);
    circle.setOrigin(20, 20);
    bool isMoving = false;
    float indx = 0;
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
                for (int i = 0; i < pointsCount; i++)
                {
                    points[i].beginDrag(sf::Mouse::getPosition(window));
                }
                break;
            case sf::Event::MouseButtonReleased:
                for (int i = 0; i < pointsCount; i++)
                {
                    points[i].endDrag();
                }
                break;
            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    isMoving = true;
                break;
            }
        }
        if (sf::Mouse::isButtonPressed)
        {
            for (int i = 0; i < pointsCount; i++)
            {
                points[i].drag(sf::Mouse::getPosition(window));
                line[i].position = points[i].getPosition();
            }
        }
        deltaTime = clock.restart().asSeconds();

        updateCurve(curve,points);
        if (isMoving)
        {
            indx += (deltaTime * circleSpeed);
            if (indx >= curvePoints-1)
            {
                isMoving = false;
                indx = 0;
            }
            else
            {
                //fmod(indx,1) for smother circle movement
                circle.setPosition(lerp(curve[indx].position, curve[indx + 1].position,fmod(indx,1)));
                circle.setFillColor(curve[indx].color);
            }
        }
        window.clear();
        
        window.draw(curve);
        if(isMoving)
        window.draw(circle);
        for (int i = 0;i < pointsCount; i++)
        {
            window.draw(points[i].shape);
        }
        window.draw(line);
        window.display();
    }
    main();

    return 0;
}