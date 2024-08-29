#include "gameDialog.h"

gameDialog::gameDialog(wxWindow* parent, const wxString& title) : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(720, 460))
{
	book = new wxSimplebook(this, wxID_ANY);

	dia1 = new gameDia1(book);
	dia2 = new gameDia2(book);
	book->AddPage(dia1, "Game 1");
	book->AddPage(dia2, "Game 2");

	book->SetSelection(1);

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(book, 1, wxEXPAND);
	this->SetSizer(sizer);
}
