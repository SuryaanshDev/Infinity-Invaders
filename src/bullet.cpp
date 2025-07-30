#include "include/Bullet.h"
#include <iostream>

Bullet::Bullet()
	: m_BulletSpeed(500.0f), offset({55, 0})
{
}

Bullet::~Bullet() {

}

void Bullet:: Load() {
	
}

void Bullet::Initialize(const sf::Vector2f& position) {
	
	m_Bullet.setSize({10.0, 30.0});
	m_Bullet.setFillColor(sf::Color::Red);
	m_Bullet.setPosition(position + offset);
}

void Bullet::Update(double deltaTime) {
	
	m_Bullet.move({0, -m_BulletSpeed * (float)deltaTime});
}

void Bullet::Draw(sf::RenderWindow& window) {
	
	window.draw(m_Bullet);
}

sf::Vector2f Bullet::GetPosition()
{

	return m_Bullet.getPosition();
}

sf::FloatRect Bullet::GetBounds() const {

	return m_Bullet.getGlobalBounds();
}
