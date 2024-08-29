#include "dicType.h"
#include "Favorite.h"
#include "History.h"
#include "searchPage.h"
#include<wx/splitter.h>


searchPage::searchPage(wxWindow* parent, int& dicTypeInt, int& searchTypeInt, std::string& sWord, std::vector<TST>& dic, std::vector<SuffixArray>& SA)
	: wxWindow(parent, wxID_ANY)
{
	this->dic = dic;
	this->SA = SA;
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

	wxSplitterWindow* splitterMain = new wxSplitterWindow(mainPanel, wxID_ANY);
	splitterMain->SetSashGravity(0.2);

	wxBoxSizer* Sizer1 = new wxBoxSizer(wxHORIZONTAL);

	wxPanel* leftPanel = new wxPanel(splitterMain, wxID_ANY);
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

	wxBoxSizer* ss4 = new wxBoxSizer(wxVERTICAL);
	ss4->Add(random, 0, wxALIGN_CENTER | wxALL, 20);
	Sizer2->Add(ss4, 1, wxEXPAND);

	leftPanel->SetSizer(Sizer2);

	//Sizer1->Add(leftPanel, 0, wxEXPAND);

	wxScrolledWindow* rightPanel = new wxScrolledWindow(splitterMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxHSCROLL);
	rightPanel->SetScrollRate(5, 5);
	setRightControls(rightPanel, dicTypeInt, searchTypeInt, Word);

	wxBoxSizer* Sizer3 = new wxBoxSizer(wxVERTICAL);

	/*wxBoxSizer* wordSizer = new wxBoxSizer(wxHORIZONTAL);
	wordSizer->Add(word, 0, wxLEFT, 20);*/
	Sizer3->Add(word, 0, wxLEFT | wxTOP, 20);

	for (int i = 0; i < editDef.size(); i++)
	{
		Sizer3->Add(editDef[i], 0, wxALL, 10);

		Sizer3->Add(line[i], 0, wxALL, 20);
	}

	rightPanel->SetSizer(Sizer3);
	//Sizer1->Add(rightPanel,1,wxEXPAND|wxALL,20);

	splitterMain->SplitVertically(leftPanel, rightPanel);
	splitterMain->SetSashPosition(225);  // Adjust the initial sash position
	Sizer1->Add(splitterMain, 1, wxEXPAND);

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



	suggestionBox = new SuggestionListBox(panel, dic, SA, dicTypeInt, searchTypeInt, wxSize(450, 33));
	Bind(wxEVT_TEXT, &searchPage::OnTextChange, this, suggestionBox->searchInput->GetId());
	Bind(wxEVT_BUTTON, &searchPage::OnSuggestionBoxToggle, this, suggestionBox->searchInput->GetId());
	Bind(wxEVT_LISTBOX, &searchPage::OnSuggestionBoxSelect, this, suggestionBox->suggest->GetId());



	wxBitmap bmOrigin(wxT("../../../../picture/Origin-Copy.png"), wxBITMAP_TYPE_PNG);
	origin = new wxBitmapButton(panel, wxID_ANY, bmOrigin, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	origin->SetBackgroundColour("#38435A");
	origin->Bind(wxEVT_BUTTON, &searchPage::OnOriginButtonClicked, this, origin->GetId());

	wxBitmap bmAddButton(wxT("../../../../picture/addButton-Copy.png"), wxBITMAP_TYPE_PNG);
	add = new wxBitmapButton(panel, wxID_ANY, bmAddButton, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	add->SetBackgroundColour("#38435A");
	add->Bind(wxEVT_BUTTON, &searchPage::OnAddButtonClicked, this, add->GetId());

}


void searchPage::setControls(wxPanel* panel, int& dicTypeInt, int& searchTypeInt, std::string Word)
{
	wxFont font(14, wxFONTFAMILY_DEFAULT, wxBOLD, wxFONTWEIGHT_NORMAL, false, "Varela Round");

	wxBitmap bmLike(wxT("../../../../picture/heart.png"), wxBITMAP_TYPE_PNG);
	like = new wxBitmapButton(panel, wxID_ANY, bmLike, wxDefaultPosition, wxDefaultSize);
	like->SetBackgroundColour("#F8D65B");
	like->Bind(wxEVT_BUTTON, &searchPage::OnLikeButtonClicked, this, like->GetId());

	wxBitmap bmDel(wxT("../../../../picture/bin.png"), wxBITMAP_TYPE_PNG);
	del = new wxBitmapButton(panel, wxID_ANY, bmDel, wxDefaultPosition, wxDefaultSize);
	del->SetBackgroundColour("#F8D65B");
	del->Bind(wxEVT_BUTTON, &searchPage::OnDelButtonClicked, this, del->GetId());

	wxBitmap bmFix(wxT("../../../../picture/publishing.png"), wxBITMAP_TYPE_PNG);
	fix = new wxBitmapButton(panel, wxID_ANY, bmFix, wxDefaultPosition, wxDefaultSize);
	fix->SetBackgroundColour("#F8D65B");
	fix->Bind(wxEVT_BUTTON, &searchPage::OnFixButtonClicked, this, fix->GetId());

	wxBitmap bmRan(wxT("../../../../picture/random.png"), wxBITMAP_TYPE_PNG);
	random = new wxBitmapButton(panel, wxID_ANY, bmRan, wxDefaultPosition, wxDefaultSize);
	random->SetBackgroundColour("#F8D65B");
	random->Bind(wxEVT_BUTTON, &searchPage::OnRandomButtonClicked, this, random->GetId());


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
	line.resize(defs.size() + 1);
	wxBitmap bmLine(wxT("../../../../picture/Line.png"), wxBITMAP_TYPE_PNG);

	const int maxWidth = 824;

	for (int i = 0; i < defs.size(); i++)
	{
		//def[i] = new wxStaticText(panel, wxID_ANY, wxString::FromUTF8(defs[i]), wxDefaultPosition, wxDefaultSize);
		editDef[i] = new wxTextCtrl(panel, wxID_ANY, wxString::FromUTF8(defs[i]), wxDefaultPosition, wxSize(maxWidth, wxDefaultSize.GetHeight()), wxTE_READONLY | wxNO_BORDER | wxTE_NO_VSCROLL | wxTE_MULTILINE);

		editDef[i]->SetFont(font);
		//def[i]->Hide();

		//def[i]->SetFont(font);
		editDef[i]->SetFont(font);
	}


	for (int i = 0; i < def.size(); i++)
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
	int dicTypeInt = this->dicTypeInt;
	int searchTypeInt = this->searchTypeInt;
	wxWindowList children = mainPanel->GetChildren();
	wxScrolledWindow* rightPanel = nullptr;

	// Assuming rightPanel is the second child in the mainSplitter
	if (children.size() > 0)
	{
		wxSplitterWindow* mainSplitter = dynamic_cast<wxSplitterWindow*>(children.Item(0)->GetData());
		if (mainSplitter)
		{
			wxWindowList splitterChildren = mainSplitter->GetChildren();
			if (splitterChildren.size() > 1)
			{
				rightPanel = dynamic_cast<wxScrolledWindow*>(splitterChildren.Item(1)->GetData());
			}
		}
	}

	// If rightPanel is successfully retrieved, update its controls
	if (rightPanel)
	{
		rightPanel->DestroyChildren();
		wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);
		rightPanel->SetSizer(rightSizer);

		wxFont Wordfont(35, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_MAX, wxFONTWEIGHT_SEMIBOLD, false, "Varela Round");
		wxFont font(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_MAX, wxFONTWEIGHT_SEMIBOLD, false, "Varela Round");

		word = new wxStaticText(rightPanel, wxID_ANY, wxString::FromUTF8(selectedWord), wxDefaultPosition, wxDefaultSize);
		word->SetFont(Wordfont);
		rightSizer->Add(word, 0, wxLEFT | wxTOP, 20);

		editWord = new wxTextCtrl(rightPanel, wxID_ANY, word->GetLabel(), wxDefaultPosition, wxDefaultSize);
		editWord->SetFont(Wordfont);
		editWord->Hide();
		rightSizer->Add(editWord, 0, wxLEFT | wxTOP, 20);

		std::vector<std::string> defs = dic[dicTypeInt].search(selectedWord);
		if (defs.empty()) {
			defs = dic[dicTypeInt].suggestCorrections(selectedWord, 2);
		}

		editDef.resize(defs.size());
		line.resize(defs.size() + 1);
		wxBitmap bmLine(wxT("../../../../picture/Line.png"), wxBITMAP_TYPE_PNG);

		int maxWidth = rightPanel->GetSize().GetWidth() * 0.99;

		for (int i = 0; i < defs.size(); i++)
		{
			editDef[i] = new wxTextCtrl(rightPanel, wxID_ANY, wxString::FromUTF8(defs[i]), wxDefaultPosition, wxSize(maxWidth, wxDefaultSize.GetHeight()), wxTE_MULTILINE | wxTE_READONLY | wxNO_BORDER | wxTE_NO_VSCROLL);
			editDef[i]->SetFont(font);
			rightSizer->Add(editDef[i], 0, wxALL, 10);

			line[i] = new wxStaticBitmap(rightPanel, wxID_ANY, bmLine, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
			rightSizer->Add(line[i], 0, wxALL, 20);
		}

		rightPanel->Layout();
		rightPanel->Refresh();
		mainPanel->Layout();
	}
}

void searchPage::OnLikeButtonClicked(wxCommandEvent& event)
{
	std::string likedWord = Word;
	std::vector<std::string> defs = dic[dicTypeInt].search(likedWord);
	if (defs.empty()) {
		defs = dic[dicTypeInt].suggestCorrections(likedWord, 2);
	}

	HandleFavoriteOperations(likedWord, defs, dicTypeInt);
}

void searchPage::OnRandomButtonClicked(wxCommandEvent& event)
{
	this->Word = WOTD(SA[lists->GetSelection()]);
	UpdateRightPanel();
}

void searchPage::HandleFavoriteOperations(const std::string& word, const std::vector<std::string>& definitions, int dicTypeInt) {
	std::string basePath = "Data_Storage/Favorite/";

	std::string favoriteFile;
	switch (dicTypeInt) {
	case 0:
		favoriteFile = basePath + "EngToEng.bin";
		break;
	case 1:
		favoriteFile = basePath + "EngToVie.bin";
		break;
	case 2:
		favoriteFile = basePath + "VieToEng.bin";
		break;
	case 3:
		favoriteFile = basePath + "Slang.bin";
		break;
	case 4:
		favoriteFile = basePath + "Emoji.bin";
		break;
	default:
		std::cerr << "Invalid dictionary type." << std::endl;
		return;
	}

	favoriteManager.loadFavorite(favoriteFile);

	if (!definitions.empty()) {
		favoriteManager.addFavorite(word, definitions);
		favoriteManager.saveFavorite(favoriteFile);
	}
	else {
		std::cerr << "No definitions found to save to favorite." << std::endl;
	}
}

void searchPage::OnSearchButtonClicked(wxCommandEvent& event)
{
	Word = suggestionBox->getSearchInput();
	suggestionBox->suggest->Hide();
	OnSuggestionBoxToggle(event);
	int dicTypeInt = this->dicTypeInt;
	int searchTypeInt = this->dicTypeInt;

	UpdateRightPanel();

	std::string searchedWord = Word;
	std::vector<std::string> defs = dic[dicTypeInt].search(searchedWord);
	if (defs.empty()) {
		defs = dic[dicTypeInt].suggestCorrections(searchedWord, 2);
	}

	HandleHistoryOperations(searchedWord, defs, dicTypeInt);
}

void searchPage::HandleHistoryOperations(const std::string& word, const std::vector<std::string>& definitions, int dicTypeInt) {
	std::string basePath = "Data_Storage/History/";

	std::string historyFile;
	switch (dicTypeInt) {
	case 0:
		historyFile = basePath + "EngToEng.bin";
		break;
	case 1:
		historyFile = basePath + "EngToVie.bin";
		break;
	case 2:
		historyFile = basePath + "VieToEng.bin";
		break;
	case 3:
		historyFile = basePath + "Slang.bin";
		break;
	case 4:
		historyFile = basePath + "Emoji.bin";
		break;
	default:
		std::cerr << "Invalid dictionary type." << std::endl;
		return;
	}

	historyManager.loadHistory(historyFile);

	if (!definitions.empty()) {
		historyManager.addHistory(word, definitions);
		historyManager.saveHistory(historyFile);
	}
	else {
		std::cerr << "No definitions found to save to history." << std::endl;
	}
}

void searchPage::OnDicTypeChanged(wxCommandEvent& event)
{
	dicTypeInt = lists->getDicType();
	suggestionBox->UpdateSuggestListBox(dic, SA, dicTypeInt, searchTypeInt);
}

void searchPage::OnSearchTypeChanged(wxCommandEvent& event)
{
	searchTypeInt = choice->getSearchType();
	suggestionBox->UpdateSuggestListBox(dic, SA, dicTypeInt, searchTypeInt);
}

void searchPage::OnDelButtonClicked(wxCommandEvent& event)
{
	dic[dicTypeInt].remove(Word);
	SA[dicTypeInt].remove(Word);
	SA[dicTypeInt].rebuildSuffixArray();
	Word = WOTD(SA[dicTypeInt]);
	UpdateRightPanel();
}

void searchPage::OnFixButtonClicked(wxCommandEvent& event)
{
	static bool isEditing = false;
	std::vector<wxString> wstr;

	for (auto& defCtrl : editDef)
	{
		defCtrl->SetEditable(!isEditing);
		defCtrl->SetBackgroundColour(isEditing ? wxColour(255, 255, 255) : wxColour(248, 214, 91));
		wstr.push_back(defCtrl->GetValue());
	}
	if (isEditing)
	{
		std::vector<std::string> str;
		std::string text;
		for (auto& w : wstr)
		{
			std::string s = std::string(w.mb_str(wxConvUTF8));
			text += s + '|';
			str.push_back(s);
		}
		dic[dicTypeInt].editMeaning(Word, str);
		SA[dicTypeInt].update(Word, text);
		SA[dicTypeInt].rebuildSuffixArray();
	}
	isEditing = !isEditing;

	mainPanel->Layout();
	mainPanel->Refresh();
}

void searchPage::OnOriginButtonClicked(wxCommandEvent& event)
{
	dic[dicTypeInt].deleteTree();
	switch (dicTypeInt)
	{
	case 0:
		for (int i = 0; i <= 27; i++) {
			std::string c = std::to_string(i + 1);
			std::string s = "Data_Storage/Eng2Eng/Origin/";
			s += c;
			s += ".txt";
			dic[dicTypeInt].loadfile(s);
		}
		SA[dicTypeInt] = SuffixArray(Origin, EE);
		break;
	case 1:
		for (int i = 0; i <= 27; i++) {
			std::string c = std::to_string(i + 1);
			std::string s = "Data_Storage/Eng2Viet/Origin/";
			s += c;
			s += ".txt";
			dic[dicTypeInt].loadfile(s);
		}
		SA[dicTypeInt] = SuffixArray(Origin, EV);
		break;
	case 2:
		for (int i = 0; i <= 24; i++) {
			std::string c = std::to_string(i + 1);
			std::string s = "Data_Storage/Viet2Eng/Origin/";
			s += c;
			s += ".txt";
			dic[dicTypeInt].loadfile(s);
		}
		SA[dicTypeInt] = SuffixArray(Origin, VE);
		break;
	case 3:
		dic[dicTypeInt].loadfile("Data_Storage/Slang/Origin/slangs.txt");
		SA[dicTypeInt] = SuffixArray(Origin, SLANG);
		break;
	case 4:
		dic[dicTypeInt].loadfile("Data_Storage/Emoji/Origin/emoji_df.txt");
		SA[dicTypeInt] = SuffixArray(Origin, EMOJI);
		break;
	default:
		break;
	}
	wxMessageBox("Reset to origin successfully", "Reset to origin", wxOK | wxICON_INFORMATION);
	suggestionBox->UpdateSuggestListBox(dic, SA, dicTypeInt, searchTypeInt);

}

void searchPage::OnAddButtonClicked(wxCommandEvent& event)
{
	addDialog dialog(this, "Adding Dialog");
	dialog.ShowModal();
	if (dialog.isAdded())
	{
		std::string word = dialog.getWord();
		std::vector<std::string> defs = dialog.getDef();
		for (auto& d : defs) {
			dic[dicTypeInt].insert(word, d);
			SA[dicTypeInt].insert(word, d);
		}
		SA[dicTypeInt].rebuildSuffixArray();
		suggestionBox->UpdateSuggestListBox(dic, SA, dicTypeInt, searchTypeInt);
		wxMessageBox("Add successfully", "Add", wxOK | wxICON_INFORMATION);
	}
}