#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <wx/grid.h>

class FavoriteManager {
public:
    void addFavorite(const std::string& word, const std::vector<std::string>& definitions);
    void saveFavorite(const std::string& filename) const;
    void loadFavorite(const std::string& filename);
    const std::vector<std::pair<std::string, std::vector<std::string>>>& getFavoriteData() const;

private:
    std::vector<std::pair<std::string, std::vector<std::string>>> favorites;
};
