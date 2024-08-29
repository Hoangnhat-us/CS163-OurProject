#pragma once

#include "dicType.h"
#include <wx/grid.h>
#include <wx/wx.h>
#include "Favorite.h"  // Ensure this include is correct

class favoritePage : public wxWindow {
public:
    favoritePage(wxWindow* parent, int& dicTypeInt);
    wxBitmapButton* home;
    dicType* lists;

private:
    wxBoxSizer* mainSizer;
    wxGrid* favoriteGrid;
    int dicTypeInt;

    void setTopControls(wxPanel* panel, int& dicTypeInt);
    wxPanel* wordsfavoriteTable(wxWindow* parent);
    void setMain(wxScrolledWindow* main);
    void refreshFavoriteGrid();
    void OnShow(wxShowEvent& event);
    void OnDicTypeChanged(wxCommandEvent& event);

    FavoriteManager favoriteManager;
};
