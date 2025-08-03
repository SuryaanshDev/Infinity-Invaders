#include <iostream>
#include "include/Menu.h"

Menu::Menu()
	:m_Selected(0), m_Play(m_Font), m_Instruction(m_Font), m_Exit(m_Font), m_InMenu(true), m_InInstructions(false)
{
	
	if (!m_Font.openFromFile("resources/pixel.ttf")) {

		std::cerr << "Failed to load menu font!" << std::endl;
	}

	else {

		std::cout << "Loaded the menu font successfully :)" << std::endl;
		
		m_Play.setFont(m_Font);
		m_Play.setString("Play");
		m_Play.setCharacterSize(90);
		m_Play.setPosition({300, 1080/4});

		m_Instruction.setFont(m_Font);
		m_Instruction.setString("Instruction");
		m_Instruction.setCharacterSize(90);
		m_Instruction.setPosition({300, 1080/(4) + 200});
		
		m_Exit.setFont(m_Font);
		m_Exit.setString("Exit");
		m_Exit.setCharacterSize(90);
		m_Exit.setPosition({300, 1080/(4) + 400});

		UpdateColors();
	}
}

Menu::~Menu() 
{

}

void Menu::Update()
{
	static bool upPressed = false;
	static bool downPressed = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {

		if (!downPressed) {

			MoveDown();
			downPressed = true;
		}
	}

	else {

		downPressed = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {

		if (!upPressed) {

			MoveUp();
			upPressed = true;
		}
	}

	else {

		upPressed = false;
	}
}

void Menu::Draw(sf::RenderWindow& window)
{

	window.draw(m_Play);
	window.draw(m_Instruction);
	window.draw(m_Exit);
}

void Menu::MoveUp() 
{
	
	m_Selected = (m_Selected + 2) % 3;
	UpdateColors();
}

void Menu::MoveDown() 
{
	
	m_Selected = (m_Selected + 1) % 3;
	UpdateColors();
}

void Menu::SetSelected(int number)
{
	m_Selected = number;
}

void Menu:: Pressed() 
{
	
	static bool enterPressed = false;
	static bool escPressed = false;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
		
		if (!enterPressed) {
			
			enterPressed = true;
			
			if (m_Selected == 0) { m_InMenu = false; m_InInstructions = false; }
			else if (m_Selected == 1) { m_InMenu = false; m_InInstructions = true; }
			else if (m_Selected == 2) { exit(0); }
		}
	}

	else {

		enterPressed = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
		
		if (!escPressed && !m_InMenu) {
			
			escPressed = true;
			m_InMenu = true;
			m_InInstructions = false;
		}
	}

	else {

		escPressed = false;
	}
}

bool Menu::InMenu() {

	return m_InMenu;
}

bool Menu::InInstructions()
{
	return m_InInstructions;
}

void Menu::UpdateColors()
{

	m_Play.setFillColor(m_Selected == 0 ? sf::Color::Magenta : sf::Color::White);
	m_Instruction.setFillColor(m_Selected == 1 ? sf::Color::Magenta : sf::Color::White);
	m_Exit.setFillColor(m_Selected == 2 ? sf::Color::Magenta : sf::Color::White);
}
