#include "include/HighScoreManager.h"
#include <sstream>
#include <iomanip>

void Highscoremanager::SortScores()
{

	std::sort(m_Highscores.begin(), m_Highscores.end(), std::greater<int>());
}

bool Highscoremanager::ValidateScores(int score)
{

	return score >= 0 && score <= 999999;
}

Highscoremanager::Highscoremanager(const std::string& filename)
	: m_Filename(filename)
{
}

Highscoremanager::~Highscoremanager()
{
	SaveHighscores();
}

bool Highscoremanager::LoadHighscores()
{
	m_Highscores.clear();

	std::ifstream file(m_Filename);
	
	if (!file.is_open()) {
		
		std::cout << "No existing highscore file found. Creating new one." << std::endl;
		
		return true;
	}

	std::string line;
	while (std::getline(file, line) && m_Highscores.size() < MAX_SCORES) {
		
		try {

			line.erase(0, line.find_first_not_of(" \t\r\n"));
			line.erase(line.find_last_not_of(" \t\r\n") + 1);

			if (!line.empty()) {
				
				int score = std::stoi(line);

				if (ValidateScores(score)) { m_Highscores.push_back(score); }
			}
		}

		catch (const std::exception& e) {
		
			std::cerr << "Error parsing score line: " << line << " - " << e.what() << std::endl;
			continue;
		}

		file.close();
		SortScores();

		std::cout << "Loaded" << m_Highscores.size() << "highscores successfully." << std::endl;
		return true;
	}
}

bool Highscoremanager::SaveHighscores()
{

	std::ofstream file(m_Filename);
	
	if (!file.is_open()) {
		
		std::cerr << "Error: Could not save highscores to file: " << m_Filename << std::endl;
		return false;
	}

	SortScores();

	for (const int& score : m_Highscores) {
			
		file << score << std::endl;
	}

	file.close();
	std::cout << "Highscores saved successfully." << std::endl;

	return true;
}

void Highscoremanager::AddScores(int score)
{

	if (!ValidateScores(score)) {
		
		std::cerr << "Invalid Score: " << score << std::endl;
		return;
	}

	m_Highscores.push_back(score);
	SortScores();

	if (m_Highscores.size() > MAX_SCORES) {
		
		m_Highscores.resize(MAX_SCORES);
	}

	std::cout << "Score" << score << "added to highscores." << std::endl;
}

int Highscoremanager::GetHighscore() const
{
	if (m_Highscores.empty()) { return 0; }

	return m_Highscores[0];
}

int Highscoremanager::GetRank(int score)
{
	if (!ValidateScores(score)) {
		
		return 0;
	}

	for (size_t i = 0; i < m_Highscores.size(); ++i) {
		
		if (score >= m_Highscores[i]) return static_cast<int>(i + 1);
	}

	return 0;
}

std::vector<int> Highscoremanager::GetTopScores(int count) const
{

	std::vector<int> topScores;
	int limit = std::min(count, static_cast<int>(m_Highscores.size()));

	for (int i = 0; i < limit; i++) {
		
		topScores.push_back(m_Highscores[i]);
	}

	return topScores;
}

void Highscoremanager::ClearHighscores()
{

	m_Highscores.clear();
	SaveHighscores();
	std::cout << "All highscores cleared" << std::endl;
}

bool Highscoremanager::IsNewHighscore(int score)
{
	
	if (!ValidateScores(score)) {
		
		return false;
	}

	if (m_Highscores.size() < MAX_SCORES) {
		
		return true;
	}

	return score > m_Highscores.back();
}

void Highscoremanager::PrintHighscores() const
{

	std::cout << "\n=== HIGHSCORES ===" << std::endl;
	
	for (size_t i = 0; i < m_Highscores.size(); i++) {
		
		std::cout << std::setw(2) << (i + 1) << ". " << std::setw(8) << m_Highscores[i] << std::endl;
	}

	std::cout << "==================\n" << std::endl;
}
