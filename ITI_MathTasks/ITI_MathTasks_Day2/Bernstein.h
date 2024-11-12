#pragma once
//trying to implement Bernstein polynomials to solve bezier curve 
#include <SFML/Graphics.hpp>
#include "DraggabelPoint.h"

int factorial(float n);
float  binomialCoef(int n, int k);
float blendingFunc(int n, int k, float t);
sf::Vector2f bezierCurve(const std::vector<sf::Vector2f>& controlPoints, float t);
