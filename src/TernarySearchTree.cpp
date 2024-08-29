#include"TernarySearchTree.h"
#include <iostream>
#include <stack>

TSTNode* TST::_insert(TSTNode* node, const std::u32string& word, const std::string& meaning, int index) {
    char32_t char_key = word[index];

    if (node == nullptr) {
        node = new TSTNode(char_key);
    }

    if (char_key < node->key) {
        node->left = _insert(node->left, word, meaning, index);
    }
    else if (char_key > node->key) {
        node->right = _insert(node->right, word, meaning, index);
    }
    else {
        if (index + 1 == word.size()) {
            node->is_end_of_string = true;
            node->meaning.push_back(meaning);
        }
        else {
            node->middle = _insert(node->middle, word, meaning, index + 1);
        }
    }

    node = _rebalance(node);
    return node;
}

// Helper function to rebalance the TST
TSTNode* TST::_rebalance(TSTNode* node) {
    if (node == nullptr) {
        return node;
    }

    if (node->left && node->left->priority < node->priority) {
        node = _right_rotate(node);
    }
    else if (node->right && node->right->priority < node->priority) {
        node = _left_rotate(node);
    }

    return node;
}

// Helper function to perform a right rotation
TSTNode* TST::_right_rotate(TSTNode* node) {
    TSTNode* left_child = node->left;
    node->left = left_child->right;
    left_child->right = node;
    return left_child;
}

// Helper function to perform a left rotation
TSTNode* TST::_left_rotate(TSTNode* node) {
    TSTNode* right_child = node->right;
    node->right = right_child->left;
    right_child->left = node;
    return right_child;
}

std::vector<std::string> TST::_search(TSTNode* node, const std::u32string& word, int index) {
    if (node == nullptr) {
        return {};
    }
    char32_t char_key = word[index];

    if (char_key < node->key) {
        return _search(node->left, word, index);
    }
    else if (char_key > node->key) {
        return _search(node->right, word, index);
    }
    else {
        if (index + 1 == word.size()) {
            if (node->is_end_of_string) {
                return node->meaning;
            }
            else {
                return {};
            }
        }
        return _search(node->middle, word, index + 1);
    }
}

TSTNode* TST::_remove(TSTNode* node, const std::u32string& word, int index) {
    if (node == nullptr) {
        return nullptr;
    }

    char32_t char_key = word[index];

    if (char_key < node->key) {
        node->left = _remove(node->left, word, index);
    }
    else if (char_key > node->key) {
        node->right = _remove(node->right, word, index);
    }
    else {
        if (index + 1 == word.size()) {
            if (node->is_end_of_string) {
                node->is_end_of_string = false;
                node->meaning.clear();
            }
        }
        else {
            node->middle = _remove(node->middle, word, index + 1);
        }
    }

    if (node->left == nullptr && node->right == nullptr && node->middle == nullptr && !node->is_end_of_string) {
        delete node;
        return nullptr;
    }

    node = _rebalance(node);
    return node;
}

void TST::insert(const std::string& word, const std::string& meaning) {
    std::u32string word32 = to_utf32(word);
    root = _insert(root, word32, meaning, 0);
}

std::vector<std::string> TST::search(const std::string& word) {
    std::u32string word32 = to_utf32(word);
    return _search(root, word32, 0);
}

void TST::remove(const std::string& word) {
    std::u32string word32 = to_utf32(word);
    root = _remove(root,word32, 0);
}

TSTNode* TST::_searchPrefix(TSTNode* node, const std::u32string& prefix, int index) {
    if (node == nullptr) {
        return nullptr;
    }

    char32_t char_key = prefix[index];

    if (char_key < node->key) {
        return _searchPrefix(node->left, prefix, index);
    }
    else if (char_key > node->key) {
        return _searchPrefix(node->right, prefix, index);
    }
    else {
        if (index + 1 == prefix.size()) {
            return node;
        }
        return _searchPrefix(node->middle, prefix, index + 1);
    }
}

void TST::_collect(TSTNode* node, std::u32string prefix, std::vector<std::string>& result) {
    if (node == nullptr) {
        return;
    }

    _collect(node->left, prefix, result);
    prefix.push_back(node->key);

    if (node->is_end_of_string) {
        for (const auto& m : node->meaning) {
            result.push_back(to_utf8(prefix) + " " + m);
        }
    }

    _collect(node->middle, prefix, result);
    prefix.pop_back();
    _collect(node->right, prefix, result);
}

void TST::_collect2(TSTNode* node, std::u32string& prefix, std::vector<std::string>& result, int& cnt) {
    if (node == nullptr || cnt == 30) {
        return;
    }

    _collect2(node->left, prefix, result, cnt);
    prefix.push_back(node->key);

    if (node->is_end_of_string && cnt<=30) {
        result.push_back(to_utf8(prefix));
        cnt++;
    }

    _collect2(node->middle, prefix, result, cnt);
    prefix.pop_back();
    _collect2(node->right, prefix, result, cnt);
}

std::vector<std::string> TST::searchPrefix(const std::string& prefix) {
    std::vector<std::string> result;
    std::u32string prefix32 = to_utf32(prefix);
    TSTNode* node = _searchPrefix(root, prefix32, 0);

    if (node == nullptr) {
        return result;
    }

    std::u32string prefixx = prefix32;
    _collect(node->middle, prefixx, result);
    return result;
}

std::vector<std::string> TST::searchPrefix2(const std::string& prefix) {
    std::vector<std::string> result;
    std::u32string prefix32 = to_utf32(prefix);
    TSTNode* node = _searchPrefix(root, prefix32, 0);

    if (node == nullptr) {
        return result;
    }

    std::u32string prefixx = prefix32;
    int cnt = 0;
    _collect2(node->middle, prefixx, result, cnt);
    return result;
}

int TST::LevenshteinDistance(const std::u32string& s1, const std::u32string& s2) {
    int m = s1.size();
    int n = s2.size();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i == 0) {
                dp[i][j] = j;
            }
            else if (j == 0) {
                dp[i][j] = i;
            }
            else if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else {
                if (dp[i - 1][j] < dp[i][j - 1] && dp[i - 1][j] < dp[i - 1][j - 1])
                    dp[i][j] = 1 + dp[i - 1][j];
                else if (dp[i][j - 1] < dp[i - 1][j] && dp[i][j - 1] < dp[i - 1][j - 1])
                    dp[i][j] = 1 + dp[i][j - 1];
                else dp[i][j] = 1 + dp[i - 1][j - 1];
            }
        }
    }

    return dp[m][n];
}

void TST::suggestCorrectionsUtil(TSTNode* node, const std::u32string& prefix, const std::u32string& target, std::vector<std::string>& result, int maxDistance){
    if (node == nullptr) return;
    if (result.size() > 10) return;
    suggestCorrectionsUtil(node->left, prefix, target, result, maxDistance);

    std::u32string newPrefix = prefix + node->key;
    if (node->is_end_of_string) {
        int distance = LevenshteinDistance(newPrefix, target);
        if (distance <= maxDistance) {
            result.emplace_back(to_utf8(newPrefix));
        }
    }

    suggestCorrectionsUtil(node->middle, newPrefix, target, result, maxDistance);
    suggestCorrectionsUtil(node->right, prefix, target, result, maxDistance);
}

std::vector<std::string> TST::suggestCorrections(const std::string& word, int maxDistance) {
    std::vector<std::string> result;
    result.emplace_back("Did you mean: " + word + "?");
    std::u32string word32 = to_utf32(word);
    suggestCorrectionsUtil(root, U"", word32, result, maxDistance);
    return result;
}

void TST::loadfile(const std::string& filename) {
    std::ifstream fin;
    fin.open(filename);
    if (!fin.is_open())
    {
        return;
    }
    std::string line;
    while (getline(fin, line))
    {
        if (line.empty())
            continue;
        std::string key;
        std::string data;
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
        while (i < line.size())
        {
            data.push_back(line[i]);
            i++;
        }
        this->insert(key, data);
    }
    fin.close();
}


void save2file(const std::string& pathname, TST &tst,SuffixArray&SA) {
	std::ofstream fout;
	fout.open(pathname);
	if (!fout.is_open())
	{
		return;
	}
	helptoSave2file(tst,SA, fout);

}

void helptoSave2file(TST&tst, SuffixArray& SA, std::ofstream& fout) {
    std::string key = "";
    std::vector<std::string> prefix;
    for (int i = 0; i < SA.words.size(); i++) {
        if (SA.words[i] == key) continue;
		key = SA.words[i];
		prefix.push_back(key);
    }
	for (int i = 0; i < prefix.size(); i++) {
		std::vector<std::string> meaning = tst.search(prefix[i]);
		tst.remove(prefix[i]);
		for (const auto& m : meaning) {
			fout << prefix[i] << " " << m << "\n";
		}
	}
}
void TST::editMeaning(const std::string& word, const std::vector<std::string>& meaning) {
	std::u32string word32 = to_utf32(word);
	TSTNode* node = _searchPrefix(root, word32, 0);
	if (node == nullptr) {
		return;
	}

	node->meaning = meaning;
}


std::u32string to_utf32(const std::string& utf8_str) {
    std::u32string str = utf8::utf8to32(utf8_str);
    return str;
}

std::string to_utf8(const std::u32string& utf32_str) {
    std::string str = utf8::utf32to8(utf32_str);
    return str;
}

void TST::_deleteTree(TSTNode* node) {
	if (node == nullptr) {
		return;
	}
	_deleteTree(node->left);
	_deleteTree(node->middle);
	_deleteTree(node->right);
	delete node;
   
}

void TST::deleteTree() {
	_deleteTree(root);
	root = nullptr;
}