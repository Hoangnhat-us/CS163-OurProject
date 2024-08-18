#pragma once

#include <wx/wx.h>
#include <wx/grid.h>
#include "dicType.h"

class favoritePage : public wxWindow {
public:
    favoritePage(wxWindow* parent, int& dicTypeInt);

private:
    void setTopControls(wxPanel* panel, int& dicTypeInt);
    wxPanel* wordsFavoriteTable(wxWindow* parent);
    void OnGamesButtonClicked(wxCommandEvent& event);

    // UI components
    wxBitmapButton* home;
    wxTextCtrl* searchInput;
    dicType* lists;
    wxBitmapButton* origin;
    wxBitmapButton* add;
    wxButton* games;
};
