#pragma once

#include <wx/wx.h>
#include "dicType.h"

class favoritePage : public wxWindow {
public:
    favoritePage(wxWindow* parent, int& dicTypeInt);

private:
    void setTopControls(wxPanel* panel, int& dicTypeInt);
    void OnGamesButtonClicked(wxCommandEvent& event); // Event handler for Games button

    // UI components
    wxBitmapButton* home;
    wxTextCtrl* searchInput;
    dicType* lists;
    wxBitmapButton* origin;
    wxBitmapButton* add;
    wxButton* games;
};
