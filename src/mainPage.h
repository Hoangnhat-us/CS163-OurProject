#pragma once

#include"dicType.h"
#include"Search.h"
#include"TernarySearchTree.h"
#include<vector>
#include <wx/wx.h>

class mainPage : public wxWindow {
public:

	wxBitmapButton* origin;
	wxBitmapButton* addButton;
	wxBitmapButton* history;
	wxBitmapButton* Random;
	wxBitmapButton* FavWords;
	wxBitmapButton* WordGames;

	wxBitmapButton* name;
	SuggestionListBox* suggestionBox;

	wxButton* searchButton;

	dicType* list;


	mainPage(wxWindow* parent, int& dicTypeInt, int& searchType, std::string& searchWord, std::vector<TST>& dic);
	void OnButtonClicked(wxCommandEvent& event);


private:
	std::vector<TST>  dic;
	void setControls(int& dicTypeIt, int& searchTypeIt);
	void OnTextChange(wxCommandEvent& event);

};


