#pragma once
#include "dicType.h";
#include "gameDialog.h"
#include "SuffixArray.h"
#include "TernarySearchTree.h"
#include <wx/wx.h>

class gamePage : public wxWindow
{
public:
	wxStaticBitmap* gameBanner;
	wxStaticBitmap* dicTypeChoice;
	wxStaticBitmap* levelChoice;
	wxBitmapButton* startButton;
	wxBitmapButton* home;
	dicType* list;
	wxComboBox* level;
	gameDialog* game;

	gamePage(wxWindow* parent, int& dicTypeInt, int& searchType, std::string& sWord, std::vector<TST>& dic, std::vector<SuffixArray>& SA);
	void OnStart(wxCommandEvent& event);
};