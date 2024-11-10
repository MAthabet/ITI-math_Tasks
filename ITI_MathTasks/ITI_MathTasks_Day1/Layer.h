#pragma once
#include <SFML/Graphics.hpp>

class Layer
{
public:
	Layer(std::string filePath, float speed);
	void draw(sf::RenderWindow* window, float deltaTime);

private:
	float offest = 0;
	sf::Texture layer;
	float layerSpeed;
	sf::Sprite sprite;
};

