#include "dicType.h"
#include "historyPage.h"
#include "History.h"

historyPage::historyPage(wxWindow* parent, int& dicTypeInt) : wxWindow(parent, wxID_ANY) {
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

    Bind(wxEVT_SHOW, &historyPage::OnShow, this);
}

void historyPage::setTopControls(wxPanel* panel, int& dicTypeInt) {
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

wxPanel* historyPage::wordsHistoryTable(wxWindow* parent) {
    wxPanel* mainPanel = new wxPanel(parent, wxID_ANY);
    wxBoxSizer* contentSizer = new wxBoxSizer(wxVERTICAL);

    historyGrid = new wxGrid(mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    historyGrid->CreateGrid(0, 2);  // Start with 0 rows and 2 columns

    historyGrid->SetColLabelValue(0, "Word");
    historyGrid->SetColLabelValue(1, "Definition");

    // Ensure there is at least one row before trying to set its size
    if (historyGrid->GetNumberRows() == 0) {
        historyGrid->AppendRows(1);
    }

    historyGrid->SetRowSize(0, 250);
    historyGrid->SetColSize(0, 200);
    historyGrid->SetColSize(1, 800);

    historyGrid->SetDefaultCellAlignment(wxALIGN_CENTER, wxALIGN_CENTER);
    historyGrid->SetGridLineColour(*wxLIGHT_GREY);
    historyGrid->SetReadOnly(0, 0);

    contentSizer->Add(historyGrid, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 20);
    mainPanel->SetSizer(contentSizer);

    refreshHistoryGrid();

    return mainPanel;
}


void historyPage::setMain(wxScrolledWindow* main) {
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    wxPanel* contentPanel = wordsHistoryTable(main);
    sizer->Add(contentPanel, 1, wxEXPAND | wxALL, 20);
    main->SetSizer(sizer);
    main->SetScrollbars(20, 20, 50, 50);
    main->SetScrollRate(5, 5);
}

void historyPage::OnShow(wxShowEvent& event) {
    if (event.IsShown()) {
        refreshHistoryGrid();
    }
    event.Skip();
}
void historyPage::refreshHistoryGrid() {
    if (!historyGrid) return;

    // Clear existing data and remove all rows
    int currentRows = historyGrid->GetNumberRows();
    if (currentRows > 0) {
        historyGrid->DeleteRows(0, currentRows);
    }

    HistoryManager historyManager;
    historyManager.loadHistory("Data_Storage/History/EngtoEng.bin");

    const auto& historyData = historyManager.getHistoryData();

    int numRows = static_cast<int>(historyData.size());
    if (numRows > 0) {
        historyGrid->AppendRows(numRows);
    }

    for (int row = 0; row < numRows; ++row) {
        const auto& [word, definitions] = historyData[row];

        // Safely convert std::string to wxString using UTF-8
        wxString wxWord = wxString::FromUTF8(word.c_str());

        // Concatenate definitions into a single string
        wxString combinedDefinitions;
        for (const auto& def : definitions) {
            if (!def.empty()) {
                combinedDefinitions += wxString::FromUTF8(def.c_str()) + "; ";
            }
        }

        if (!combinedDefinitions.IsEmpty()) {
            combinedDefinitions.RemoveLast(2);  // Remove trailing "; "
        }

        // Safeguard row index operations
        if (row < historyGrid->GetNumberRows()) {
            historyGrid->SetCellValue(row, 0, wxWord);
            historyGrid->SetCellValue(row, 1, combinedDefinitions);
        }
        else {
            wxLogError("Attempted to access an invalid row index: %d", row);
        }
    }

    historyGrid->ForceRefresh();  // Force the grid to refresh and display the new data
}


void historyPage::OnGamesButtonClicked(wxCommandEvent& event) {
    wxMessageBox("Games page not implemented yet.", "Info", wxOK | wxICON_INFORMATION, this);
}
