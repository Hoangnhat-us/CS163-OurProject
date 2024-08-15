#include "dicType.h"
#include "mainPage.h"

mainPage::mainPage(wxWindow* parent, int& dicTypeIt, int& searchTypeIt, wxString& searchWord) : wxWindow(parent, wxID_ANY)
{

	this->SetBackgroundColour(wxColor("#38435A"));

	setControls(dicTypeIt, searchTypeIt);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);

	topSizer->Add(addButton, 0, wxEXPAND | wxALL, 23);
	topSizer->Add(origin, 0, wxEXPAND | wxALL, 23);

	wxBoxSizer* temp = new wxBoxSizer(wxVERTICAL);
	temp->Add(list, 0, wxALIGN_RIGHT | wxALL, 23);

	topSizer->Add(temp, 1, wxALIGN_BOTTOM | wxALL, 23);

	mainSizer->Add(topSizer, 0, wxEXPAND);


	mainSizer->AddSpacer(35);
	mainSizer->Add(name, 0, wxALIGN_CENTER);

	// Create a horizontal sizer for the search bar
	wxBoxSizer* searchSizer = new wxBoxSizer(wxHORIZONTAL);


	// Add search input and button to the search sizer
	searchSizer->Add(searchInput, 1, wxALIGN_CENTER, 10);
	searchSizer->AddSpacer(10);
	searchSizer->Add(searchButton, 0, wxALIGN_CENTER, 10);

	mainSizer->Add(searchSizer, 0, wxALIGN_CENTER);

	mainSizer->AddSpacer(10);

	wxBoxSizer* botSizer = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* s1 = new wxBoxSizer(wxVERTICAL);
	s1->Add(history, 0, wxALIGN_CENTER, 20);
	botSizer->Add(s1, 1, wxEXPAND);

	wxBoxSizer* s2 = new wxBoxSizer(wxVERTICAL);
	s2->Add(Random, 0, wxALIGN_CENTER, 20);
	botSizer->Add(s2, 1, wxEXPAND);

	wxBoxSizer* s3 = new wxBoxSizer(wxVERTICAL);
	s3->Add(FavWords, 0, wxALIGN_CENTER, 20);
	botSizer->Add(s3, 1, wxEXPAND);

	wxBoxSizer* s4 = new wxBoxSizer(wxVERTICAL);
	s4->Add(WordGames, 0, wxALIGN_CENTER, 20);
	botSizer->Add(s4, 1, wxEXPAND);

	// Add the searchSizer to the mainSizer

	mainSizer->Add(botSizer, 1, wxEXPAND | wxTOP, 95);

	mainSizer->AddSpacer(20);

	this->SetSizerAndFit(mainSizer);




}

void mainPage::OnButtonClicked(wxCommandEvent& event)
{
	wxCommandEvent evt(wxEVT_COMMAND_BUTTON_CLICKED, wxID_ANY);
	evt.SetEventObject(this);
	wxPostEvent(GetParent(), evt);
}

void mainPage::setControls(int& dicTypeIt, int& searchTypeIt)
{
	// Create the search input field
		// Create the search button
	wxFont font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Varela Round");


	searchInput = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(633, 33));
	searchInput->SetFont(font);
	searchInput->SetHint("Enter search text...");  // Placeholder text

	searchButton = new wxButton(this, wxID_ANY, "Search", wxDefaultPosition, wxSize(50, 33), wxNO_BORDER);
	searchButton->SetFont(font);
	searchButton->SetBackgroundColour("#FF4F70");
	searchButton->SetForegroundColour(wxColour("#FFFFFF"));

	// Tạo wxBitmap từ file ảnh
	wxBitmap bmHistory(wxT("D:/CS163/picture/search history.png"), wxBITMAP_TYPE_PNG);
	wxBitmap bmRandom(wxT("D:/CS163/picture/random word.png"), wxBITMAP_TYPE_PNG);
	wxBitmap bmFavWords(wxT("D:/CS163/picture/favorite words.png"), wxBITMAP_TYPE_PNG);
	wxBitmap bmWordGames(wxT("D:/CS163/picture/word games.png"), wxBITMAP_TYPE_PNG);



	// Tạo wxBitmapButton
	history = new wxBitmapButton(this, wxID_ANY, bmHistory, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	Random = new wxBitmapButton(this, wxID_ANY, bmRandom, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	FavWords = new wxBitmapButton(this, wxID_ANY, bmFavWords, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	WordGames = new wxBitmapButton(this, wxID_ANY, bmWordGames, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);

	history->SetBackgroundColour("#38435A");
	Random->SetBackgroundColour("#38435A");
	FavWords->SetBackgroundColour("#38435A");
	WordGames->SetBackgroundColour("#38435A");


	list = new dicType(this, dicTypeIt);

	wxBitmap bmAddButton(wxT("D:/CS163/picture/addButton.png"), wxBITMAP_TYPE_PNG);
	wxBitmap bmOrigin(wxT("D:/CS163/picture/origin.png"), wxBITMAP_TYPE_PNG);

	addButton = new wxBitmapButton(this, wxID_ANY, bmAddButton, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	origin = new wxBitmapButton(this, wxID_ANY, bmOrigin, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);

	addButton->SetBackgroundColour("#38435A");
	origin->SetBackgroundColour("#38435A");

	wxBitmap tPDic(wxT("D:/CS163/picture/TPHANG DICTIONARY.png"), wxBITMAP_TYPE_PNG);
	name = new wxBitmapButton(this, wxID_ANY, tPDic, wxDefaultPosition, wxSize(884, 147), wxNO_BORDER);
	name->SetBackgroundColour("#38435A");
}
