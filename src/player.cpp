#include "include/Player.h"
#include <iostream>


Player::Player(int width, int height, float speed)
	: m_Width(width), m_Height(height), m_PlayerSpeed(speed), m_PlayerSprite(m_PlayerTexture),
	m_FireCooldown(0.15f), m_FireTimer(0.0f)
{
}

Player::~Player()
{
}

void Player::Initialize()
{

	m_PlayerSprite.setScale({4, 4});
}

void Player::Load() {
	
	int xIndex = 0;
	int yIndex = 0;

	if (!m_PlayerTexture.loadFromFile("resources/Plane-Sheet.png")) {
		
		std::cerr << "Error loading player sprite!" << std::endl;
	}

	else {

		std::cout << "Sprite loaded successfully :)" << std::endl;
	}
	
	m_PlayerSprite.setTexture(m_PlayerTexture);

	sf::IntRect spriteRect({ xIndex * m_Width, yIndex * m_Width }, { m_Width , m_Height });

	m_PlayerSprite.setTextureRect(spriteRect);
}

void Player::Update(double deltaTime)
{

	sf::Vector2f position = m_PlayerSprite.getPosition();

	Move();
	
	m_FireTimer += deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space ) && m_FireTimer >= m_FireCooldown){
		
		auto bullet = std::make_unique<Bullet>();
		
		
		bullet->Initialize(position);

		bullets.push_back(std::move(bullet));

		m_FireTimer = 0.0f;
	}
	
	for (auto& bullet : bullets) {
		
		bullet->Update(deltaTime);
	}

	for (int i = 0; i < bullets.size(); i++) {

		if (bullets[i]->GetPosition().y < -1920) {
			
			bullets.erase(bullets.begin() + i);
			std::cout << "Bullet " << i << " deleted" << std::endl;
		}
	}
}

void Player::Draw(sf::RenderWindow& window) 
{
	
	window.draw(m_PlayerSprite);
	
	for (auto& bullet : bullets) {
		
		bullet->Draw(window);
	}
}

void Player::Move() {
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		
		m_PlayerSprite.move({0, -m_PlayerSpeed});
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {

		m_PlayerSprite.move({0, m_PlayerSpeed});
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {

		m_PlayerSprite.move({-m_PlayerSpeed, 0});
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		
		m_PlayerSprite.move({m_PlayerSpeed, 0});
	}
}
