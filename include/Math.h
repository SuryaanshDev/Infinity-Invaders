#pragma once
#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>
#include <SFML/Graphics.hpp>

class Math {

private:

	std::vector<sf::Vector2f> vertices;

public:

	Math();
	~Math();

	//-----------------------Vector math functions----------------------
	inline float Dot(const sf::Vector2f& objA, const sf::Vector2f& objB);
	inline sf::Vector2f Perpendicular(const sf::Vector2f& vertex);
	inline sf::Vector2f Normalize(const sf::Vector2f& vertex);
	//--------------------------------------------------------------------
	
	static bool IsColliding(const sf::FloatRect& rect1, const sf::FloatRect& rect2);
};