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
	game = new gamePage(book, dicTypeInt, searchTypeInt, searchWord, dic, SA);

	book->AddPage(home, "Home");
	book->AddPage(search, "Search");
	book->AddPage(favorite, "Favorite");
	book->AddPage(his, "History");
	book->AddPage(game, "Game");


	book->SetSelection(0);

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(book, 1, wxEXPAND);
	this->SetSizerAndFit(sizer);

	home->Random->Bind(wxEVT_BUTTON, &frame::switchToSearch, this);
	home->history->Bind(wxEVT_BUTTON, &frame::switchToHis, this);
	home->FavWords->Bind(wxEVT_BUTTON, &frame::switchToFav, this);
	home->WordGames->Bind(wxEVT_BUTTON, &frame::switchToGame, this);


	Bind(wxEVT_CLOSE_WINDOW, &frame::OnExit, this);

	search->home->Bind(wxEVT_BUTTON, &frame::switchToHome, this);
	his->home->Bind(wxEVT_BUTTON, &frame::switchToHome, this);
	favorite->Bind(wxEVT_BUTTON, &frame::switchToHome, this);
	game->home->Bind(wxEVT_BUTTON, &frame::switchToHome, this);

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
		save2file("Data_Storage/Eng2Eng/Current/eng2eng.txt", dic[0], SA[0]);
		save2file("Data_Storage/Eng2Viet/Current/eng2viet.txt", dic[1], SA[1]);
		save2file("Data_Storage/Viet2Eng/Current/viet2eng.txt", dic[2], SA[2]);
		save2file("Data_Storage/Slang/Current/slangs.txt", dic[3], SA[3]);
		save2file("Data_Storage/Emoji/Current/emoji_df.txt", dic[4], SA[4]);



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
	search->Refresh();
	search->Update();
	book->SetSelection(1);
}

void frame::switchToHome(wxCommandEvent& event)
{
	home->Refresh();
	home->Update();
	book->SetSelection(0);
}

void frame::switchToFav(wxCommandEvent& event)
{
	favorite->Refresh();
	favorite->Update();
	book->SetSelection(2);
}

void frame::switchToHis(wxCommandEvent& event)
{
	his->Refresh();
	his->Update();
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

	
		/*for (int i = 0; i <= 27; i++) {
			std::string c = std::to_string(i + 1);
			std::string s = "Data_Storage/Eng2Eng/Origin/";
			s += c;
			s += ".txt";
			dic[0].loadfile(s);
		}
		SA[0] = SuffixArray(Origin, EE);
		
		for (int i = 0; i <= 27; i++) {
			std::string c = std::to_string(i + 1);
			std::string s = "Data_Storage/Eng2Viet/Origin/";
			s += c;
			s += ".txt";
			dic[1].loadfile(s);
		}
		SA[1] = SuffixArray(Origin, EV);
		
		for (int i = 0; i <= 24; i++) {
			std::string c = std::to_string(i + 1);
			std::string s = "Data_Storage/Viet2Eng/Origin/";
			s += c;
			s += ".txt";
			dic[2].loadfile(s);
		}
		SA[2] = SuffixArray(Origin, VE);
		
		dic[3].loadfile("Data_Storage/Slang/Origin/slangs.txt");
		SA[3] = SuffixArray(Origin, SLANG);
		
		dic[4].loadfile("Data_Storage/Emoji/Origin/emoji_df.txt");
		SA[4] = SuffixArray(Origin, EMOJI);*/
		
}

void frame::switchToGame(wxCommandEvent& event)
{
	game->Refresh();
	book->SetSelection(4);
}
