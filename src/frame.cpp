#include "frame.h"
#include "mainPage.h"
#include "searchPage.h"
#include "favoritePage.h"
#include <wx/simplebook.h>
#include "SuffixArray.h"
#include "Random.h"

frame::frame() : wxFrame(NULL, wxID_ANY, "wxSimplebook Example")
{
	// Tạo wxSimplebook
	wxSimplebook* book = new wxSimplebook(this, wxID_ANY);
	dic = std::vector<TST>(4);
	SuffixArray SA(CSV, EE);
	
	
	for (int i = 0; i <= 27; i++) {
		std::string c = std::to_string(i+1);
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
	std::string searchWord = WOTD(SA);
	mainPage* home = new mainPage(book, dicTypeInt, searchTypeInt, searchWord, dic);
	searchPage* search = new searchPage(book, dicTypeInt, searchTypeInt, searchWord, dic);
	favoritePage* favorite = new favoritePage(book, dicTypeInt);

	// Thêm các trang vào wxSimplebook
	book->AddPage(home, "Home");
	book->AddPage(search, "Search");
	book->AddPage(favorite, "Favorite");

	book->SetSelection(2);

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(book, 1, wxEXPAND);
	this->SetSizerAndFit(sizer);





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


}
