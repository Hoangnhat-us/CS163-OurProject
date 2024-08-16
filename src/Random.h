#pragma once

#include "SuffixArray.h"
#include "TernarySearchTree.h"

int random(int n);

std::vector<std::pair<std::string, std::vector<std::string>>> WOTD(const SuffixArray& sa, const TST& tst);
