#include "include/Player.h"
#include <iostream>
#include "include/Math.h"
#include "include/EnemySpawner.h"

Player::Player(int width, int height, float speed)
	: m_PlayerWidth(width), m_PlayerHeight(height), m_PlayerSpeed(speed), m_PlayerHealth(3),
	m_PlayerSprite(m_PlayerTexture), m_FireCooldown(0.15f), m_FireTimer(0.0f)
{
}

Player::~Player()
{
}

void Player::Initialize()
{

	m_PlayerSprite.setScale({4, 4});
	m_PlayerSprite.setPosition({850, 850});
}

void Player::Load() {
	
	int xIndex = 0;
	int yIndex = 0;

	if (!m_PlayerTexture.loadFromFile("resources/Plane-Sheet.png")) {
		
		std::cerr << "Error loading player sprite!" << std::endl;
	}

	else {

		std::cout << "Player sprite loaded successfully :)" << std::endl;
	}
	
	m_PlayerSprite.setTexture(m_PlayerTexture);

	sf::IntRect spriteRect({ xIndex * m_PlayerWidth, yIndex * m_PlayerHeight }, { m_PlayerWidth , m_PlayerHeight });

	m_PlayerSprite.setTextureRect(spriteRect);
}

void Player::Update(double deltaTime, EnemySpawner& spawner)
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

	auto& enemy = spawner.GetEnemies();
	
	for (auto& bullet : bullets) {
		
		bullet->Update(deltaTime);
	}

	std::vector<int> bulletsToRemove;

	for (int i = 0; i < bullets.size(); i++) {

		if (bullets[i]->GetPosition().y < -1920) {
			
			bulletsToRemove.push_back(i);
			continue;
		}

		for (auto& e : enemy) {

			if (Math::IsColliding(bullets[i]->GetBounds(), e->GetBounds())) {
			
				e->SetHealth(-1);
				bulletsToRemove.push_back(i);
				bullets.erase(bullets.begin() + i);
				std::cout << "Enemy Health: " << e->GetHealth() << std::endl;
				break;
			}
		}
	}

	std::sort(bulletsToRemove.rbegin(), bulletsToRemove.rend());

	for (int i : bulletsToRemove) {
		
		if (i >= 0 && i < bullets.size()) {
			
			bullets.erase(bullets.begin() + i);
			std::cout << "Bullet : " << i << "deleted" << std::endl;
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

int Player::GetHealth() const
{

	return m_PlayerHealth;
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
