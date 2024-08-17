#include "favoritePage.h"
#include "dicType.h"

favoritePage::favoritePage(wxWindow* parent, int& dicTypeInt) : wxWindow(parent, wxID_ANY)
{
    this->SetBackgroundColour("#FFFFFF");
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Create panel and sizers
    // Top panel
    wxPanel* topPanel = new wxPanel(this, wxID_ANY);
    topPanel->SetBackgroundColour("#38435A");

    setTopControls(topPanel, dicTypeInt);

    wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer* s1 = new wxBoxSizer(wxVERTICAL);
    s1->Add(home, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 20);
    topSizer->Add(s1, 0, wxTOP | wxBOTTOM | wxEXPAND, 20);

    wxBoxSizer* s2 = new wxBoxSizer(wxVERTICAL);
    s2->Add(searchInput, 0, wxEXPAND | wxLEFT, 10);
    topSizer->Add(s2, 1, wxTOP | wxBOTTOM | wxEXPAND, 20);

    wxBoxSizer* s3 = new wxBoxSizer(wxVERTICAL);
    s3->Add(lists, 0, wxALIGN_CENTER | wxLEFT, 20);
    topSizer->Add(s3, 0, wxTOP | wxBOTTOM | wxEXPAND, 20);

    wxBoxSizer* s5 = new wxBoxSizer(wxVERTICAL);
    s5->Add(games, 0, wxALIGN_CENTER | wxLEFT, 30);
    topSizer->Add(s5, 0, wxTOP | wxBOTTOM | wxEXPAND, 20);

    wxBoxSizer* s4 = new wxBoxSizer(wxVERTICAL);
    s4->Add(origin, 0, wxALIGN_CENTER | wxLEFT, 40);
    topSizer->Add(s4, 0, wxTOP | wxBOTTOM | wxEXPAND, 20);

    wxBoxSizer* s6 = new wxBoxSizer(wxVERTICAL);
    s6->Add(add, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 30);
    topSizer->Add(s6, 0, wxTOP | wxBOTTOM | wxEXPAND, 20);

    topPanel->SetSizer(topSizer);

    mainSizer->Add(topPanel, 0, wxEXPAND);
    this->SetSizer(mainSizer);
}

void favoritePage::setTopControls(wxPanel* panel, int& dicTypeInt)
{
    wxBitmap bmHome(wxT("../../../../picture/home.png"), wxBITMAP_TYPE_PNG);
    home = new wxBitmapButton(panel, wxID_ANY, bmHome, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
    home->SetBackgroundColour("#38435A");

    wxFont font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_MAX, wxFONTWEIGHT_SEMIBOLD, false, "Varela Round");

    searchInput = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(450, 33));
    searchInput->SetFont(font);
    searchInput->SetHint("Search...");

    games = new wxButton(panel, wxID_ANY, "Games", wxDefaultPosition, wxSize(80, 33), wxNO_BORDER);
    games->SetBackgroundColour("#38435A");
    games->SetForegroundColour("#FFFFFF");
    games->SetFont(font);
    games->Bind(wxEVT_BUTTON, &favoritePage::OnGamesButtonClicked, this);

    lists = new dicType(panel, dicTypeInt);
    lists->SetSize(wxSize(1270, 33));
    lists->SetFont(font);

    wxBitmap bmOrigin(wxT("../../../../picture/Origin-Copy.png"), wxBITMAP_TYPE_PNG);
    origin = new wxBitmapButton(panel, wxID_ANY, bmOrigin, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
    origin->SetBackgroundColour("#38435A");

    wxBitmap bmAddButton(wxT("../../../../picture/addButton-Copy.png"), wxBITMAP_TYPE_PNG);
    add = new wxBitmapButton(panel, wxID_ANY, bmAddButton, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
    add->SetBackgroundColour("#38435A");
}

void favoritePage::OnGamesButtonClicked(wxCommandEvent& event)
{
    wxMessageBox("Games page not implemented yet.", "Info", wxOK | wxICON_INFORMATION, this);
}
