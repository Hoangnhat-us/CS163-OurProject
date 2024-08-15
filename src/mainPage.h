#pragma once

#include"dicType.h"
#include <wx/wx.h>
#include"Search.h"
#include<vector>
#include"TernarySearchTree.h"

class mainPage : public wxWindow {
public:

	wxBitmapButton* origin;
	wxBitmapButton* addButton;
	wxBitmapButton* history;
	wxBitmapButton* Random;
	wxBitmapButton* FavWords;
	wxBitmapButton* WordGames;

	wxTextCtrl* searchInput;
	wxBitmapButton* name;
	SuggestionListBox* suggestionBox;

	wxButton* searchButton;

	dicType* list;


	mainPage(wxWindow* parent, int& dicTypeInt, int& searchType, wxString& searchWord,std::vector<TST>& dic);
	void OnButtonClicked(wxCommandEvent& event);

	
private:
	std::vector<TST>  dic;
	void setControls(int& dicTypeIt, int& searchTypeIt);
	void OnTextChange(wxCommandEvent& event);

};


