#pragma once

#include"dicType.h"
#include"Search.h"
#include"TernarySearchTree.h"
#include<vector>
#include <wx/wx.h>

class mainPage : public wxWindow {
public:

	wxStaticBitmap* banner;

	wxBitmapButton* history;
	wxBitmapButton* Random;
	wxBitmapButton* FavWords;
	wxBitmapButton* WordGames;

	wxBitmapButton* name;

	mainPage(wxWindow* parent, int& dicTypeInt, int& searchType, std::string& searchWord, std::vector<TST>& dic, std::vector<SuffixArray>& SA);


private:
	std::vector<TST>  dic;
	std::vector<SuffixArray> SA;
	void setControls(int& dicTypeIt, int& searchTypeIt, wxPanel* panel);
};


