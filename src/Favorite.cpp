#include "Favorite.h"

void FavoriteManager::addFavorite(const std::string& word, const std::vector<std::string>& definitions) {
    for (const auto& pair : favorites) {
        if (pair.first == word) {
            return;
        }
    }

    favorites.emplace_back(word, definitions);
}

void FavoriteManager::saveFavorites(const std::string& filename) const {
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
    }
}

void FavoriteManager::loadFavorites(const std::string& filename) {
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
                std::string definition(definitionLength, '\0');// Create a string `definition` of length `definitionLength`, init with null characters
                inFile.read(&definition[0], definitionLength);// `&definition[0]` provides a pointer to the first character in the string's internal buffer.
                definitions[j] = definition;// Store the fully read definition into the `definitions` vector at the index `j`.
            }

            favorites.emplace_back(word, definitions);
        }

        inFile.close();
    }
    else {
        std::cerr << "Could not open file " << filename << " for reading." << std::endl;
    }
}

void FavoriteManager::viewFavorites() const {
    if (favorites.empty()) {
        return;
    }

    for (const auto& pair : favorites) {
        for (const auto& definition : pair.second) {
        }
    }
}
