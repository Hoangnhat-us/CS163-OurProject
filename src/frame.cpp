#include "favoritePage.h"
#include "frame.h"
#include "mainPage.h"
#include "Random.h"
#include "searchPage.h"
#include "SuffixArray.h"

#include <wx/simplebook.h>
frame::frame() : wxFrame(NULL, wxID_ANY, "wxSimplebook Example")
{
	// Tạo wxSimplebook
	book = new wxSimplebook(this, wxID_ANY);
	dic = std::vector<TST>(4);
	SuffixArray SA(CSV, EE);


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

	int dicTypeInt = 0;
	int searchTypeInt = 0;
	std::string searchWord = /*WOTD(SA)*/" ";
	mainPage* home = new mainPage(book, dicTypeInt, searchTypeInt, searchWord, dic);
	searchPage* search = new searchPage(book, dicTypeInt, searchTypeInt, searchWord, dic);
	favoritePage* favorite = new favoritePage(book, dicTypeInt);

	// Thêm các trang vào wxSimplebook
	book->AddPage(home, "Home");
	book->AddPage(search, "Search");
	book->AddPage(favorite, "Favorite");


	book->SetSelection(1);

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(book, 1, wxEXPAND);
	this->SetSizerAndFit(sizer);

	home->Random->Bind(wxEVT_BUTTON, &frame::switchToSearch, this);
	home->searchButton->Bind(wxEVT_BUTTON, &frame::switchToSearch, this);


	Bind(wxEVT_CLOSE_WINDOW, &frame::OnExit, this);

	search->home->Bind(wxEVT_BUTTON, &frame::switchToHome, this);


	// Đặt wxSimplebook vào khung
	//wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	//sizer->Add(book, 1, wxEXPAND);
	// Lấy kích thước màn hình
	//wxSize screenSize = wxGetDisplaySize();
	//wxSize screenSize = wxSize(1458, 866);

	// Thiết lập kích thước của frame theo kích thước màn hình
	//SetSize(screenSize);
	//this->SetSizer(sizer);
	//SetMaxSize(screenSize);
	//SetMinSize(screenSize);
	/*dic[0].~TST();
	dic[1].~TST();*/
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
	book->SetSelection(0);
}
