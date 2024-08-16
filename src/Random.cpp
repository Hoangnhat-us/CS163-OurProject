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

std::vector<std::pair<std::string, std::vector<std::string>>> WOTD(SuffixArray& sa, TST& tst) {
	std::vector<std::pair<std::string, std::vector<std::string>>> wotd;

	int n = sa.words.size();

	for (int i = 0; i < 5; i++) {
		int index = random(n);
		std::string word = sa.words[index];
		// Check if the word is already in the vector
		bool found = false;
		for (const auto& w : wotd) {
			if (w.first == word) {
				found = true;
				break;
			}
		}
		if (found) {
			i--;
			continue;
		}
		std::vector<std::string> meanings = tst.search(word);
		wotd.push_back(std::make_pair(word, meanings));
	}

	return wotd;
}