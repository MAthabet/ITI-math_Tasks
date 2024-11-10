#include <SFML/Graphics.hpp>

#include "Animation.h"

#define Window_W 400
#define Window_H 300
#define JUMP_PATH "./Resources/_Jump.png"
#define RUN_PATH "./Resources/_Run.png"

#define ANIMATION_SPF 0.0769

//TODO: create player class
float quad(float t,float a, float b, float c)
{
    
    return a*t*t + b*t + c;
}
/* case: jumping in 2D:
* when t = 0, then f(t) = c so c is the starting pos( and end pos in this case)
* when t = duration(T), then 0 = a t^2+b t then at = -b
* 2at+b = 0, then when t = -b/2a = T/2, then f(T/2) = c + h , -b = Ta
* a/4 T^2 + b T/2 = h, then a = -4h/T^2, b =4h/T
*/
// NOTE: jumping is moving in -Y in SFML
void jump(sf::RectangleShape* player, sf::Clock* clock,float* startY,float h = -10,float duration = 1.0f)
{
    float a =  (h / duration)* (- 4.0f / duration);
    float b = 4.0f* (h/ duration);
    float t = clock->getElapsedTime().asSeconds();

    player->setPosition(player->getPosition().x, quad(t, a, b, *startY));
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(Window_W, Window_H), "Main Window");

    sf::Texture Run;
    Run.loadFromFile(RUN_PATH);
    sf::Texture Jump;
    Jump.loadFromFile(JUMP_PATH);


    sf::RectangleShape player(sf::Vector2f(Run.getSize().x/10, Run.getSize().y/1));
    player.setTexture(&Run);
    player.setPosition(0, Window_H/2);

    Animation running(&Run, sf::Vector2u(10, 1), ANIMATION_SPF);
    Animation jumping(&Jump, sf::Vector2u(3, 1), 0.3334);

    float deltaTime;
    sf::Clock clock;
    sf::Clock jumpingClock;
    bool isJumping = false;
    float jumpingStartPos = player.getPosition().y;
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        // Check for all window events
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Space:
                {
                    if (isJumping == true) break;
                    else
                    {
                        isJumping = true;
                        jumpingStartPos = player.getPosition().y;
                        player.setTexture(&Jump);
                        jumpingClock.restart();
                    }
                    break;
                }
                default:
                    break;
                }
            default:
                break;
            }
        }
        if (isJumping)
        {
            if (jumpingClock.getElapsedTime().asSeconds() >= 1)
            {
                isJumping = false;
                player.setTexture(&Run);
            }
            jump(&player, &jumpingClock, &jumpingStartPos);
            jumping.Update(0, deltaTime);
            player.setTextureRect(jumping.uvRect);
        }
        else
        {
            running.Update(0, deltaTime);
            player.setTextureRect(running.uvRect);
        }
        window.clear(sf::Color::Magenta);
        window.draw(player);
        window.display();
    }

    return 0;
}