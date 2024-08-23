#include"Search.h"

void SuggestionListBox::UpdateSuggestions(const wxString& prefix) {
	suggest->Clear();
	
	std::vector<std::string> suggestions = tst.searchPrefix2(prefix.ToStdString());

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

SuggestionListBox::SuggestionListBox(wxWindow* parent, std::vector<TST>& tst, int& dicTypeInt, int& searchType, wxSize size) : wxPanel(parent, wxID_ANY)
{
	wxFont font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Varela Round");


	searchInput = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, size);
	searchInput->SetFont(font);
	searchInput->SetHint("Enter search text...");  // Placeholder tex


	suggest = new  wxListBox(this, wxID_ANY, wxDefaultPosition,wxSize(size.GetWidth(),size.GetHeight()*5), 0, nullptr, wxLB_SINGLE | wxLB_ALWAYS_SB);
	suggest->SetFont(font);

	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

	vbox->Add(searchInput);

	// Add the wxListBox to the sizer
	vbox->Add(suggest);

	// Set the sizer for the panel
	this->SetSizerAndFit(vbox);

	switch (dicTypeInt)
	{
	case 0:
		this->tst = tst[0];
		break;
	case 1:
		this->tst = tst[1];
		break;
	case 2:
		this->tst = tst[2];
		break;
	case 3:
		this->tst = tst[3];
		break;
	case 4:
		this->tst = tst[4];
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
	return searchInput->GetValue().ToStdString();
}

void SuggestionListBox::OnSuggestionSelected(wxCommandEvent& event)
{
	searchInput->SetValue(suggest->GetStringSelection());
	suggest->Hide();
}