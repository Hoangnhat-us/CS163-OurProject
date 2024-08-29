#include "History.h"
#include <fstream>
#include <iostream>
#include <wx/wx.h>

void HistoryManager::addHistory(const std::string& word, const std::vector<std::string>& definitions) {
    history.emplace(history.begin(), word, definitions);
}

void HistoryManager::saveHistory(const std::string& filename) const {
    std::ofstream outFile(filename, std::ios::binary);
    if (outFile.is_open()) {
        size_t size = history.size();  // Correct size calculation
        outFile.write(reinterpret_cast<const char*>(&size), sizeof(size));

        for (const auto& pair : history) {
            size_t wordLength = pair.first.length();
            size_t numDefinitions = pair.second.size();

            outFile.write(reinterpret_cast<const char*>(&wordLength), sizeof(wordLength));
            outFile.write(pair.first.c_str(), wordLength);

            outFile.write(reinterpret_cast<const char*>(&numDefinitions), sizeof(numDefinitions));
            for (const auto& definition : pair.second) {
                size_t definitionLength = definition.length();
                outFile.write(reinterpret_cast<const char*>(&definitionLength), sizeof(definitionLength));
                outFile.write(definition.c_str(), definitionLength);
            }
        }
        outFile.close();
        
    }
    else {
        std::cerr << "Failed to open " << filename << std::endl;
    }
}

void HistoryManager::loadHistory(const std::string& filename) {
    history.clear();
    std::ifstream inFile(filename, std::ios::binary);
    if (inFile.is_open()) {
        size_t size;
        inFile.read(reinterpret_cast<char*>(&size), sizeof(size));

        for (size_t i = 0; i < size; ++i) {
            size_t wordLength, numDefinitions;
            inFile.read(reinterpret_cast<char*>(&wordLength), sizeof(wordLength));
            std::string word(wordLength, '\0');
            inFile.read(&word[0], wordLength);

            inFile.read(reinterpret_cast<char*>(&numDefinitions), sizeof(numDefinitions));
            std::vector<std::string> definitions(numDefinitions);
            for (size_t j = 0; j < numDefinitions; ++j) {
                size_t definitionLength;
                inFile.read(reinterpret_cast<char*>(&definitionLength), sizeof(definitionLength));
                std::string definition(definitionLength, '\0');
                inFile.read(&definition[0], definitionLength);
                definitions[j] = definition;
            }

            history.emplace_back(word, definitions);
        }

        inFile.close();
    }
    else {
        std::cerr << "Failed to open " << filename << std::endl;
    }
}


void HistoryManager::viewHistory(wxGrid* historyGrid) const {
    historyGrid->ClearGrid();  // Clear existing grid data

    // Ensure grid has the correct number of rows
    int numRows = static_cast<int>(history.size());
    if (historyGrid->GetNumberRows() != numRows) {
        historyGrid->DeleteRows(0, historyGrid->GetNumberRows(), true);
        historyGrid->AppendRows(numRows);
    }

    for (int row = 0; row < numRows; ++row) {
        const auto& pair = history[row];
        historyGrid->SetCellValue(row, 0, pair.first);
        std::string definitions;
        for (const auto& definition : pair.second) {
            definitions += definition + "; ";
        }
        if (!definitions.empty()) {
            definitions.pop_back();
        }
        historyGrid->SetCellValue(row, 1, definitions);
    }
}

const std::vector<std::pair<std::string, std::vector<std::string>>>& HistoryManager::getHistoryData() const {
    return history;
}