#include"Search.h"

void SuggestionListBox::UpdateSuggestions(const wxString& prefix) {
    Clear();
    std::vector<std::string> suggestions = tst.searchPrefix2(prefix.ToStdString());

    for (const auto& suggestion : suggestions) {
        Append(wxString::FromUTF8(suggestion));
    }

    if (!IsShown() && !suggestions.empty()) {
        Show();
    }
    else if (IsShown() && suggestions.empty()) {
        Hide();
    }
}

SuggestionListBox::SuggestionListBox(wxWindow* parent, std::vector<TST>& tst,int& dicTypeInt, int& searchType)
    : wxListBox(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxLB_SINGLE | wxLB_ALWAYS_SB)
{
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
    Hide();  // Initially hide the suggestion box
}
