#pragma once

#include "dicType.h"
#include "TernarySearchTree.h" 
#include <vector>
#include <wx/listbox.h>
#include <wx/wx.h>
#include <wx/textctrl.h>
#include "searchType.h"

class SuggestionListBox : public wxPanel
{
public:
	
	SuggestionListBox(wxWindow* parent, std::vector<TST>& tst, int& dicTypeInt, int& searchType, wxSize size);
	void UpdateSuggestListBox(std::vector<TST>& dic, int& dicTypeInt, int& searchType);
	void UpdateSuggestions(const wxString& prefix);
	void OnSuggestionSelected(wxCommandEvent& event);
	std::string getSearchInput();

	wxTextCtrl* searchInput;
	wxListBox* suggest;

private:
	TST tst;
	bool isHaveunicode(const std::string& str);
	int dicTypeInt;
	int searchType;
};



