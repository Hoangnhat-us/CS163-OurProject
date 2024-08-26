#pragma once
#include <wx/dialog.h>
#include <wx/wx.h>

class addDialog : public wxDialog
{
public:
	addDialog(wxWindow* parent, const wxString& title);

	wxBitmapButton* add;
	wxStaticText* word;
	wxStaticText* def;
	wxTextCtrl* wordInput;
	wxTextCtrl* defInput;
	wxStaticBitmap* pic;
};