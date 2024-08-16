#pragma once

#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <codecvt>
#include <vector>
#include <Windows.h>
#include <fstream>
#include<algorithm>




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
   
public:
    
    TST() : root(nullptr) {
        std::srand(std::time(nullptr)); 
    }
    TSTNode* getRoot() { return root; }

    void insert(const std::string& word, const std::string& meaning);
    std::vector<std::string> search(const std::string& word);
    void loadCSV(const std::string& filename);
	void remove(const std::string& word);
	std::vector<std::string> searchPrefix(const std::string& prefix);
    //for search prefix return only 20 word
    std::vector<std::string> searchPrefix2(const std::string& prefix);
    std::vector<std::string> suggestCorrections(const std::string& word, int maxDistance);
	

};
void save2CSV(const std::string& filename, std::string prefix, std::ofstream& fout,TST tst);
void saveAll2csv(const std::string& pathname,TST tst);

std::u32string to_utf32(const std::string& utf8_str);

std::string to_utf8(const std::u32string& utf32_str);