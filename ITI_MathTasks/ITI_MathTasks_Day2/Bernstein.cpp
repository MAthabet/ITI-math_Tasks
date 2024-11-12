//trying to implement Bernstein polynomials to solve bezier curve 
#include "Bernstein.h"

int factorial(int n)
{
	if (n < 2) return 1;
	return n * factorial(n - 1);
}
float  binomialCoef(int n, int k)
{
	return  factorial(n)/ factorial(k)/ factorial(n-k);
}
float blendingFunc(int n, int k, float t)
{
	return binomialCoef(n, k)* pow(t, k)* pow(1 - t, n - k);
}
sf::Vector2f bezierCurve(const std::vector<sf::Vector2f>& controlPoints, float t)
{
	int n = controlPoints.size()-1;
	sf::Vector2f B(0,0);

	for (int k = 0; k < n+1; k++)
	{
		B += blendingFunc(n, k, t) * controlPoints[k];
	}
	return B;
}
