#pragma once

#include "dicType.h"
#include <wx/grid.h>
#include <wx/wx.h>

class favoritePage : public wxWindow {
public:
	favoritePage(wxWindow* parent, int& dicTypeInt);
	wxBitmapButton* home;
	wxTextCtrl* searchInput;
	dicType* lists;
	wxBitmapButton* origin;
	wxBitmapButton* add;
	wxButton* games;

private:
	void setTopControls(wxPanel* panel, int& dicTypeInt);
	wxPanel* wordsFavoriteTable(wxWindow* parent);
	void OnGamesButtonClicked(wxCommandEvent& event);
	void setMain(wxScrolledWindow* main);
	// UI components


};
