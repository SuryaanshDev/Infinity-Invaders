#include "include/Math.h"

Math::Math()
{
}

Math::~Math()
{
}

inline float Math::Dot(const sf::Vector2f& objA, const sf::Vector2f& objB)
{
	return objA.x * objB.x + objA.y * objB.y;
}

inline sf::Vector2f Math::Perpendicular(const sf::Vector2f& vertex)
{
	return sf::Vector2f(-vertex.y, vertex.x);
}

inline sf::Vector2f Math::Normalize(const sf::Vector2f& vertex)
{

	float length = std::sqrt(vertex.x * vertex.x + vertex.y * vertex.y);
	return (length != 0)? vertex / length : sf::Vector2f(0.0f, 0.0f);
}

bool Math::IsColliding(const sf::FloatRect& rect1, const sf::FloatRect& rect2)
{
	return rect1.findIntersection(rect2).has_value();
}


