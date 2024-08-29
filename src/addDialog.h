#pragma once
#include <wx/dialog.h>
#include <wx/wx.h>

class addDialog : public wxDialog
{
public:
	addDialog(wxWindow* parent, const wxString& title);
	bool isAdded();
	std::string getWord();
	std::vector<std::string> getDef();
	void OnAddButtonClicked(wxCommandEvent& event);
	//void OnCancelButtonClicked(wxCommandEvent& event);
private:
	bool isAdd=false;
	wxBitmapButton* add;
	wxStaticText* word;
	wxStaticText* def;
	wxTextCtrl* wordInput;
	wxTextCtrl* defInput;
	wxStaticBitmap* pic;
};