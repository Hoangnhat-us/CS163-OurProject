#pragma once
#include <wx/wx.h>
#include "TernarySearchTree.h"
#include<vector>

class frame : public wxFrame {
public:
	frame();
private:
	std::vector<TST> dic;
	
};
