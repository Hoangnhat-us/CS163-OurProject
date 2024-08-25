#include "dicType.h"
#include "historyPage.h"
#include "History.h"

historyPage::historyPage(wxWindow* parent, int& dicTypeInt) : wxWindow(parent, wxID_ANY)
{
    this->SetBackgroundColour("#FFFFFF");
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

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

    wxPanel* mid = new wxPanel(this, wxID_ANY);
    wxPanel* banners = new wxPanel(mid, wxID_ANY);
    banners->SetBackgroundColour("#636252");
    wxBoxSizer* ban = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer* a = new wxBoxSizer(wxHORIZONTAL);
    wxBitmap historyBanner(wxT("../../../../picture/historyBanner.png"), wxBITMAP_TYPE_PNG);
    wxStaticBitmap* banner = new wxStaticBitmap(banners, wxID_ANY, historyBanner);
    a->Add(banner, 1, wxALIGN_CENTER);

    banners->SetSizer(a);
    ban->Add(banners, 1, wxALIGN_CENTER);

    mid->SetSizer(ban);
    mainSizer->Add(mid, 0, wxEXPAND);

    wxScrolledWindow* main = new wxScrolledWindow(this);
    setMain(main);
    mainSizer->Add(main, 1, wxEXPAND);

    this->SetSizer(mainSizer);
}

void historyPage::setTopControls(wxPanel* panel, int& dicTypeInt)
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
    games->Bind(wxEVT_BUTTON, &historyPage::OnGamesButtonClicked, this);

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

wxPanel* historyPage::wordsHistoryTable(wxWindow* parent)
{
    wxPanel* mainPanel = new wxPanel(parent, wxID_ANY);
    wxBoxSizer* contentSizer = new wxBoxSizer(wxVERTICAL);

    wxGrid* historyGrid = new wxGrid(mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    historyGrid->CreateGrid(1, 2);
    historyGrid->SetColLabelValue(0, "Word");
    historyGrid->SetColLabelValue(1, "Definition");

    historyGrid->SetRowSize(0, 250);
    historyGrid->SetColSize(0, 200);
    historyGrid->SetColSize(1, 800);
    historyGrid->SetDefaultCellAlignment(wxALIGN_CENTER, wxALIGN_CENTER);
    historyGrid->SetGridLineColour(*wxLIGHT_GREY);
    historyGrid->SetReadOnly(0, 0);

    contentSizer->Add(historyGrid, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 20);
    mainPanel->SetSizer(contentSizer);

    HistoryManager historyManager;
    historyManager.loadHistory("Data_Storage/history.bin");
    historyManager.viewHistory(historyGrid);

    return mainPanel;
}

void historyPage::OnGamesButtonClicked(wxCommandEvent& event)
{
    wxMessageBox("Games page not implemented yet.", "Info", wxOK | wxICON_INFORMATION, this);
}

void historyPage::setMain(wxScrolledWindow* main)
{
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    wxPanel* contentPanel = wordsHistoryTable(main);
    sizer->Add(contentPanel, 1, wxEXPAND | wxALL, 20);
    main->SetSizer(sizer);
    main->SetScrollbars(20, 20, 50, 50);
    main->SetScrollRate(5, 5);
}
