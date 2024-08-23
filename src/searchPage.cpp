#include "dicType.h"
#include "searchPage.h"
#include<wx/splitter.h>

searchPage::searchPage(wxWindow* parent, int& dicTypeInt, int& searchTypeInt, std::string& sWord, std::vector<TST>& dic)
	: wxWindow(parent, wxID_ANY)
{
	this->dic = dic;
	this->SetBackgroundColour("#FFFFFF");
	this->Word = sWord;

	this->dicTypeInt = dicTypeInt;
	this->searchTypeInt = searchTypeInt;

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	// Create a wxSplitterWindow
	splitter = new wxSplitterWindow(this, wxID_ANY);
	splitter->SetSashGravity(0.1);  // Adjust the ratio of the top panel size relative to the bottom

	// Create top panel
	wxPanel* topPanel = new wxPanel(splitter, wxID_ANY);
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
	//s3->Add(searchInput, 0, wxEXPAND | wxLEFT, 10);
	//s1->AddSpacer(10);
	s3->Add(suggestionBox, 0, wxEXPAND | wxLEFT, 10);
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

	wxBoxSizer* s7 = new wxBoxSizer(wxHORIZONTAL);
	s7->Add(add, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 30);
	topSizer->Add(s7, 0, wxTOP | wxBOTTOM | wxEXPAND, 20);

	topPanel->SetSizer(topSizer);

	// Create bottom panel (mainPanel)
	mainPanel = new wxPanel(splitter, wxID_ANY);

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

	// Split the top and bottom panels
	splitter->SplitHorizontally(topPanel, mainPanel);
	splitter->SetSashPosition(100);  // Adjust the initial sash position


	// Add the splitter window to the main sizer
	mainSizer->Add(splitter, 1, wxEXPAND);


	this->SetSizer(mainSizer);
}

void searchPage::setTopControls(wxPanel* panel, int& dicTypeInt, int& searchTypeInt, std::string sWord)
{
	wxBitmap bmHome(wxT("../../../../picture/home.png"), wxBITMAP_TYPE_PNG);
	home = new wxBitmapButton(panel, wxID_ANY, bmHome, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	home->SetBackgroundColour("#38435A");

	wxFont font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_MAX, wxFONTWEIGHT_SEMIBOLD, false, "Varela Round");

	choice = new searchType(panel, searchTypeInt);
	choice->SetSize(wxSize(49, 29));
	choice->SetFont(font);
	choice->Bind(wxEVT_COMBOBOX, &searchPage::OnSearchTypeChanged, this);

	lists = new dicType(panel, dicTypeInt);
	lists->SetSize(wxSize(127, 33));
	lists->SetFont(font);

	lists->Bind(wxEVT_COMBOBOX, &searchPage::OnDicTypeChanged, this);


	wxBitmap bmSearchButton(wxT("../../../../picture/searchButton.png"), wxBITMAP_TYPE_PNG);
	searchButton = new wxBitmapButton(panel, wxID_ANY, bmSearchButton, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	searchButton->SetBackgroundColour("#38435A");
	Bind(wxEVT_BUTTON, &searchPage::OnSearchButtonClicked, this, searchButton->GetId());


	//searchInput = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(450, 33));
	//searchInput->SetFont(font);
	//searchInput->SetHint("Enter search text...");  // Placeholder text



	suggestionBox = new SuggestionListBox(panel, dic, dicTypeInt, searchTypeInt, wxSize(450, 33));
	Bind(wxEVT_TEXT, &searchPage::OnTextChange, this, suggestionBox->searchInput->GetId());
	Bind(wxEVT_BUTTON, &searchPage::OnSuggestionBoxToggle, this, suggestionBox->searchInput->GetId());
	Bind(wxEVT_LISTBOX, &searchPage::OnSuggestionBoxSelect, this, suggestionBox->suggest->GetId());



	wxBitmap bmOrigin(wxT("../../../../picture/Origin-Copy.png"), wxBITMAP_TYPE_PNG);
	origin = new wxBitmapButton(panel, wxID_ANY, bmOrigin, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	origin->SetBackgroundColour("#38435A");

	wxBitmap bmAddButton(wxT("../../../../picture/addButton-Copy.png"), wxBITMAP_TYPE_PNG);
	add = new wxBitmapButton(panel, wxID_ANY, bmAddButton, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	add->SetBackgroundColour("#38435A");

}


void searchPage::setControls(wxPanel* panel, int& dicTypeInt, int& searchTypeInt, std::string Word)
{
	wxFont font(14, wxFONTFAMILY_DEFAULT, wxBOLD, wxFONTWEIGHT_NORMAL, false, "Varela Round");

	wxBitmap bmLike(wxT("../../../../picture/heart.png"), wxBITMAP_TYPE_PNG);
	like = new wxBitmapButton(panel, wxID_ANY, bmLike, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	like->SetBackgroundColour("#F8D65B");

	wxBitmap bmDel(wxT("../../../../picture/bin.png"), wxBITMAP_TYPE_PNG);
	del = new wxBitmapButton(panel, wxID_ANY, bmDel, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	del->SetBackgroundColour("#F8D65B");

	wxBitmap bmFix(wxT("../../../../picture/publishing.png"), wxBITMAP_TYPE_PNG);
	fix = new wxBitmapButton(panel, wxID_ANY, bmFix, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	fix->SetBackgroundColour("#F8D65B");
}

void searchPage::setRightControls(wxPanel* panel, int& dicTypeInt, int& searchTypeInt, std::string Word)
{
	wxFont Wordfont(35, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_MAX, wxFONTWEIGHT_SEMIBOLD, false, "Varela Round");
	wxFont font(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_MAX, wxFONTWEIGHT_SEMIBOLD, false, "Varela Round");

	word = new wxStaticText(panel, wxID_ANY, Word, wxDefaultPosition, wxDefaultSize);
	word->SetFont(Wordfont);
	word->SetBackgroundColour("F8D65B");

	editWord = new wxTextCtrl(panel, wxID_ANY, word->GetLabel(), wxDefaultPosition, wxDefaultSize);
	editWord->Hide();
	editWord->SetFont(Wordfont);

	std::vector<std::string> defs = dic[0].search(Word);



	def.resize(defs.size());
	editDef.resize(defs.size());

	for (int i = 0; i < def.size(); i++)
	{
		def[i] = new wxStaticText(panel, wxID_ANY, defs[i], wxDefaultPosition, wxSize(300, 30));
		editDef[i] = new wxTextCtrl(this, wxID_ANY, word->GetLabel(), wxDefaultPosition, wxSize(300, 30));
		editDef[i]->Hide();
		def[i]->SetFont(font);
		editDef[i]->SetFont(font);
	}

	line.resize(def.size() + 1);
	wxBitmap bmLine(wxT("../../../../picture/Line.png"), wxBITMAP_TYPE_PNG);
	for (int i = 0; i < def.size() + 1; i++)
	{
		line[i] = new wxStaticBitmap(panel, wxID_ANY, bmLine, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	}
	panel->Layout();
	panel->Refresh();
}

void searchPage::OnTextChange(wxCommandEvent& event) {
	wxString prefix = suggestionBox->searchInput->GetValue();
	suggestionBox->UpdateSuggestions(prefix);
	OnSuggestionBoxToggle(event);

}
void searchPage::OnSuggestionBoxToggle(wxCommandEvent& event)
{
	if (suggestionBox->suggest->IsShown()) {
		// Resize the splitter or adjust the layout
		splitter->SetSashPosition(250); // Adjust to the desired sash position
	}
	else {
		splitter->SetSashPosition(100);  // Adjust to the desired sash position when hidden
	}
	splitter->Layout(); // Refresh the layout after adjusting the sash
	event.Skip(); // Ensure the event is processed further
}

void searchPage::OnSuggestionBoxSelect(wxCommandEvent& event)
{
	suggestionBox->OnSuggestionSelected(event);
	suggestionBox->suggest->Hide();
	OnSuggestionBoxToggle(event);
}
void searchPage::UpdateRightPanel()
{
	std::string selectedWord = Word;
	//int dicTypeInt = lists->getDicType();
	//int searchTypeInt = choice->getSearchType();
	wxWindowList children = mainPanel->GetChildren();
	wxPanel* rightPanel = nullptr;

	// Assuming rightPanel is the second child in mainPanel
	if (children.size() > 1)
	{
		rightPanel = dynamic_cast<wxPanel*>(children.Item(1)->GetData());
	}

	// If rightPanel is successfully retrieved, update its controls
	if (rightPanel)
	{
		rightPanel->DestroyChildren();
		wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);
		rightPanel->SetSizer(rightSizer);

		// Set fonts
		wxFont Wordfont(35, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_MAX, wxFONTWEIGHT_SEMIBOLD, false, "Varela Round");
		wxFont font(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_MAX, wxFONTWEIGHT_SEMIBOLD, false, "Varela Round");

		// Update the word label and text box
		word = new wxStaticText(rightPanel, wxID_ANY, selectedWord, wxDefaultPosition, wxDefaultSize);
		word->SetFont(Wordfont);
		rightSizer->Add(word, 0, wxLEFT | wxTOP, 20);

		editWord = new wxTextCtrl(rightPanel, wxID_ANY, word->GetLabel(), wxDefaultPosition, wxDefaultSize);
		editWord->SetFont(Wordfont);
		editWord->Hide();
		rightSizer->Add(editWord, 0, wxLEFT | wxTOP, 20);

		// Retrieve definitions for the selected word
		std::vector<std::string> defs = dic[0].search(selectedWord);
		if (defs.empty()) {
			defs = dic[0].suggestCorrections(selectedWord, 2);
		}

		// Add the definitions to the right panel
		def.resize(defs.size());
		editDef.resize(defs.size());
		line.resize(def.size() + 1);
		wxBitmap bmLine(wxT("../../../../picture/Line.png"), wxBITMAP_TYPE_PNG);

		for (int i = 0; i < defs.size(); i++)
		{
			def[i] = new wxStaticText(rightPanel, wxID_ANY, defs[i], wxDefaultPosition, wxDefaultSize);
			def[i]->SetFont(font);
			rightSizer->Add(def[i], 0, wxALL, 10);


			editDef[i] = new wxTextCtrl(rightPanel, wxID_ANY, defs[i], wxDefaultPosition, wxDefaultSize);
			editDef[i]->SetFont(font);
			editDef[i]->Hide();
			rightSizer->Add(editDef[i], 0, wxALL, 10);

			line[i] = new wxStaticBitmap(rightPanel, wxID_ANY, bmLine, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
			rightSizer->Add(line[i], 0, wxLEFT, 20);
		}

		// Layout and refresh
		rightPanel->Layout();
		rightPanel->Refresh();
	}
}

void searchPage::OnSearchButtonClicked(wxCommandEvent& event)
{
	Word = suggestionBox->getSearchInput();
	suggestionBox->suggest->Hide();
	OnSuggestionBoxToggle(event);
	//int dicTypeInt = lists->getDicType();
	//int searchTypeInt = choice->getSearchType();

	UpdateRightPanel();
}

void searchPage::OnDicTypeChanged(wxCommandEvent& event)
{
	dicTypeInt = lists->getDicType();
}

void searchPage::OnSearchTypeChanged(wxCommandEvent& event)
{
	searchTypeInt = choice->getSearchType();
}