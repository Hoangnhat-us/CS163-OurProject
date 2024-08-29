#include "gamePage.h"

gamePage::gamePage(wxWindow* parent, int& dicTypeInt, int& searchType, std::string& sWord, std::vector<TST>& dic, std::vector<SuffixArray>& SA) : wxWindow(parent, wxID_ANY)
{
	wxBitmap bm1(wxT("../../../../picture/gameBanner.png"), wxBITMAP_TYPE_PNG);
	wxBitmap bm2(wxT("../../../../picture/dicTypeChoice.png"), wxBITMAP_TYPE_PNG);
	wxBitmap bm3(wxT("../../../../picture/levelChoice.png"), wxBITMAP_TYPE_PNG);
	wxBitmap bm4(wxT("../../../../picture/startChoice.png"), wxBITMAP_TYPE_PNG);
	wxBitmap bm5(wxT("../../../../picture/home.png"), wxBITMAP_TYPE_PNG);

	this->SetBackgroundColour("#B5D395");

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	wxPanel* top = new wxPanel(this, wxID_ANY);
	top->SetBackgroundColour("#38435A");
	wxPanel* banners = new wxPanel(top, wxID_ANY);
	banners->SetBackgroundColour("#38435A");
	wxBoxSizer* ban = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* a = new wxBoxSizer(wxVERTICAL);
	wxBitmap favoriteBanner(wxT("../../../../picture/addBanner.png"), wxBITMAP_TYPE_PNG);
	wxStaticBitmap* banner = new wxStaticBitmap(banners, wxID_ANY, favoriteBanner);
	a->Add(banner, 1, wxALIGN_CENTER);

	banners->SetSizer(a);

	home = new wxBitmapButton(top, wxID_ANY, bm5, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	home->SetBackgroundColour("#38435A");

	ban->Add(home);

	ban->Add(banners, 1, wxALIGN_CENTER);

	top->SetSizer(ban);

	mainSizer->Add(top, 0, wxEXPAND | wxBOTTOM, 20);


	//
	wxPanel* Panel1 = new wxPanel(this, wxID_ANY);

	gameBanner = new wxStaticBitmap(Panel1, wxID_ANY, bm1);

	wxBoxSizer* wordSizer = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* s1 = new wxBoxSizer(wxVERTICAL);
	s1->Add(gameBanner, 1, wxALIGN_CENTER);
	wordSizer->Add(s1, 1, wxEXPAND);

	Panel1->SetSizer(wordSizer);

	mainSizer->Add(Panel1, 1, wxALL | wxEXPAND, 20);

	//

	wxPanel* Panel2 = new wxPanel(this, wxID_ANY);

	list = new dicType(Panel2, dicTypeInt);
	list->SetSize(127, 33);
	dicTypeChoice = new wxStaticBitmap(Panel2, wxID_ANY, bm2);


	wxBoxSizer* Sizer2 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* s3 = new wxBoxSizer(wxVERTICAL);
	s3->Add(dicTypeChoice, 1, wxALIGN_LEFT);
	Sizer2->Add(s3, 1, wxEXPAND);


	wxBoxSizer* s4 = new wxBoxSizer(wxVERTICAL);
	s4->Add(list, 1, wxALIGN_RIGHT);
	Sizer2->Add(s4, 1, wxEXPAND);

	Panel2->SetSizer(Sizer2);

	mainSizer->Add(Panel2, 1, wxALL | wxEXPAND, 20);

	//

	wxPanel* Panel3 = new wxPanel(this, wxID_ANY);

	wxString choices[] = { "Easy", "Medium", "Hard" };
	// Tải hình ảnh từ file
	level = new wxComboBox(Panel3, wxID_ANY, "Select an option",
		wxDefaultPosition, wxDefaultSize,
		WXSIZEOF(choices), choices);
	wxFont font(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_MAX, wxFONTWEIGHT_SEMIBOLD, false, "Kadwa Bold");
	level->SetFont(font);
	level->SetSelection(0);

	levelChoice = new wxStaticBitmap(Panel3, wxID_ANY, bm3);

	wxBoxSizer* Sizer3 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* s5 = new wxBoxSizer(wxVERTICAL);
	s5->Add(levelChoice, 1, wxALIGN_LEFT);
	Sizer3->Add(s5, 1, wxEXPAND);

	wxBoxSizer* s6 = new wxBoxSizer(wxVERTICAL);
	s6->Add(level, 1, wxALIGN_RIGHT);
	Sizer3->Add(s6);

	Panel3->SetSizer(Sizer3);

	mainSizer->Add(Panel3, 1, wxALL | wxEXPAND, 20);

	wxPanel* Panel4 = new wxPanel(this, wxID_ANY);

	startButton = new wxBitmapButton(Panel4, wxID_ANY, bm4, wxDefaultPosition, wxDefaultSize);

	wxBoxSizer* Sizer4 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* s7 = new wxBoxSizer(wxVERTICAL);
	s7->Add(startButton, 1, wxALIGN_RIGHT);
	Sizer4->Add(s7);

	Panel4->SetSizer(Sizer4);

	mainSizer->Add(Panel4, 1, wxALL | wxEXPAND, 20);

	this->SetSizer(mainSizer);

	startButton->Bind(wxEVT_BUTTON, &gamePage::OnStart, this);
}

void gamePage::OnStart(wxCommandEvent& event)
{
	game = new gameDialog(this, "Word Game");
	game->ShowModal();

}
