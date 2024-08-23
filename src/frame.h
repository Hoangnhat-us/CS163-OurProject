#pragma once
#include "TernarySearchTree.h"
#include<vector>
#include <wx/simplebook.h>
#include <wx/wx.h>

class frame : public wxFrame {
public:
	frame();
	void OnButtonClicked(wxCommandEvent& event);
	void OnExit(wxCloseEvent& event);
private:
	wxSimplebook* book;
	std::vector<TST> dic;
	void switchToSearch(wxCommandEvent& event);
	void switchToHome(wxCommandEvent& event);
};
