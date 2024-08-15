#pragma once

#include <wx/wx.h>
#include <wx/listbox.h>
#include <vector>
#include "TernarySearchTree.h" 
#include "dicType.h"

class SuggestionListBox : public wxListBox {
public:
	dicType* dicType;
    SuggestionListBox(wxWindow* parent, std::vector<TST>& tst, int& dicTypeInt, int& searchType);

    void UpdateSuggestions(const wxString& prefix);

private:
    TST tst;
};



