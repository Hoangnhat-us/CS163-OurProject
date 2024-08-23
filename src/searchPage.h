#pragma once

#include "dicType.h"
#include "searchType.h"
#include "TernarySearchTree.h"
#include <vector>
#include <wx/wx.h>
#include "Search.h"
#include<wx/splitter.h>



class searchPage : public wxWindow {
public:

	wxBitmapButton* home;
	dicType* lists;
	searchType* choice;
	wxBitmapButton* searchButton;
	wxBitmapButton* origin;
	wxBitmapButton* add;

	wxTextCtrl* searchInput;
	wxBitmapButton* like;
	wxBitmapButton* del;
	wxBitmapButton* fix;

	wxStaticText* word;
	wxTextCtrl* editWord;
	SuggestionListBox* suggestionBox;

	wxSplitterWindow* splitter;

	std::vector<wxStaticText*> def;
	std::vector<wxTextCtrl*> editDef;
	std::vector<wxStaticBitmap*> line;

	searchPage(wxWindow* parent, int& dicTypeInt, int& searchType, std::string& Word, std::vector<TST>& dic);
	void OnButtonClicked(wxCommandEvent& event);
	void OnTextChange(wxCommandEvent& event);
	void OnSuggestionBoxToggle(wxCommandEvent& event);
	void OnSuggestionBoxSelect(wxCommandEvent& event);

private:
	std::vector<TST>  dic;
	std::string Word;
	void setTopControls(wxPanel* panel, int& dicTypeInt, int& searchTypeInt, std::string Word);
	void setControls(wxPanel* panel, int& dicTypeInt, int& searchTypeInt, std::string Word);
	void setRightControls(wxPanel* panel, int& dicTypeInt, int& searchTypeInt, std::string Word);
};


