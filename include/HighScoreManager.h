#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>

class Highscoremanager {

private:
	
	std::vector<int> m_Highscores;
	std::string m_Filename;
	
	static const int MAX_SCORES = 10;

private:

	void SortScores();
	bool ValidateScores(int score);

public:
	Highscoremanager(const std::string& filename = "highscores.txt");
	~Highscoremanager();

	bool LoadHighscores();
	bool SaveHighscores();
	void AddScores(int scores);

	int GetHighscore() const;
	int GetRank(int score);
	std::vector<int> GetTopScores(int count = MAX_SCORES) const;

	void ClearHighscores();
	bool IsNewHighscore(int score);
	void PrintHighscores() const;
};