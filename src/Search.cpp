#include"Search.h"

void SuggestionListBox::UpdateSuggestions(const wxString& prefix) {
	suggest->Clear();

	if (isHaveunicode(prefix.ToStdString()))
	{
		if (dicTypeInt == 0) {
			suggest->Hide();
			return;
		}
		if (dicTypeInt == 1 and searchType == 0) {
			suggest->Hide();
			return;
		}
		if (dicTypeInt == 2 and searchType == 1) {
			suggest->Hide();
			return;
		}
	}
	std::string str = std::string(prefix.mb_str(wxConvUTF8));
	std::vector<std::string> suggestions;
	if (searchType == 0) {
		suggestions = tst.searchPrefix2(str);
	}
	else
	{
		suggestions = SA.search(str);
	}

	for (const auto& suggestion : suggestions) {
		suggest->Append(wxString::FromUTF8(suggestion));
	}

	if (!suggest->IsShown() && !suggestions.empty()) {
		suggest->Show();
	}
	else if (suggest->IsShown() && suggestions.empty()) {
		suggest->Hide();
	}
}

SuggestionListBox::SuggestionListBox(wxWindow* parent, std::vector<TST>& tst, std::vector<SuffixArray>& SA, int& dicTypeInt, int& searchType, wxSize size) : wxPanel(parent, wxID_ANY)
{
	wxFont font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Varela Round");

	this->dicTypeInt = dicTypeInt;
	this->searchType = searchType;
	wxPanel* panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, size);
	searchInput = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, size);
	searchInput->SetFont(font);
	searchInput->SetHint("Enter search text...");  // Placeholder tex

	suggest = new wxListBox(panel, wxID_ANY, wxDefaultPosition, wxSize(size.GetWidth(), size.GetHeight() * 5), 0, nullptr, wxLB_SINGLE | wxLB_ALWAYS_SB);
	suggest->SetFont(font);

	wxBoxSizer* main = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

	vbox->Add(searchInput);

	// Add the wxListBox to the sizer
	vbox->Add(suggest);

	panel->SetSizerAndFit(vbox);

	main->Add(panel, 1, wxEXPAND);

	// Set the sizer for the panel
	this->SetSizerAndFit(main);

	switch (dicTypeInt)
	{
	case 0:
		this->tst = tst[0];
		this->SA = SA[0];
		break;
	case 1:
		this->tst = tst[1];
		this->SA = SA[1];
		break;
	case 2:
		this->tst = tst[2];
		this->SA = SA[2];
		break;
	case 3:
		this->tst = tst[3];
		this->SA = SA[3];
		break;
	case 4:
		this->tst = tst[4];
		this->SA = SA[4];
		break;
	default:
		break;
	}
	suggest->Hide();  // Initially hide the suggestion box
}

bool SuggestionListBox::isHaveunicode(const std::string& str)
{
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] < 0)
			return true;
	}
	return false;
}

std::string SuggestionListBox::getSearchInput()
{
	wxString wstr = searchInput->GetValue();
	std::string str = std::string(wstr.mb_str(wxConvUTF8));
	if (searchType == 1) {
		auto it = std::find(str.begin(), str.end(), ':');
		it = std::find(it, str.end(), '\t');
		if (it != str.end()) {
			str = std::string(str.begin(), it - 1);
		}
	}
	return str;
}

void SuggestionListBox::OnSuggestionSelected(wxCommandEvent& event)
{
	searchInput->SetValue(suggest->GetStringSelection());
	suggest->Hide();
}
void SuggestionListBox::UpdateSuggestListBox(std::vector<TST>& dic, std::vector<SuffixArray>& SA, int& dicTypeInt, int& searchType)
{
	this->dicTypeInt = dicTypeInt;
	switch (dicTypeInt)
	{
	case 0:
		this->tst = dic[0];
		this->SA = SA[0];
		break;
	case 1:
		this->tst = dic[1];
		this->SA = SA[1];
		break;
	case 2:
		this->tst = dic[2];
		this->SA = SA[2];
		break;
	case 3:
		this->tst = dic[3];
		this->SA = SA[3];
		break;
	case 4:
		this->tst = dic[4];
		this->SA = SA[4];
		break;
	default:
		break;
	}
	this->searchType = searchType;
}
