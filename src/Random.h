#pragma once
#include "SuffixArray.h"
#include"TernarySearchTree.h"
#include <iostream>
#include <string>
#include <vector>


int random(int n);

std::string WOTD(const SuffixArray& SA);

class QuestionGenerator
{
public:
	std::string question;
	std::vector<std::string> answers;
	int correctAnswerIndex;
};

std::vector<QuestionGenerator> chooseCorrectWord(std::string filename, TST& TST); // EngEng, EngViet
std::vector<QuestionGenerator> chooseCorrectDefinition(std::string filename, TST& TST);
QuestionGenerator chooseCorrectWord(const SuffixArray& SA, TST& TST); // The rest
QuestionGenerator chooseCorrectDefinition(const SuffixArray& SA, TST& TST);