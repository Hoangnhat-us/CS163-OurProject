#include "dicType.h"
#include "historyPage.h"
#include "History.h"

historyPage::historyPage(wxWindow* parent, int& dicTypeInt) : wxWindow(parent, wxID_ANY), dicTypeInt(dicTypeInt) {
    this->SetBackgroundColour("#FFFFFF");
    mainSizer = new wxBoxSizer(wxVERTICAL);

    wxPanel* topPanel = new wxPanel(this, wxID_ANY);
    topPanel->SetBackgroundColour("#38435A");

    setTopControls(topPanel, dicTypeInt);

    wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer* s1 = new wxBoxSizer(wxVERTICAL);
    s1->Add(home, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 20);
    topSizer->Add(s1, 0, wxTOP | wxBOTTOM | wxEXPAND, 20);

    wxBoxSizer* s3 = new wxBoxSizer(wxVERTICAL);
    s3->Add(lists, 0, wxALIGN_CENTER | wxLEFT, 20);
    topSizer->Add(s3, 0, wxTOP | wxBOTTOM | wxEXPAND, 20);

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

    lists = new dicType(panel, dicTypeInt);
    lists->SetSize(wxSize(1270, 33));
    lists->SetFont(font);
    lists->Bind(wxEVT_COMBOBOX, &historyPage::OnDicTypeChanged, this);
}

wxPanel* historyPage::wordsHistoryTable(wxWindow* parent) {
    wxPanel* mainPanel = new wxPanel(parent, wxID_ANY);
    wxBoxSizer* contentSizer = new wxBoxSizer(wxVERTICAL);

    historyGrid = new wxGrid(mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    historyGrid->CreateGrid(0, 2);  // Start with 0 rows and 2 columns

    historyGrid->SetColLabelValue(0, "Word");
    historyGrid->SetColLabelValue(1, "Definition");

    // Set fixed column sizes
    historyGrid->SetColSize(0, 100);  // Word column width
    historyGrid->SetColSize(1, 900);  // Definition column width

    historyGrid->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);
    historyGrid->SetGridLineColour(*wxLIGHT_GREY);

    contentSizer->Add(historyGrid, 1, wxEXPAND | wxALL, 20);
    mainPanel->SetSizer(contentSizer);

    refreshHistoryGrid();  // Load initial data

    return mainPanel;
}

void historyPage::setMain(wxScrolledWindow* main) {
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    wxPanel* contentPanel = wordsHistoryTable(main);
    sizer->Add(contentPanel, 1, wxEXPAND);
    main->SetSizer(sizer);
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
    std::string historyFilePath;

    switch (dicTypeInt) {
    case 0:
        historyFilePath = "Data_Storage/History/EngToEng.bin";
        break;
    case 1:
        historyFilePath = "Data_Storage/History/EngToVie.bin";
        break;
    case 2:
        historyFilePath = "Data_Storage/History/VieToEng.bin";
        break;
    case 3:
        historyFilePath = "Data_Storage/History/Slang.bin";
        break;
    case 4:
        historyFilePath = "Data_Storage/History/Emoji.bin";
        break;
    default:
        wxLogError("Unknown dictionary type.");
        return;
    }

    historyManager.loadHistory(historyFilePath);

    const auto& historyData = historyManager.getHistoryData();
    int numRows = static_cast<int>(historyData.size());

    if (numRows > 0) {
        historyGrid->AppendRows(numRows);
    }

    for (int row = 0; row < numRows; ++row) {
        const auto& [word, definitions] = historyData[row];

        wxString wxWord = wxString::FromUTF8(word.c_str());
        wxString combinedDefinitions;
        for (const auto& def : definitions) {
            if (!def.empty()) {
                combinedDefinitions += wxString::FromUTF8(def.c_str()) + "\n";
            }
        }

        if (!combinedDefinitions.IsEmpty()) {
            combinedDefinitions.RemoveLast();  // Remove the trailing newline
        }

        if (row < historyGrid->GetNumberRows()) {
            historyGrid->SetCellValue(row, 0, wxWord);
            historyGrid->SetCellValue(row, 1, combinedDefinitions);

            // Set up cell for text wrapping
            wxGridCellAttr* attr = new wxGridCellAttr();
            attr->SetOverflow(false);
            attr->SetReadOnly(true);
            attr->SetRenderer(new wxGridCellAutoWrapStringRenderer());
            historyGrid->SetAttr(row, 1, attr);

            int lineCount = std::count(combinedDefinitions.begin(), combinedDefinitions.end(), '\n') + 1;
            int rowHeight = lineCount * historyGrid->GetDefaultRowSize();
            historyGrid->SetRowSize(row, rowHeight);
        }
    }

    historyGrid->ForceRefresh();
    mainSizer->Layout();
}

void historyPage::OnDicTypeChanged(wxCommandEvent& event) {
    dicTypeInt = lists->getDicType();
    refreshHistoryGrid();
}