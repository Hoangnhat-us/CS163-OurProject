#pragma once

#include <string>
#include <vector>
#include <wx/grid.h>

class HistoryManager {
public:
    void addHistory(const std::string& word, const std::vector<std::string>& definitions);
    void saveHistory(const std::string& filename) const;
    void loadHistory(const std::string& filename);
    void viewHistory(wxGrid* historyGrid) const;

private:
    std::vector<std::pair<std::string, std::vector<std::string>>> history;
};
