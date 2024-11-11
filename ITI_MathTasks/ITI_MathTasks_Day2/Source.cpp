#include <SFML/Graphics.hpp>


template<class T>T lerp(const T& start, const T& end, float alpha = 0.5)
{
    if (alpha <= 0) return T(start);
    if (alpha >= 1) return T(end);
    return (1 - alpha) * start  + alpha * end ;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "Main Window");
    const int circlesCount = 7;
    int r = 10;
    std::vector<sf::CircleShape> circles;
    for(int i = 0;i < circlesCount; i++)
    {
        sf::CircleShape s(10);
        s.setFillColor(sf::Color::White);
        s.setPosition(0, 0);
        s.setOrigin(r, r);
        //to make color fade away
        float f = lerp(255, 0, (float)i * 1 / circlesCount);
        s.setFillColor(sf::Color( f, 0, 0));

        circles.push_back(s);
    }
    float deltaTime;
    float speed = 10;
    sf::Clock clock;

    // Run the program as long as the window is open
    while (window.isOpen())
    {
        // Check for all window events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Mouse mouse;
        deltaTime = clock.restart().asSeconds();
        circles[0].setPosition(lerp(circles[0].getPosition(), (sf::Vector2f)sf::Mouse::getPosition(window), deltaTime * speed));
        for (int i = 1;i < circlesCount; i++)
        {
            circles[i].setPosition(lerp(circles[i].getPosition(), circles[i-1].getPosition(), deltaTime * speed) );
        }
        window.clear();
        for (int i = 0;i < circlesCount; i++)
        {
            window.draw(circles[i]);
        }
        window.display();
    }

    return 0;
}