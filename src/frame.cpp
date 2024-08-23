#include "frame.h"
#include <wx/simplebook.h>
frame::frame() : wxFrame(NULL, wxID_ANY, "wxSimplebook Example")
{
	// Tạo wxSimplebook
	book = new wxSimplebook(this, wxID_ANY);
	dic = std::vector<TST>(4);

	SuffixArray SA(CSV, EE);
	std::string searchWord = WOTD(SA);

	for (int i = 0; i <= 27; i++) {
		std::string c = std::to_string(i + 1);
		std::string s = "Data_Storage/Eng2Eng/Origin/";
		s += c;
		s += ".txt";
		dic[0].loadfile(s);
	}
	for (int i = 0; i <= 27; i++) {
		std::string c = std::to_string(i + 1);
		std::string s = "Data_Storage/Eng2Viet/Origin/";
		s += c;
		s += ".txt";
		dic[1].loadfile(s);
	}

	home = new mainPage(book, dicTypeInt, searchTypeInt, searchWord, dic);
	search = new searchPage(book, dicTypeInt, searchTypeInt, searchWord, dic);
	favorite = new favoritePage(book, dicTypeInt);
	his = new historyPage(book, dicTypeInt);

	book->AddPage(home, "Home");
	book->AddPage(search, "Search");
	book->AddPage(favorite, "Favorite");
	book->AddPage(his, "History");


	book->SetSelection(2);

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(book, 1, wxEXPAND);
	this->SetSizerAndFit(sizer);

	home->Random->Bind(wxEVT_BUTTON, &frame::switchToSearch, this);
	home->searchButton->Bind(wxEVT_BUTTON, &frame::switchToSearch, this);
	home->history->Bind(wxEVT_BUTTON, &frame::switchToHis, this);
	home->FavWords->Bind(wxEVT_BUTTON, &frame::switchToFav, this);


	Bind(wxEVT_CLOSE_WINDOW, &frame::OnExit, this);

	search->home->Bind(wxEVT_BUTTON, &frame::switchToHome, this);
	his->home->Bind(wxEVT_BUTTON, &frame::switchToHome, this);
	favorite->Bind(wxEVT_BUTTON, &frame::switchToHome, this);

}

void frame::OnButtonClicked(wxCommandEvent& event)
{
	Close(true);
}

void frame::OnExit(wxCloseEvent& event)
{
	if (wxMessageBox("Are you sure to quit?", "Confirm", wxICON_QUESTION | wxYES_NO) == wxYES)
	{
		for (int i = 0; i < dic.size(); i++) {
			dic[i].deleteTree();
		}
		Destroy();
	}
	else
	{
		event.Veto();
	}
}

void frame::switchToSearch(wxCommandEvent& event)
{
	book->SetSelection(1);
}

void frame::switchToHome(wxCommandEvent& event)
{
	book->SetSelection(1);
}

void frame::switchToFav(wxCommandEvent& event)
{
	book->SetSelection(2);
}

void frame::switchToHis(wxCommandEvent& event)
{
	book->SetSelection(3);
}
