#pragma once
#include <string>
#include <vector>
#include <iostream>
#include"TernarySearchTree.h"
#include "SuffixArray.h"


int random(int n);

std::u32string WOTD(const VNSuffixArray& VSA);

class QuestionGenerator
{
	std::u32string question;
	std::vector<std::u32string> answers(4);
	int correctAnswerIndex;
};

std::vector<QuestionGenerator> chooseCorrectWord(std::string filename, const TernarySearchTree& TST);
std::vector<QuestionGenerator> chooseCorrectDefinition(std::string filename, const TernarySearchTree& TST);
QuestionGenerator chooseCorrectWord(const VNSuffixArray& VSA, const TernarySearchTree& TST);
QuestionGenerator chooseCorrectDefinition(const VNSuffixArray& VSA, const TernarySearchTree& TST);