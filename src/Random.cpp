#include "Random.h"
#include "SuffixArray.h"
#include "TernarySearchTree.h"
#include <fstream>
#include <random>

int random(int n) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, n - 1);
	return dis(gen);
}

std::string WOTD(const SuffixArray& SA) {
	std::string wotd;
	int n = SA.words.size();
	int i = random(n);
	wotd = SA.words[i];

	return wotd;
}

std::vector<QuestionGenerator> chooseCorrectWord(std::string filename, TST& TST)
{
	std::ifstream file;
	std::vector<std::string> words;
	file.open(filename);
	if (!file.is_open())
	{
		return {};
	}
	std::string word;
	while (std::getline(file, word))
	{
		words.push_back(word);
	}
	file.close();

	std::vector<QuestionGenerator> questions;
	while (!words.empty())
	{
		QuestionGenerator q;
		int i = random(words.size());
		std::vector<std::string> definitions = TST.search(words[i]);
		q.question = definitions[0];
		q.correctAnswerIndex = random(4);
		q.answers[q.correctAnswerIndex] = words[i];
		words.erase(words.begin() + i);
		for (int j = 0; j < 4; j++)
		{
			if (j != q.correctAnswerIndex)
			{
				int k = random(words.size());
				q.answers[j] = words[k];
				words.erase(words.begin() + k);
			}
		}
		questions.push_back(q);
	}

	return questions;
}

std::vector<QuestionGenerator> chooseCorrectDefinition(std::string filename, TST& TST)
{
	std::ifstream file;
	std::vector<std::string> words;
	file.open(filename);
	if (!file.is_open())
	{
		return {};
	}
	std::string word;
	while (std::getline(file, word))
	{
		words.push_back(word);
	}
	file.close();

	std::vector<QuestionGenerator> questions;
	while (!words.empty())
	{
		QuestionGenerator q;
		int i = random(words.size());
		q.question = words[i];
		std::vector<std::string> definitions = TST.search(words[i]);
		q.correctAnswerIndex = random(4);
		q.answers[q.correctAnswerIndex] = definitions[0];
		words.erase(words.begin() + i);
		for (int j = 0; j < 4; j++)
		{
			if (j != q.correctAnswerIndex)
			{
				int k = random(words.size());
				std::vector<std::string> defs = TST.search(words[k]);
				q.answers[j] = defs[0];
				words.erase(words.begin() + k);
			}
		}
		questions.push_back(q);
	}

	return questions;
}

QuestionGenerator chooseCorrectWord(const SuffixArray& SA, TST& TST)
{
	std::string word = WOTD(SA);
	std::vector<std::string> definitions = TST.search(word);
	QuestionGenerator q;
	q.question = definitions[0];
	q.correctAnswerIndex = random(4);
	q.answers[q.correctAnswerIndex] = word;
	for (int i = 0; i < 4; i++)
	{
		if (i != q.correctAnswerIndex)
		{
			std::string wotd = WOTD(SA);
			while (wotd == word)
			{
				wotd = WOTD(SA);
			}
			q.answers[i] = wotd;
		}
	}

	return q;
}

QuestionGenerator chooseCorrectDefinition(const SuffixArray& SA, TST& TST)
{
	std::string word = WOTD(SA);
	std::vector<std::string> definitions = TST.search(word);
	QuestionGenerator q;
	q.question = word;
	q.correctAnswerIndex = random(4);
	q.answers[q.correctAnswerIndex] = definitions[0];
	for (int i = 0; i < 4; i++)
	{
		if (i != q.correctAnswerIndex)
		{
			std::string wotd = WOTD(SA);
			while (wotd == word)
			{
				wotd = WOTD(SA);
			}
			std::vector<std::string> defs = TST.search(wotd);
			q.answers[i] = defs[0];
		}
	}

	return q;
}
