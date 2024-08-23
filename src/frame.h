#pragma once
#include <wx/wx.h>
#include "TernarySearchTree.h"
#include<vector>

class frame : public wxFrame {
public:
	frame();
	void OnButtonClicked(wxCommandEvent& event);
	void OnExit(wxCloseEvent& event);
private:
	std::vector<TST> dic;
};
