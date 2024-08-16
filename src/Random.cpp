#include "Random.h"
#include "SuffixArray.h"
#include "TernarySearchTree.h"
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