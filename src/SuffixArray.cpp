#include <algorithm>
#include <cassert>
#include <codecvt>
#include <locale>

#include "SuffixArray.h"

std::ifstream in;
std::ofstream out;

SuffixArray::SuffixArray(initType iType, dictType dType)
{
	if (iType == Cur)
	{
		if (dType == EE)
		{

			std::string filename = "Data_Storage/Eng2Eng/Current/eng2eng.txt";
			loadCSV(filename);

		}
		else if (dType == EV)
		{

			std::string filename = "Data_Storage/Eng2Viet/Current/eng2viet.txt";
			loadCSV(filename);

		}
		else if (dType == VE)
		{

			std::string filename = "Data_Storage/Viet2Eng/Current/viet2eng.txt";
			loadCSV(filename);

		}
		else if (dType == SLANG)
		{
			std::string filename = "Data_Storage/Slang/Current/slangs.txt";
			loadCSV(filename);
		}
		else if (dType == EMOJI)
		{
			std::string filename = "Data_Storage/Emoji/Current/emoji_df.txt";
			loadCSV(filename);
		}
	}
	else if (iType == Origin)
	{
		if (dType == EE)
		{
			for (int i = 1; i <= 28; i++)
			{
				std::string filename = "Data_Storage/Eng2Eng/Origin/" + std::to_string(i) + ".txt";
				loadCSV(filename);
			}
		}
		else if (dType == EV)
		{
			for (int i = 1; i <= 28; i++)
			{
				std::string filename = "Data_Storage/Eng2Viet/Origin/" + std::to_string(i) + ".txt";
				loadCSV(filename);
			}
		}
		else if (dType == VE)
		{
			for (int i = 1; i <= 25; i++)
			{
				std::string filename = "Data_Storage/Viet2Eng/Origin/" + std::to_string(i) + ".txt";
				loadCSV(filename);
			}
		}
		else if (dType == SLANG)
		{
			std::string filename = "Data_Storage/Slang/Origin/slangs.txt";
			loadCSV(filename);
		}
		else if (dType == EMOJI)
		{
			std::string filename = "Data_Storage/Emoji/Origin/emoji_df.txt";
			loadCSV(filename);
		}
	}
	text.push_back(U'$');
	int n = text.length();

	std::vector<int> s(n + 3);
	std::vector<int> SA(n + 3);

	for (int i = 0; i < n; ++i)
	{
		s[i] = static_cast<unsigned int>(text[i]);
	}

	SA_.resize(n + 3);

	makeSuffixArray(s, SA, n, 65536);

	for (int i = 0; i < SA_.size(); i++)
	{
		SA_[i] = SA[i];
	}
}

void SuffixArray::rebuildSuffixArray()
{
	int n = text.length();

	std::vector<int> s(n + 3);
	std::vector<int> SA(n + 3);

	for (int i = 0; i < n; ++i)
	{
		s[i] = static_cast<unsigned int>(text[i]);
	}

	SA_.resize(n + 3);

	makeSuffixArray(s, SA, n, 65536);

	for (int i = 0; i < SA_.size(); i++)
	{
		SA_[i] = SA[i];
	}
}

void SuffixArray::loadCSV(std::string filename)
{
	in.open(filename);
	if (!in.is_open())
	{
		return;
	}
	std::string line;
	while (std::getline(in, line))
	{
		if (line.empty()) continue;

		std::string key;
		std::u32string definition;

		size_t i = 0;
		while (i < line.size())
		{
			if ((line[i] == '\t' || line[i] == ' ') && line[i + 1] == '(')
			{
				break;
			}
			if (i == 0)
			{
				key.push_back(tolower(line[i]));
			}
			else key.push_back(line[i]);
			i++;
		}
		i++;

		fix_utf8_string(line);
		definition = utf8::utf8to32(line.substr(i, line.size() - i));
		wordStartIndices.push_back(text.size());
		words.push_back(key);
		text += definition;
		std::u32string endSign = U"|";
		text += endSign;
	}
	in.close();
}

std::vector<std::string> SuffixArray::search(const std::string& pattern) {
	std::u32string pattern_ = utf8::utf8to32(pattern);
	int n = text.size();
	int m = pattern_.size();
	std::vector<int> result;

	int left = 0, right = n;

	// ind the first occurrence of the pattern
	while (left < right) {
		int mid = (left + right) / 2;
		std::u32string suffix = text.substr(SA_[mid], m);
		if (suffix < pattern_) {
			left = mid + 1;
		}
		else {
			right = mid;
		}
	}

	// Collect all occurrences of the pattern
	while (left < n && text.substr(SA_[left], m) == pattern_) {
		result.push_back(SA_[left]);
		left++;
	}

	std::vector<std::string> meanings;
	// Limit the number of results to 10
	int count = 0;

	// Collect and print the results between start and end
	for (int i = 0; i < result.size() && count < 10; ++i) {
		// Assuming `indWordStartIndices` and `wordStartIndices` are deined elsewhere
		// and that they provide the starting index of words in the text.
		int wordIndex = findWordStartIndices(result[i]);
		if (wordIndex != -1) {
			int wordStart = wordStartIndices[wordIndex];
			int wordEnd = text.find(U'|', wordStart);
			std::string key = words[wordIndex];
			if (wordEnd != std::u32string::npos) {
				std::u32string foundWord = text.substr(wordStart, wordEnd - wordStart);
				meanings.push_back(key + ":\t" + utf8::utf32to8(foundWord));
				count++;
			}
		}
	}

	return meanings;
}

void SuffixArray::insert(const std::string& word, const std::string& definition)
{
	std::string key = word;
	std::u32string definition_ = utf8::utf8to32(definition);
	words.push_back(key);
	// Remove '$' from the end of the text
	text.pop_back();
	wordStartIndices.push_back(text.size());
	text += definition_;
	std::u32string endSign = U"|$";
	text += endSign;
}

bool SuffixArray::remove(const std::string& word)
{
	std::string key = word;
	int index = -1;
	for (int i = 0; i < words.size(); i++)
	{
		if (words[i] == key)
		{
			index = i;
			break;
		}
	}
	if (index == -1)
	{
		return false;
	}
	int start = wordStartIndices[index];
	int end = text.find(U'|', start);
	words.erase(words.begin() + index);
	wordStartIndices.erase(wordStartIndices.begin() + index);
	while (words[index] == key) {
		end = text.find(U'|', end + 1);
		words.erase(words.begin() + index);
		wordStartIndices.erase(wordStartIndices.begin() + index);
	}

	text.erase(start, end - start + 1);
	int n = end - start + 1;
	for (int i = 0; i < wordStartIndices.size(); i++)
	{
		if (wordStartIndices[i] > start)
		{
			wordStartIndices[i] -= n;
		}
	}

	return true;
}

bool SuffixArray::update(const std::string& word, const std::string& definition)
{
	std::string key = word;
	int index = -1;
	for (int i = 0; i < words.size(); i++)
	{
		if (words[i] == key)
		{
			index = i;
			break;
		}
	}
	if (index == -1)
	{
		return false;
	}
	int start = wordStartIndices[index];
	int end = text.find(U'|', start);
	while (words[index] == key) {
		end = text.find(U'|', end + 1);
		index++;
	}
	//text.erase(start, end - start + 1);
	std::u32string definition_ = utf8::utf8to32(definition) + U'|';
	text.replace(start, end - start + 1, definition_);

	return true;
}

void SuffixArray::saveToBF(const std::string& filename) const
{
	out.open(filename, std::ios::binary);
	if (!out.is_open())
	{
		return;
	}
	// Serialize the object
	int textSize = text.size() * sizeof(char32_t);
	out.write(reinterpret_cast<const char*>(&textSize), sizeof(textSize));
	out.write((char*)&text[0], text.size());

	int SASize = SA_.size();
	out.write(reinterpret_cast<const char*>(&SASize), sizeof(SASize));
	out.write((char*)&SA_[0], SA_.size() * sizeof(int));

	int wordStartIndicesSize = wordStartIndices.size();
	out.write(reinterpret_cast<const char*>(&wordStartIndicesSize), sizeof(wordStartIndicesSize));
	out.write((char*)&wordStartIndices[0], wordStartIndices.size() * sizeof(int));

	int wordsSize = words.size();
	out.write(reinterpret_cast<const char*>(&wordsSize), sizeof(wordsSize));

	for (const auto& word : words)
	{
		int wordSize = word.size();
		out.write(reinterpret_cast<const char*>(&wordSize), sizeof(wordSize));
		out.write(reinterpret_cast<const char*>(&word[0]), wordSize);
	}

	out.close();
}

void SuffixArray::loadFromBF(const std::string& filename)
{
	in.open(filename, std::ios::binary);
	if (!in.is_open())
	{
		return;
	}
	// Deserialize the object
	int textSize;
	in.read(reinterpret_cast<char*>(&textSize), sizeof(textSize));
	text.resize(textSize / sizeof(char32_t));
	in.read(reinterpret_cast<char*>(&text[0]), textSize);

	int SASize;
	in.read(reinterpret_cast<char*>(&SASize), sizeof(SASize));
	SA_.resize(SASize);
	in.read(reinterpret_cast<char*>(&SA_[0]), SASize * sizeof(int));

	int wordStartIndicesSize;
	in.read(reinterpret_cast<char*>(&wordStartIndicesSize), sizeof(wordStartIndicesSize));
	wordStartIndices.resize(wordStartIndicesSize);
	in.read(reinterpret_cast<char*>(&wordStartIndices[0]), wordStartIndicesSize * sizeof(int));

	int wordsSize;
	in.read(reinterpret_cast<char*>(&wordsSize), sizeof(wordsSize));
	words.resize(wordsSize);
	for (auto& word : words)
	{
		int wordSize;
		in.read(reinterpret_cast<char*>(&wordSize), sizeof(wordSize));
		word.resize(wordSize);
		in.read(reinterpret_cast<char*>(&word[0]), wordSize);
	}

	in.close();
}


void SuffixArray::makeSuffixArray(const std::vector<int>& s, std::vector<int>& SA, int n, int K)
{
	int n0 = (n + 2) / 3;
	int n1 = (n + 1) / 3;
	int n2 = n / 3;
	int t = n0 - n1;
	int n12 = n1 + n2 + t;

	std::vector<int> s12(n12 + 3);
	std::vector<int> SA12(n12 + 3);
	std::vector<int> s0(n0);
	std::vector<int> SA0(n0);

	for (int i = 0, j = 0; i < n + t; ++i)
	{
		if (i % 3 != 0)
		{
			s12[j++] = i;
		}
	}

	int K12 = assignNames(s, s12, SA12, n0, n12, K);

	computeS12(s12, SA12, n12, K12);
	computeS0(s, s0, SA0, SA12, n0, n12, K);
	merge(s, s12, SA, SA0, SA12, n, n0, n12, t);
}

int SuffixArray::assignNames(const std::vector<int>& s, std::vector<int>& s12, std::vector<int>& SA12, int n0, int n12, int K)
{
	radixPass(s12, SA12, s, 2, n12, K);
	radixPass(SA12, s12, s, 1, n12, K);
	radixPass(s12, SA12, s, 0, n12, K);

	int name = 0;
	int c0 = -1;
	int c1 = -1;
	int c2 = -1;
	for (int i = 0; i < n12; ++i)
	{
		if (s[SA12[i]] != c0 || s[SA12[i] + 1] != c1 || s[SA12[i] + 2] != c2)
		{
			++name;
			c0 = s[SA12[i]];
			c1 = s[SA12[i] + 1];
			c2 = s[SA12[i] + 2];
		}
		if (SA12[i] % 3 == 1)
		{
			s12[SA12[i] / 3] = name;
		}
		else
		{
			s12[SA12[i] / 3 + n0] = name;
		}
	}
	return name;
}

void SuffixArray::radixPass(const std::vector<int>& in, std::vector<int>& out, const std::vector<int>& s, int offset, int n, int K)
{
	std::vector<int> count(K + 2);
	for (int i = 0; i < n; ++i)
	{
		++count[s[in[i] + offset] + 1];
	}

	for (int i = 1; i <= K + 1; ++i)
	{
		count[i] += count[i - 1];
	}
	for (int i = 0; i < n; ++i)
	{
		out[count[s[in[i] + offset]]++] = in[i];
	}
}

void SuffixArray::radixPass(const std::vector<int>& in, std::vector<int>& out, const std::vector<int>& s, int n, int K)
{
	radixPass(in, out, s, 0, n, K);
}

void SuffixArray::computeS12(std::vector<int>& s12, std::vector<int>& SA12, int n12, int K12)
{
	if (K12 == n12)
	{
		for (int i = 0; i < n12; ++i)
		{
			SA12[s12[i] - 1] = i;
		}
	}
	else
	{
		makeSuffixArray(s12, SA12, n12, K12);
		for (int i = 0; i < n12; ++i)
		{
			s12[SA12[i]] = i + 1;
		}
	}
}

void SuffixArray::computeS0(const std::vector<int>& s, std::vector<int>& s0, std::vector<int>& SA0, const std::vector<int>& SA12, int n0, int n12, int K)
{
	for (int i = 0, j = 0; i < n12; ++i)
	{
		if (SA12[i] < n0)
		{
			s0[j++] = 3 * SA12[i];
		}
	}
	radixPass(s0, SA0, s, n0, K);
}

void SuffixArray::merge(const std::vector<int>& s, const std::vector<int>& s12, std::vector<int>& SA, const std::vector<int>& SA0, const std::vector<int>& SA12, int n, int n0, int n12, int t)
{
	int p = 0;
	int k = 0;
	while (t != n12 && p != n0)
	{
		int i = getIndexIntoS(SA12, t, n0);
		int j = SA0[p];

		if (suffix12IsSmaller(s, s12, SA12, n0, i, j, t))
		{
			SA[k++] = i;
			++t;
		}
		else
		{
			SA[k++] = j;
			++p;
		}
	}
	while (p < n0)
	{
		SA[k++] = SA0[p++];
	}
	while (t < n12)
	{
		SA[k++] = getIndexIntoS(SA12, t++, n0);
	}
}

int SuffixArray::getIndexIntoS(const std::vector<int>& SA12, int t, int n0)
{
	if (SA12[t] < n0)
	{
		return SA12[t] * 3 + 1;
	}
	else
	{
		return (SA12[t] - n0) * 3 + 2;
	}
}

bool SuffixArray::leq(int a1, int a2, int b1, int b2)
{
	return (a1 < b1 || (a1 == b1 && a2 <= b2));
}

bool SuffixArray::leq(int a1, int a2, int a3, int b1, int b2, int b3)
{
	return (a1 < b1 || (a1 == b1 && leq(a2, a3, b2, b3)));
}

bool SuffixArray::suffix12IsSmaller(const std::vector<int>& s, const std::vector<int>& s12, const std::vector<int>& SA12, int n0, int i, int j, int t)
{
	if (SA12[t] < n0)
	{
		return leq(s[i], s12[SA12[t] + n0], s[j], s12[j / 3]);
	}
	else
	{
		return leq(s[i], s[i + 1], s12[SA12[t] - n0 + 1], s[j], s[j + 1], s12[j / 3 + n0]);
	}
}

int SuffixArray::findWordStartIndices(int suffixStart)
{
	for (int i = 0; i < wordStartIndices.size(); ++i)
	{
		if (suffixStart >= wordStartIndices[i] && (i == wordStartIndices.size() - 1 || suffixStart < wordStartIndices[i + 1]))
		{
			return i;
		}
	}
	return -1;
}

void fix_utf8_string(std::string& str)
{
	std::string temp;
	utf8::replace_invalid(str.begin(), str.end(), back_inserter(temp));
	str = temp;
}