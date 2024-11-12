#pragma once
#include <SFML/Graphics.hpp>

class DraggabelPoint {
public:
	sf::CircleShape shape;
	bool isDragging = false;

	void beginDrag(const sf::Vector2i& mousePos);
	void drag(const sf::Vector2i& mousePos);
	void endDrag();
	sf::Vector2f getPosition();

	DraggabelPoint(const sf::Vector2f& position);

};
