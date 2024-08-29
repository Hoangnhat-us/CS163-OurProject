#include "Favorite.h"
#include <fstream>
#include <iostream>
#include <wx/wx.h>

void FavoriteManager::addFavorite(const std::string& word, const std::vector<std::string>& definitions) {
    for (const auto& pair : favorites) {
        if (pair.first == word) {
            wxMessageBox("Word already in Favorite List", "Favorite", wxOK | wxICON_INFORMATION);
            return;
        }
    }
    favorites.insert(favorites.begin(), { word, definitions });
    wxMessageBox("Add words to favorite successfully", "Favorite", wxOK | wxICON_INFORMATION);
}

void FavoriteManager::saveFavorite(const std::string& filename) const {
    std::ofstream outFile(filename, std::ios::binary);

    if (outFile.is_open()) {
        size_t size = favorites.size();
        outFile.write(reinterpret_cast<const char*>(&size), sizeof(size));

        for (const auto& pair : favorites) {
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
        std::cerr << "Failed to open file for saving: " << filename << std::endl;
    }
}

void FavoriteManager::loadFavorite(const std::string& filename) {
    favorites.clear();
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

            // Append each entry to the end of the vector to maintain the order
            favorites.emplace_back(word, definitions);
        }

        inFile.close();
    }
    else {
        std::cerr << "Failed to open file for loading: " << filename << std::endl;
    }
}

void FavoriteManager::removeFavorite(const std::string& word, const std::string& filename) {
    auto it = std::remove_if(favorites.begin(), favorites.end(), [&word](const auto& pair) { return pair.first == word; });
    if (it != favorites.end()) {
        favorites.erase(it, favorites.end());
        saveFavorite(filename);
    }
}

const std::vector<std::pair<std::string, std::vector<std::string>>>& FavoriteManager::getFavoriteData() const {
    return favorites;
}
