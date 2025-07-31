#pragma once
#include<SFML/Graphics.hpp>

class Enemy {
	
private:
	float m_EnemySpeed;
	int m_EnemyHealth;
	sf::Texture m_EnemyTexture;
	sf::Sprite m_EnemySprite;
	sf::RectangleShape m_BoundingRectangle;

	bool m_IsDead;

public:
	
	Enemy();
	~Enemy();

	void Initialize();
	void Load();
	void Update(double deltaTime);
	void Draw(sf::RenderWindow& window);
	void SetHealth(int hp);

	bool IsDead() const;
	void MarkDead();
// Getters and Setters 
public:
	
	int GetHealth() const;
	void SetSpeed(float speed);
	void SetPosition(const sf::Vector2f& pos);
	sf::Vector2f GetPosition() const;
	sf::FloatRect GetBounds() const;
};