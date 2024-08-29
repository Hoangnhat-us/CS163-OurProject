#pragma once
#include "timer.h"
#include <wx/wx.h>

class gameDia2 : public wxPanel
{
public:
	CountdownTimer* timer;
	wxStaticText* point;
	wxStaticText* w;
	wxButton* buttons[4];

	gameDia2(wxWindow* parent);
	void OnButtonClicked(wxCommandEvent& event);
};