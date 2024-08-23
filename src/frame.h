#pragma once
#include "TernarySearchTree.h"
#include<vector>
#include <wx/simplebook.h>
#include <wx/wx.h>

class frame : public wxFrame {
public:
	frame();
private:
	wxSimplebook* book;
	std::vector<TST> dic;
	void switchToSearch(wxCommandEvent& event);
};
