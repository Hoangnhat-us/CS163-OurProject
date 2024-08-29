#pragma once

#include"addDialog.h"
#include "dicType.h"
#include "Favorite.h"
#include "History.h"
#include"Random.h"
#include "Search.h"
#include "searchType.h"
#include "SuffixArray.h"
#include "TernarySearchTree.h"
#include <vector>
#include <wx/splitter.h>
#include <wx/wx.h>

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

	wxBitmapButton* random;

	wxStaticText* word;
	wxTextCtrl* editWord;
	SuggestionListBox* suggestionBox;
	wxPanel* mainPanel;

	wxSplitterWindow* splitter;


	std::vector<wxStaticText*> def;
	std::vector<wxTextCtrl*> editDef;
	std::vector<wxStaticBitmap*> line;
	std::vector<TST>  dic;
	std::vector<SuffixArray> SA;

	searchPage(wxWindow* parent, int& dicTypeInt, int& searchType, std::string& sWord, std::vector<TST>& dic, std::vector<SuffixArray>& SA);
	void OnTextChange(wxCommandEvent& event);
	void OnSuggestionBoxToggle(wxCommandEvent& event);
	void OnSuggestionBoxSelect(wxCommandEvent& event);
	void UpdateRightPanel();
	void OnSearchButtonClicked(wxCommandEvent& event);
	void OnDicTypeChanged(wxCommandEvent& event);
	void OnSearchTypeChanged(wxCommandEvent& event);
	void OnDelButtonClicked(wxCommandEvent& event);
	void OnFixButtonClicked(wxCommandEvent& event);
	void OnOriginButtonClicked(wxCommandEvent& event);
	void OnAddButtonClicked(wxCommandEvent& event);
	void OnLikeButtonClicked(wxCommandEvent& event);
	void OnRandomButtonClicked(wxCommandEvent& event);

	void HandleHistoryOperations(const std::string& word, const std::vector<std::string>& definitions, int dicTypeInt);
	void HandleFavoriteOperations(const std::string& word, const std::vector<std::string>& definitions, int dicTypeInt);
private:
	int dicTypeInt;
	int searchTypeInt;

	std::string Word;
	void setTopControls(wxPanel* panel, int& dicTypeInt, int& searchTypeInt, std::string Word);
	void setControls(wxPanel* panel, int& dicTypeInt, int& searchTypeInt, std::string Word);
	void setRightControls(wxPanel* panel, int& dicTypeInt, int& searchTypeInt, std::string Word);

	HistoryManager historyManager;
	FavoriteManager favoriteManager;
};


