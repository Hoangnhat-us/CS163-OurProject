#pragma once
#include "gameDia1.h"
#include "gameDia2.h"
#include <wx/dialog.h>
#include <wx/simplebook.h>
#include <wx/wx.h>

class gameDialog : public wxDialog
{
public:
	gameDialog(wxWindow* parent, const wxString& title);

	wxSimplebook* book;
	gameDia1* dia1;
	gameDia2* dia2;
};
