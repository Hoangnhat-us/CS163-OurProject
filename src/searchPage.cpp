#include "dicType.h"
#include "searchPage.h"

searchPage::searchPage(wxWindow* parent, int& dicTypeInt, int& searchTypeInt, wxString& Word) : wxWindow(parent, wxID_ANY)
{
	this->SetBackgroundColour("#FFFFFF");
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	// Create panel and sizers
	// Top panel
	wxPanel* topPanel = new wxPanel(this, wxID_ANY);

	topPanel->SetBackgroundColour("#38435A");

	setTopControls(topPanel, dicTypeInt, searchTypeInt, Word);

	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* s1 = new wxBoxSizer(wxVERTICAL);
	s1->Add(home, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 20);
	topSizer->Add(s1, 0, wxTOP | wxBOTTOM | wxEXPAND, 20);

	wxBoxSizer* s2 = new wxBoxSizer(wxVERTICAL);
	s2->Add(choice, 0, wxALIGN_CENTER | wxLEFT, 30);
	topSizer->Add(s2, 0, wxTOP | wxBOTTOM | wxEXPAND, 20);

	wxBoxSizer* s3 = new wxBoxSizer(wxVERTICAL);
	s3->Add(searchInput, 0, wxEXPAND | wxLEFT, 10);
	topSizer->Add(s3, 1, wxTOP | wxBOTTOM | wxEXPAND, 20);

	wxBoxSizer* s4 = new wxBoxSizer(wxVERTICAL);
	s4->Add(searchButton, 0, wxALIGN_CENTER | wxLEFT, 10);
	topSizer->Add(s4, 0, wxTOP | wxBOTTOM | wxEXPAND, 20);

	wxBoxSizer* s5 = new wxBoxSizer(wxVERTICAL);
	s5->Add(lists, 0, wxALIGN_CENTER | wxLEFT, 100);
	topSizer->Add(s5, 0, wxTOP | wxBOTTOM | wxEXPAND, 20);

	wxBoxSizer* s6 = new wxBoxSizer(wxVERTICAL);
	s6->Add(origin, 0, wxALIGN_CENTER | wxLEFT, 30);
	topSizer->Add(s6, 0, wxTOP | wxBOTTOM | wxEXPAND, 20);

	wxBoxSizer* s7 = new wxBoxSizer(wxVERTICAL);
	s7->Add(add, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 30);
	topSizer->Add(s7, 0, wxTOP | wxBOTTOM | wxEXPAND, 20);


	topPanel->SetSizer(topSizer);

	mainSizer->Add(topPanel, 0, wxEXPAND);


	//Main panel
	wxPanel* mainPanel = new wxPanel(this, wxID_ANY);


	wxBoxSizer* Sizer1 = new wxBoxSizer(wxHORIZONTAL);

	wxPanel* leftPanel = new wxPanel(mainPanel, wxID_ANY);

	leftPanel->SetBackgroundColour("#F8D65B");

	setControls(leftPanel, dicTypeInt, searchTypeInt, Word);

	wxBoxSizer* Sizer2 = new wxBoxSizer(wxVERTICAL);

	Sizer2->AddSpacer(40);

	wxBoxSizer* ss1 = new wxBoxSizer(wxVERTICAL);
	ss1->Add(like, 0, wxALIGN_CENTER | wxALL, 20);
	Sizer2->Add(ss1, 1, wxEXPAND);

	wxBoxSizer* ss2 = new wxBoxSizer(wxVERTICAL);
	ss2->Add(del, 0, wxALIGN_CENTER | wxALL, 20);
	Sizer2->Add(ss2, 1, wxEXPAND);

	wxBoxSizer* ss3 = new wxBoxSizer(wxVERTICAL);
	ss3->Add(fix, 0, wxALIGN_CENTER | wxALL, 20);
	Sizer2->Add(ss3, 1, wxEXPAND);

	leftPanel->SetSizer(Sizer2);

	Sizer1->Add(leftPanel, 0, wxEXPAND);

	wxPanel* rightPanel = new wxPanel(mainPanel, wxID_ANY);

	setRightControls(rightPanel, dicTypeInt, searchTypeInt, Word);

	wxBoxSizer* Sizer3 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* wordSizer = new wxBoxSizer(wxHORIZONTAL);
	wordSizer->Add(word, 0, wxLEFT, 20);
	Sizer3->Add(wordSizer, 1, wxALL, 20);

	wxBoxSizer* lineSizer = new wxBoxSizer(wxHORIZONTAL);
	lineSizer->Add(line[0], 0, wxLEFT, 20);
	Sizer3->Add(lineSizer, 1, wxALL, 20);

	std::vector<wxBoxSizer*> linesSizer;
	std::vector<wxBoxSizer*> wordsSizer;

	for (int i = 0; i < def.size(); i++)
	{
		wxBoxSizer* wordsSizer = new wxBoxSizer(wxHORIZONTAL);
		wordsSizer->Add(def[i], 0, wxLEFT, 20);
		Sizer3->Add(wordsSizer, 1, wxALL, 20);

		linesSizer.push_back(new wxBoxSizer(wxHORIZONTAL));
		linesSizer[i]->Add(line[i + 1], 0, wxLEFT, 20);
		Sizer3->Add(linesSizer[i], 1, wxALL, 20);
	}

	rightPanel->SetSizer(Sizer3);

	Sizer1->Add(rightPanel, 1, wxEXPAND);

	mainPanel->SetSizer(Sizer1);

	mainSizer->Add(mainPanel, 1, wxEXPAND);

	this->SetSizer(mainSizer);
}

void searchPage::setTopControls(wxPanel* panel, int& dicTypeInt, int& searchTypeInt, wxString Word)
{
	wxBitmap bmHome(wxT("D:/CS163/picture/home.png"), wxBITMAP_TYPE_PNG);
	home = new wxBitmapButton(panel, wxID_ANY, bmHome, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	home->SetBackgroundColour("#38435A");

	wxFont font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_MAX, wxFONTWEIGHT_SEMIBOLD, false, "Varela Round");

	choice = new searchType(panel, searchTypeInt);
	choice->SetSize(wxSize(49, 29));
	choice->SetFont(font);

	lists = new dicType(panel, dicTypeInt);
	lists->SetSize(wxSize(127, 33));
	lists->SetFont(font);

	wxBitmap bmSearchButton(wxT("D:/CS163/picture/searchButton.png"), wxBITMAP_TYPE_PNG);
	searchButton = new wxBitmapButton(panel, wxID_ANY, bmSearchButton, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	searchButton->SetBackgroundColour("#38435A");


	searchInput = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(450, 33));
	searchInput->SetFont(font);
	searchInput->SetHint("Enter search text...");  // Placeholder text

    

	wxBitmap bmOrigin(wxT("D:/CS163/picture/Origin-Copy.png"), wxBITMAP_TYPE_PNG);
	origin = new wxBitmapButton(panel, wxID_ANY, bmOrigin, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	origin->SetBackgroundColour("#38435A");

	wxBitmap bmAddButton(wxT("D:/CS163/picture/addButton-Copy.png"), wxBITMAP_TYPE_PNG);
	add = new wxBitmapButton(panel, wxID_ANY, bmAddButton, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	add->SetBackgroundColour("#38435A");

}

void searchPage::setControls(wxPanel* panel, int& dicTypeInt, int& searchTypeInt, wxString Word)
{
	wxFont font(14, wxFONTFAMILY_DEFAULT, wxBOLD, wxFONTWEIGHT_NORMAL, false, "Varela Round");

	wxBitmap bmLike(wxT("D:/CS163/picture/heart.png"), wxBITMAP_TYPE_PNG);
	like = new wxBitmapButton(panel, wxID_ANY, bmLike, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	like->SetBackgroundColour("#F8D65B");

	wxBitmap bmDel(wxT("D:/CS163/picture/bin.png"), wxBITMAP_TYPE_PNG);
	del = new wxBitmapButton(panel, wxID_ANY, bmDel, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	del->SetBackgroundColour("#F8D65B");

	wxBitmap bmFix(wxT("D:/CS163/picture/publishing.png"), wxBITMAP_TYPE_PNG);
	fix = new wxBitmapButton(panel, wxID_ANY, bmFix, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	fix->SetBackgroundColour("#F8D65B");
}

void searchPage::setRightControls(wxPanel* panel, int& dicTypeInt, int& searchTypeInt, wxString Word)
{
	wxFont Wordfont(35, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_MAX, wxFONTWEIGHT_SEMIBOLD, false, "Varela Round");
	wxFont font(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_MAX, wxFONTWEIGHT_SEMIBOLD, false, "Varela Round");

	word = new wxStaticText(panel, wxID_ANY, Word, wxDefaultPosition, wxDefaultSize);
	word->SetFont(Wordfont);
	word->SetBackgroundColour("F8D65B");

	editWord = new wxTextCtrl(panel, wxID_ANY, word->GetLabel(), wxDefaultPosition, wxDefaultSize);
	editWord->Hide();
	editWord->SetFont(Wordfont);

	//Set definition?

	def.resize(5);
	editDef.resize(5);

	for (int i = 0; i < def.size(); i++)
	{
		def[i] = new wxStaticText(panel, wxID_ANY, Word, wxDefaultPosition, wxSize(300, 30));
		editDef[i] = new wxTextCtrl(this, wxID_ANY, word->GetLabel(), wxDefaultPosition, wxSize(300, 30));
		editDef[i]->Hide();
		def[i]->SetFont(font);
		editDef[i]->SetFont(font);
	}

	line.resize(def.size() + 1);
	wxBitmap bmLine(wxT("D:/CS163/picture/Line.png"), wxBITMAP_TYPE_PNG);
	for (int i = 0; i < def.size() + 1; i++)
	{
		line[i] = new wxStaticBitmap(panel, wxID_ANY, bmLine, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	}
}

