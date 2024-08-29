#include "addDialog.h"

addDialog::addDialog(wxWindow* parent, const wxString& title) : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(720, 520))
{
	this->SetBackgroundColour("#FDF2CB");

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	wxPanel* top = new wxPanel(this, wxID_ANY);
	wxPanel* banners = new wxPanel(top, wxID_ANY);
	banners->SetBackgroundColour("#38435A");
	wxBoxSizer* ban = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* a = new wxBoxSizer(wxVERTICAL);
	wxBitmap favoriteBanner(wxT("../../../../picture/addBanner.png"), wxBITMAP_TYPE_PNG);
	wxStaticBitmap* banner = new wxStaticBitmap(banners, wxID_ANY, favoriteBanner);
	a->Add(banner, 1, wxALIGN_CENTER);

	banners->SetSizer(a);

	ban->Add(banners, 1, wxALIGN_CENTER);

	top->SetSizer(ban);

	mainSizer->Add(top, 0, wxEXPAND | wxBOTTOM, 20);


	//

	wxFont font(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_MAX, wxFONTWEIGHT_SEMIBOLD, false, "Kadwa Bold");
	wxFont font1(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Varela Round");
	wxPanel* wordPanel = new wxPanel(this, wxID_ANY);


	word = new wxStaticText(wordPanel, wxID_ANY, "Word", wxDefaultPosition, wxDefaultSize);

	word->SetFont(font);

	wordInput = new wxTextCtrl(wordPanel, wxID_ANY, "", wxDefaultPosition, wxSize(506, 20));
	wordInput->SetFont(font1);
	wordInput->SetHint("Enter new word");

	wxBoxSizer* wordSizer = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* s1 = new wxBoxSizer(wxVERTICAL);
	s1->Add(word, 1, wxALIGN_LEFT);
	wordSizer->Add(s1, 1, wxEXPAND);

	wxBoxSizer* s2 = new wxBoxSizer(wxVERTICAL);
	s2->Add(wordInput, 1, wxALIGN_RIGHT);
	wordSizer->Add(s2, 1, wxEXPAND);

	wordPanel->SetSizer(wordSizer);

	mainSizer->Add(wordPanel, 1, wxALL | wxEXPAND, 20);

	//

	wxPanel* defPanel = new wxPanel(this, wxID_ANY);


	def = new wxStaticText(defPanel, wxID_ANY, "Definition", wxDefaultPosition, wxDefaultSize);
	def->SetFont(font);

	word->SetFont(font);

	defInput = new wxTextCtrl(defPanel, wxID_ANY, "", wxDefaultPosition, wxSize(506, 120), wxTE_MULTILINE);
	defInput->SetFont(font1);
	defInput->SetHint("Def 1 | Def 2 | Def 3");


	wxBoxSizer* defSizer = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* s3 = new wxBoxSizer(wxVERTICAL);
	s3->Add(def, 1, wxALIGN_LEFT);
	defSizer->Add(s3, 1, wxEXPAND);


	wxBoxSizer* s4 = new wxBoxSizer(wxVERTICAL);
	s4->Add(defInput, 1, wxALIGN_RIGHT);
	defSizer->Add(s4, 1, wxEXPAND);

	defPanel->SetSizer(defSizer);

	mainSizer->Add(defPanel, 1, wxALL | wxEXPAND, 20);

	//

	wxPanel* lastPanel = new wxPanel(this, wxID_ANY);

	// Tải hình ảnh từ file
	wxBitmap bitmap(wxT("../../../../picture/addPicture.png"), wxBITMAP_TYPE_PNG);

	// Tạo wxStaticBitmap để hiển thị hình ảnh
	pic = new wxStaticBitmap(lastPanel, wxID_ANY, bitmap, wxDefaultPosition, wxDefaultSize);

	wxBitmap bitmap1(wxT("../../../../picture/add.png"), wxBITMAP_TYPE_PNG);

	add = new wxBitmapButton(lastPanel, wxID_ANY, bitmap1, wxDefaultPosition, wxDefaultSize);


	wxBoxSizer* lastSizer = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* s5 = new wxBoxSizer(wxVERTICAL);
	s5->Add(pic, 1, wxALIGN_LEFT);
	lastSizer->Add(s5, 1, wxEXPAND);

	wxBoxSizer* s6 = new wxBoxSizer(wxVERTICAL);
	s6->Add(add, 1, wxALIGN_RIGHT);
	lastSizer->Add(s6);

	lastPanel->SetSizer(lastSizer);

	mainSizer->Add(lastPanel, 1, wxALL | wxEXPAND, 20);

	this->SetSizer(mainSizer);

	add->Bind(wxEVT_BUTTON, &addDialog::OnAddButtonClicked, this);
}
bool addDialog::isAdded()
{
	return isAdd;
}
std::string addDialog::getWord()
{
	wxString wstr = wordInput->GetValue();
	std::string str = std::string(wstr.mb_str(wxConvUTF8));
	return str;
}

std::vector < std::string> addDialog::getDef()
{
	wxString wstr = defInput->GetValue();
	std::string str = std::string(wstr.mb_str(wxConvUTF8));
	std::vector<std::string> def;
	std::string temp = "";
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '|')
		{
			def.push_back(temp);
			temp = "";
		}
		else
		{
			temp += str[i];
		}
	}
	def.push_back(temp);
	return def;
}
void addDialog::OnAddButtonClicked(wxCommandEvent& event)
{
	isAdd = true;
	Close(true);
}
