#include "Random.h"
#include "SuffixArray.h"
#include "TernarySearchTree.h"
#include <VNSuffixArray.h>
#include <fstream>
#include <random>

int random(int n) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, n - 1);
	return dis(gen);
}

std::u32string WOTD(const VNSuffixArray& VSA) {
	std::u32string wotd;
	int n = VSA.words.size();
	int i = random(n);
	wotd = VSA.words[i];

	return wotd;
}

std::vector<QuestionGenerator> chooseCorrectWord(std::string filename, const TernarySearchTree& TST)
{
	std::ifstream file;
	std::vector<std::u32string> words;
	file.open(filename);
	if (!file.is_open())
	{
		return;
	}
	std::u32string word;
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
		std::vector<std::u32string> definitions = TST.search(words[i]);
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

std::vector<QuestionGenerator> chooseCorrectDefinition(std::string filename, const TernarySearchTree& TST)
{
	std::ifstream file;
	std::vector<std::u32string> words;
	file.open(filename);
	if (!file.is_open())
	{
		return;
	}
	std::u32string word;
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
		std::vector<std::u32string> definitions = TST.search(words[i]);
		q.correctAnswerIndex = random(4);
		q.answers[q.correctAnswerIndex] = definitions[0];
		words.erase(words.begin() + i);
		for (int j = 0; j < 4; j++)
		{
			if (j != q.correctAnswerIndex)
			{
				int k = random(words.size());
				std::vector<std::u32string> defs = TST.search(words[k]);
				q.answers[j] = defs[0];
				words.erase(words.begin() + k);
			}
		}
		questions.push_back(q);
	}

	return questions;
}

QuestionGenerator chooseCorrectWord(const VNSuffixArray& VSA, const TernarySearchTree& TST)
{
	std::u32string word = WOTD(VSA);
	std::vector<std::u32string> definitions = TST.search(word);
	QuestionGenerator q;
	q.question = definitions[0];
	q.correctAnswerIndex = random(4);
	q.answers[q.correctAnswerIndex] = word;
	for (int i = 0; i < 4; i++)
	{
		if (i != q.correctAnswerIndex)
		{
			std::u32string wotd = WOTD(VSA);
			while (wotd == word)
			{
				wotd = WOTD(VSA);
			}
			q.answers[i] = wotd;
		}
	}

	return q;
}

QuestionGenerator chooseCorrectDefinition(const VNSuffixArray& VSA, const TernarySearchTree& TST)
{
	std::u32string word = WOTD(VSA);
	std::vector<std::u32string> definitions = TST.search(word);
	QuestionGenerator q;
	q.question = word;
	q.correctAnswerIndex = random(4);
	q.answers[q.correctAnswerIndex] = definitions[0];
	for (int i = 0; i < 4; i++)
	{
		if (i != q.correctAnswerIndex)
		{
			std::u32string wotd = WOTD(VSA);
			while (wotd == word)
			{
				wotd = WOTD(VSA);
			}
			std::vector<std::u32string> defs = TST.search(wotd);
			q.answers[i] = defs[0];
		}
	}

	return q;
}
