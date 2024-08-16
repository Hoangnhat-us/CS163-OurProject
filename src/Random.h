#pragma once
#include <string>
#include <vector>
#include <iostream>
#include"TernarySearchTree.h"
#include "SuffixArray.h"


int random(int n);

std::vector<std::pair<std::string, std::vector<std::string>>> WOTD(SuffixArray& sa, TST& tst);
