#pragma once
#include "favoritePage.h"
#include "gamePage.h"
#include "historyPage.h"
#include "mainPage.h"
#include "Random.h"
#include "searchPage.h"
#include "SuffixArray.h"
#include "TernarySearchTree.h"
#include<vector>
#include <wx/simplebook.h>
#include <wx/wx.h>

class frame : public wxFrame {
public:
	frame();
	void OnButtonClicked(wxCommandEvent& event);
	void OnExit(wxCloseEvent& event);

	mainPage* home;
	searchPage* search;
	favoritePage* favorite;
	historyPage* his;
	gamePage* game;


	int dicTypeInt = 0;
	int searchTypeInt = 0;

	std::string searchWord;

private:
	wxSimplebook* book;
	std::vector<TST> dic;
	std::vector<SuffixArray> SA;

	void switchToSearch(wxCommandEvent& event);
	void switchToHome(wxCommandEvent& event);
	void switchToFav(wxCommandEvent& event);
	void switchToHis(wxCommandEvent& event);
	void switchToGame(wxCommandEvent& event);
	void LoadDic();
};
