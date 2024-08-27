#include "frame.h"
#include <wx/simplebook.h>
frame::frame() : wxFrame(NULL, wxID_ANY, "wxSimplebook Example")
{
	// Tạo wxSimplebook
	book = new wxSimplebook(this, wxID_ANY);
	dic = std::vector<TST>(5);
	SA = std::vector<SuffixArray>(5);
	LoadDic();

	//SuffixArray SA(CSV, EE);
	std::string searchWord = WOTD(SA[0]);

	home = new mainPage(book, dicTypeInt, searchTypeInt, searchWord, dic, SA);
	search = new searchPage(book, dicTypeInt, searchTypeInt, searchWord, dic, SA);
	favorite = new favoritePage(book, dicTypeInt);
	his = new historyPage(book, dicTypeInt);

	book->AddPage(home, "Home");
	book->AddPage(search, "Search");
	book->AddPage(favorite, "Favorite");
	book->AddPage(his, "History");


	book->SetSelection(0);

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
		this->dic = search->dic;
		this->SA = search->SA;
		save2file("Data_Storage/Eng2Eng/Current/eng2eng.txt", dic[0],SA[0]);
		save2file("Data_Storage/Eng2Viet/Current/eng2viet.txt", dic[1],SA[1]);
		save2file("Data_Storage/Viet2Eng/Current/viet2eng.txt", dic[2],SA[2]);
		save2file("Data_Storage/Slang/Current/slangs.txt", dic[3],SA[3]);
		save2file("Data_Storage/Emoji/Current/emoji_df.txt", dic[4],SA[4]);



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

void frame::switchToFav(wxCommandEvent& event)
{
	book->SetSelection(2);
}

void frame::switchToHis(wxCommandEvent& event)
{
	book->SetSelection(3);
}

void frame::LoadDic() {
	
	dic[0].loadfile("Data_Storage/Eng2Eng/Current/eng2eng.txt");
	dic[1].loadfile("Data_Storage/Eng2Viet/Current/eng2viet.txt");
	dic[2].loadfile("Data_Storage/Viet2Eng/Current/viet2eng.txt");
	dic[3].loadfile("Data_Storage/Slang/Current/slangs.txt");
	dic[4].loadfile("Data_Storage/Emoji/Current/emoji_df.txt");

	SA[0] = SuffixArray(Cur, EE);
	SA[1] = SuffixArray(Cur, EV);
	SA[2] = SuffixArray(Cur, VE);
	SA[3] = SuffixArray(Cur, SLANG);
	SA[4] = SuffixArray(Cur, EMOJI);
}
