#pragma once

#include<algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

#include "utf8/utf8.h"
#include "utf8/utf8/cpp20.h"
#include"SuffixArray.h"



class TSTNode {
public:
	char32_t key;
	TSTNode* left;
	TSTNode* middle;
	TSTNode* right;
	int priority;
	bool is_end_of_string;
	std::vector<std::string> meaning;

	TSTNode(char32_t key)
		: key(key), left(nullptr), middle(nullptr), right(nullptr),
		priority(rand() % 100), is_end_of_string(false) {}
};

class TST {
private:
	TSTNode* root;
	// Helper function to insert a word into the TST
	TSTNode* _insert(TSTNode* node, const std::u32string& word, const std::string& meaning, int index);

	// Helper function to rebalance the TST
	TSTNode* _rebalance(TSTNode* node);

	// Helper function to perform a right rotation
	TSTNode* _right_rotate(TSTNode* node);

	// Helper function to perform a left rotation
	TSTNode* _left_rotate(TSTNode* node);

	// Helper function to search for a word and return its meaning
	std::vector<std::string> _search(TSTNode* node, const std::u32string& word, int index);

	TSTNode* _remove(TSTNode* node, const std::u32string& word, int index);

	TSTNode* _searchPrefix(TSTNode* node, const std::u32string& prefix, int index);

	void _collect(TSTNode* node, std::u32string prefix, std::vector<std::string>& result);
	//for collect only 20 keys
	void _collect2(TSTNode* node, std::u32string& prefix, std::vector<std::string>& result, int& cnt);

	int LevenshteinDistance(const std::u32string& s1, const std::u32string& s2);
	void suggestCorrectionsUtil(TSTNode* node, const std::u32string& prefix, const std::u32string& target, std::vector<std::string>& result, int maxDistance);
	void _deleteTree(TSTNode* node);
public:

	TST() : root(nullptr) {
		std::srand(std::time(nullptr));
	}
	/*~TST() {
		deleteTree();
	}*/
	void deleteTree();
	TSTNode* getRoot() { return root; }

	void insert(const std::string& word, const std::string& meaning);
	std::vector<std::string> search(const std::string& word);
	void loadfile(const std::string& filename);
	void remove(const std::string& word);
	std::vector<std::string> searchPrefix(const std::string& prefix);
	//for search prefix return only 20 word
	std::vector<std::string> searchPrefix2(const std::string& prefix);
	std::vector<std::string> suggestCorrections(const std::string& word, int maxDistance);
	void editMeaning(const std::string& word, const std::vector<std::string>& meaning);

};
void helptoSave2file(TST&tst, SuffixArray& SA, std::ofstream& fout);
void save2file(const std::string& pathname, TST &tst,SuffixArray&SA);

std::u32string to_utf32(const std::string& utf8_str);

std::string to_utf8(const std::u32string& utf32_str);