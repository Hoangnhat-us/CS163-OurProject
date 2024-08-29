#include "gameDia2.h"

gameDia2::gameDia2(wxWindow* parent) : wxPanel(parent, wxID_ANY)
{
	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

	wxFont font(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_MAX, wxFONTWEIGHT_SEMIBOLD, false, "Kadwa Bold");
	w = new wxStaticText(this, wxID_ANY, "Word", wxDefaultPosition, wxDefaultSize);
	w->SetFont(font);
	vbox->Add(w, 0, wxALIGN_CENTER);

	wxGridSizer* gSizer = new wxGridSizer(2, 2, 20, 20);
	wxColour buttonColor(0, 128, 0);

	wxString labels[4] = { "A.", "B.", "C.", "D." };
	for (int i = 0; i < 4; ++i) {
		buttons[i] = new wxButton(this, 10001 + i, labels[i], wxDefaultPosition, wxSize(200, 50));
		buttons[i]->SetFont(font);
		buttons[i]->SetBackgroundColour(buttonColor);
		buttons[i]->SetForegroundColour(*wxWHITE);
		gSizer->Add(buttons[i], 0, wxEXPAND | wxALL, 10);
	}

	vbox->Add(gSizer, 1, wxEXPAND | wxALL, 20);
	this->SetSizer(vbox);

	Bind(wxEVT_BUTTON, &gameDia2::OnButtonClicked, this, 10001);
	Bind(wxEVT_BUTTON, &gameDia2::OnButtonClicked, this, 10002);
	Bind(wxEVT_BUTTON, &gameDia2::OnButtonClicked, this, 10003);
	Bind(wxEVT_BUTTON, &gameDia2::OnButtonClicked, this, 10004);

	SetBackgroundColour(wxColour(240, 240, 240));
}

void gameDia2::OnButtonClicked(wxCommandEvent& event)
{
	int id = event.GetId();
	wxString msg;
	switch (id) {
	case 10001: msg = "Button A clicked!"; break;
	case 10002: msg = "Button B clicked!"; break;
	case 10003: msg = "Button C clicked!"; break;
	case 10004: msg = "Button D clicked!"; break;
	}
	wxMessageBox(msg, "Info", wxOK | wxICON_INFORMATION);
}
