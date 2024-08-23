#include "searchType.h"

searchType::searchType(wxWindow* panel, int& searchTypeInt) : wxComboBox(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY | wxNO_BORDER)
{

	this->Append(wxT(" Word"));
	this->Append(wxT(" Def"));

	this->SetSelection(searchTypeInt);

	wxFont font(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Varela Round");
	this->SetFont(font);
}
int searchType::getSearchType()
{
	return this->GetSelection();
}

void searchType::setSearchType(int& searchTypeInt)
{
	this->SetSelection(searchTypeInt);
}