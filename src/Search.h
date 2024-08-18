#pragma once

#include "dicType.h"
#include "TernarySearchTree.h" 
#include <vector>
#include <wx/listbox.h>
#include <wx/wx.h>

class SuggestionListBox : public wxPanel
{
public:
	dicType* dicType;
	SuggestionListBox(wxWindow* parent, std::vector<TST>& tst, int& dicTypeInt, int& searchType, wxSize size);

	void UpdateSuggestions(const wxString& prefix);

	wxTextCtrl* searchInput;
	wxListBox* suggest;

private:
	TST tst;
	bool isHaveunicode(const std::string& str);
};



