#pragma once

#include "dicType.h"
#include <wx/grid.h>
#include <wx/wx.h>
#include "History.h"

class historyPage : public wxWindow {
public:
    historyPage(wxWindow* parent, int& dicTypeInt);
    wxBitmapButton* home;
    wxTextCtrl* searchInput;
    dicType* lists;
    wxBitmapButton* origin;
    wxBitmapButton* add;
    wxButton* games;

    void OnDicTypeChanged(wxCommandEvent& event);

private:
    wxGrid* historyGrid;
    int dicTypeInt;

    void setTopControls(wxPanel* panel, int& dicTypeInt);
    wxPanel* wordsHistoryTable(wxWindow* parent);
    void OnGamesButtonClicked(wxCommandEvent& event);
    void setMain(wxScrolledWindow* main);
    void refreshHistoryGrid();
    void OnShow(wxShowEvent& event);

    HistoryManager historyManager;  // HistoryManager instance
};
