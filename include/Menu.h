#pragma once

#include <SFML/Graphics.hpp>

class Menu {

private:

	int m_Selected;
	sf::Font m_Font;

public:

	sf::Text m_Play;
	sf::Text m_Instruction;
	sf::Text m_Exit;
	bool m_InMenu;
	bool m_InInstructions;

	bool m_EnterPressed = false;

public:

	Menu();
	~Menu();

	void Update();
	void Draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void SetSelected(int number);
	void Pressed();
	bool InMenu();
	bool InInstructions();

	void UpdateColors();

	void SetInMenu(bool set);

public:

	bool IsPlayPressed();
	void ClearSelection();
	bool IsInstructionsPressed();
};