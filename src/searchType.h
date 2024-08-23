#pragma once
#include <wx/bmpcbox.h>
#include <wx/wx.h>

class searchType : public wxComboBox
{
public:
	searchType(wxWindow* panel, int& seacrhTypeInt);
	int getSearchType();
};

