#include "include/Player.h"
#include <iostream>
#include "include/Math.h"
#include "include/EnemySpawner.h"

Player::Player(int width, int height, float speed)
	: m_PlayerWidth(width), m_PlayerHeight(height), m_PlayerSpeed(speed), m_PlayerHealth(5),
	m_PlayerSprite(m_PlayerTexture), m_FireCooldown(0.15f), m_FireTimer(0.0f),
	m_DamageCooldown(1.0f), m_DamageTimer(0.0f), m_PlayerScore(0), m_IsDead(false),
	m_ScreenWidth(1920), m_ScreenHeight(1080)
{
}

Player::~Player()
{
}

void Player::Initialize()
{

	m_PlayerHealth = 5;
	m_PlayerSprite.setScale({ 4, 4 });
	m_PlayerSprite.setPosition({ 850, 850 });
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

	if (IsDead()) {

		std::cout << "You Died Game Over!" << std::endl;
	}

	m_DamageTimer += deltaTime;

	sf::Vector2f position = m_PlayerSprite.getPosition();

	Move();

	m_FireTimer += deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && m_FireTimer >= m_FireCooldown) {

		auto bullet = std::make_unique<Bullet>();


		bullet->Initialize(position);

		bullets.push_back(std::move(bullet));

		m_FireTimer = 0.0f;
	}

	auto& enemy = spawner.GetEnemies();

	for (auto& bullet : bullets) {

		bullet->Update(deltaTime);
	}



	for (auto& e : enemy) {

		if (e->GetPosition().y > 1080 && m_DamageTimer >= m_DamageCooldown || Math::IsColliding(m_PlayerSprite.getGlobalBounds(), e->GetBounds()) &&
			m_DamageTimer >= m_DamageCooldown) {

			e->SetHealth(-1);
			TakeDamage(1);
			m_DamageTimer = 0.0f;
			continue;
		}
	}

	bullets.erase(
		std::remove_if(bullets.begin(), bullets.end(), [&](const std::unique_ptr<Bullet>& bullet) {

			if (bullet->GetPosition().y < -1920) {
				return true;
			}

			for (auto& e : enemy) {
				if (Math::IsColliding(bullet->GetBounds(), e->GetBounds())) {

					e->SetHealth(-1);

					//------------------------------------------------Score Logic--------------------------------
					if (e->GetHealth() <= 0 && !e->IsDead()) {
						SetScore(1);
						e->MarkDead();
					}
					//------------------------------------------------------------------------------------------
					std::cout << "Enemy Health: " << e->GetHealth() << std::endl;
					return true; 
				}
			}

			return false;
			}),
		bullets.end()
	);
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

void Player::TakeDamage(int dmg)
{

	m_PlayerHealth -= dmg;

	if (m_PlayerHealth <= 0) {

		m_PlayerHealth = 0;
		m_IsDead = true;
		std::cout << "Player damaged!\n" << "Health: " << m_PlayerHealth << std::endl;
	}
}

void Player::Move() {

	sf::Vector2f currentPos = m_PlayerSprite.getPosition();
	sf::Vector2f newPos = currentPos;

	float spriteWidth = m_PlayerWidth * m_PlayerSprite.getScale().x;
	float spriteHeight = m_PlayerHeight * m_PlayerSprite.getScale().y;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		newPos.y -= m_PlayerSpeed;

		if (newPos.y < 0) {
			newPos.y = 0;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		newPos.y += m_PlayerSpeed;

		if (newPos.y + spriteHeight > m_ScreenHeight) {
			newPos.y = m_ScreenHeight - spriteHeight;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		newPos.x -= m_PlayerSpeed;

		if (newPos.x + spriteWidth < 0) {
			newPos.x = m_ScreenWidth;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		newPos.x += m_PlayerSpeed;

		if (newPos.x > m_ScreenWidth) {
			newPos.x = -spriteWidth;
		}
	}

	m_PlayerSprite.setPosition(newPos);
}

bool Player::IsDead()
{
	return m_IsDead;
}

void Player::Reset()
{

	m_IsDead = false;
	m_PlayerHealth = 5;
	m_PlayerSprite.setPosition({ 850, 850 });
	m_PlayerScore = 0; 
	bullets.clear();
	Initialize();
}

void Player::SetScore(int score)
{

	m_PlayerScore += score;
}

int Player::GetScore() const {

	return m_PlayerScore;
}

void Player::SetScreenDimensions(int width, int height)
{
	m_ScreenWidth = width;
	m_ScreenHeight = height;
}
