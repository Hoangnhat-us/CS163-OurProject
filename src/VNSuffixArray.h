#pragma once

#include <fstream>
#include <string>
#include <uni_algo/all.h>
#include <vector>

std::ifstream in;
std::ofstream out;


class VNSuffixArray
{
public:
	std::u16string text;
	std::vector<int> SA_;
	std::vector<int> wordStartIndices;
	std::vector<std::u32string> words;

	VNSuffixArray(initType iType, dictType dType);

	void loadCSV(std::string filename);
	std::vector<std::pair<std::u32string, std::u16string>> search(const std::u16string& pattern);
	void insert(const std::u32string& word, const std::u16string& definition);
	bool remove(const std::u32string& word);
	bool update(const std::u32string& word, const std::u16string& definition);
	void saveToBF(const std::string& filename) const;
	void loadFromBF(const std::string& filename);
	void end(bool isModified);

private:
	void makeSuffixArray(const std::vector<int>& s, std::vector<int>& SA, int n, int K);
	int assignNames(const std::vector<int>& s, std::vector<int>& s12, std::vector<int>& SA12, int n0, int n12, int K);
	void radixPass(const std::vector<int>& in, std::vector<int>& out, const std::vector<int>& s, int offset, int n, int K);
	void radixPass(const std::vector<int>& in, std::vector<int>& out, const std::vector<int>& s, int n, int K);
	void computeS12(std::vector<int>& s12, std::vector<int>& SA12, int n12, int K12);
	void computeS0(const std::vector<int>& s, std::vector<int>& s0, std::vector<int>& SA0, const std::vector<int>& SA12, int n0, int n12, int K);
	void merge(const std::vector<int>& s, const std::vector<int>& s12, std::vector<int>& SA, const std::vector<int>& SA0, const std::vector<int>& SA12, int n, int n0, int n12, int t);
	int getIndexIntoS(const std::vector<int>& SA12, int t, int n0);
	bool leq(int a1, int a2, int b1, int b2);
	bool leq(int a1, int a2, int a3, int b1, int b2, int b3);
	bool suffix12IsSmaller(const std::vector<int>& s, const std::vector<int>& s12, const std::vector<int>& SA12, int n0, int i, int j, int t);
	int findWordStartIndices(int suffixStart);
};
