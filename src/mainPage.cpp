#include "addDialog.h"
#include "dicType.h"
#include "mainPage.h"

mainPage::mainPage(wxWindow* parent, int& dicTypeIt, int& searchTypeIt, std::string& searchWord, std::vector<TST>& dic, std::vector<SuffixArray>& SA) : wxWindow(parent, wxID_ANY)
{
	this->dic = dic;
	this->SA = SA;

	this->SetBackgroundColour(wxColor("#38435A"));

	wxPanel* main = new wxPanel(this, wxID_ANY);

	setControls(dicTypeIt, searchTypeIt, main);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	mainSizer->Add(banner, 0, wxALIGN_CENTER);
	mainSizer->Add(name, 0, wxALIGN_CENTER);


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

	main->SetSizer(mainSizer);

	wxBoxSizer* all = new wxBoxSizer(wxVERTICAL);

	all->Add(main, 0, wxALIGN_CENTER | wxTOP, 30);

	this->SetSizer(all);


}


void mainPage::setControls(int& dicTypeIt, int& searchTypeIt, wxPanel* panel)
{
	// Create the search input field
		// Create the search button


	// Tạo wxBitmap từ file ảnh
	wxBitmap bmHistory(wxT("../../../../picture/search history.png"), wxBITMAP_TYPE_PNG);
	wxBitmap bmRandom(wxT("../../../../picture/random word.png"), wxBITMAP_TYPE_PNG);
	wxBitmap bmFavWords(wxT("../../../../picture/favorite words.png"), wxBITMAP_TYPE_PNG);
	wxBitmap bmWordGames(wxT("../../../../picture/word games.png"), wxBITMAP_TYPE_PNG);
	wxBitmap bmBanner(wxT("../../../../picture/TPHANG Banner.png"), wxBITMAP_TYPE_PNG);

	banner = new wxStaticBitmap(panel, wxID_ANY, bmBanner);


	// Tạo wxBitmapButton
	history = new wxBitmapButton(panel, wxID_ANY, bmHistory, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	Random = new wxBitmapButton(panel, wxID_ANY, bmRandom, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	FavWords = new wxBitmapButton(panel, wxID_ANY, bmFavWords, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	WordGames = new wxBitmapButton(panel, wxID_ANY, bmWordGames, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);

	history->SetBackgroundColour("#38435A");
	Random->SetBackgroundColour("#38435A");
	FavWords->SetBackgroundColour("#38435A");
	WordGames->SetBackgroundColour("#38435A");

	wxBitmap tPDic(wxT("../../../../picture/TPHANG DICTIONARY.png"), wxBITMAP_TYPE_PNG);
	name = new wxBitmapButton(panel, wxID_ANY, tPDic, wxDefaultPosition, wxSize(884, 147), wxNO_BORDER);
	name->SetBackgroundColour("#38435A");


}


