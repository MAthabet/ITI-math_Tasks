#include "DraggabelPoint.h"
DraggabelPoint::DraggabelPoint(const sf::Vector2f& position)
{
	shape = sf::CircleShape(10);
	shape.setOrigin(10, 10);
	shape.setPosition(position);
}

void DraggabelPoint::beginDrag(const sf::Vector2i& mousePos)
{
	isDragging = shape.getGlobalBounds().contains((sf::Vector2f)mousePos);
}

void DraggabelPoint::drag(const sf::Vector2i& mousePos)
{
	if (!isDragging) return;
	shape.setPosition((sf::Vector2f)mousePos);
}

void DraggabelPoint::endDrag()
{
	isDragging = false;
}

sf::Vector2f DraggabelPoint::getPosition()
{
	return shape.getPosition();
}