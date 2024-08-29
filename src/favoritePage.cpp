#include "dicType.h"
#include "favoritePage.h"
#include "Favorite.h"

favoritePage::favoritePage(wxWindow* parent, int& dicTypeInt)
    : wxWindow(parent, wxID_ANY), dicTypeInt(dicTypeInt) {

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
    banners->SetBackgroundColour("#ff82a8");
    wxBoxSizer* ban = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer* a = new wxBoxSizer(wxHORIZONTAL);
    wxBitmap favoriteBanner(wxT("../../../../picture/favoriteBanner.png"), wxBITMAP_TYPE_PNG);
    wxStaticBitmap* banner = new wxStaticBitmap(banners, wxID_ANY, favoriteBanner);
    a->Add(banner, 1, wxALIGN_CENTER);

    banners->SetSizer(a);
    ban->Add(banners, 1, wxALIGN_CENTER);

    mid->SetSizer(ban);
    mainSizer->Add(mid, 0, wxEXPAND);

    wxScrolledWindow* main = new wxScrolledWindow(this);
    setMain(main);
    mainSizer->Add(main, 1, wxEXPAND);

    this->SetSizer(mainSizer);

    Bind(wxEVT_SHOW, &favoritePage::OnShow, this);
}

void favoritePage::setTopControls(wxPanel* panel, int& dicTypeInt) {
    wxBitmap bmHome(wxT("../../../../picture/home.png"), wxBITMAP_TYPE_PNG);
    home = new wxBitmapButton(panel, wxID_ANY, bmHome, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
    home->SetBackgroundColour("#38435A");

    wxFont font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_MAX, wxFONTWEIGHT_SEMIBOLD, false, "Varela Round");

    lists = new dicType(panel, dicTypeInt);
    lists->SetSize(wxSize(1270, 33));
    lists->SetFont(font);
    lists->Bind(wxEVT_COMBOBOX, &favoritePage::OnDicTypeChanged, this);
}

wxPanel* favoritePage::wordsFavoriteTable(wxWindow* parent) {
    wxPanel* mainPanel = new wxPanel(parent, wxID_ANY);
    wxBoxSizer* contentSizer = new wxBoxSizer(wxVERTICAL);

    favoriteGrid = new wxGrid(mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    favoriteGrid->CreateGrid(0, 3);  // 3 columns to include the "Remove" column

    favoriteGrid->SetColLabelValue(0, "Word");
    favoriteGrid->SetColLabelValue(1, "Definition");
    favoriteGrid->SetColLabelValue(2, "Remove");

    favoriteGrid->SetColSize(0, 100);  // Word column width
    favoriteGrid->SetColSize(1, 900);  // Definition column width
    favoriteGrid->SetColSize(2, 100);  // Remove button column width

    favoriteGrid->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);
    favoriteGrid->SetGridLineColour(*wxLIGHT_GREY);

    contentSizer->Add(favoriteGrid, 1, wxEXPAND | wxALL, 20);
    mainPanel->SetSizer(contentSizer);

    refreshFavoriteGrid();

    // Bind the event here after the grid is initialized
    favoriteGrid->Bind(wxEVT_GRID_CELL_LEFT_CLICK, &favoritePage::OnRemoveButtonClicked, this);

    return mainPanel;
}

void favoritePage::setMain(wxScrolledWindow* main) {
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    wxPanel* contentPanel = wordsFavoriteTable(main);
    sizer->Add(contentPanel, 1, wxEXPAND);
    main->SetSizer(sizer);
    main->SetScrollRate(5, 5);
}

void favoritePage::OnShow(wxShowEvent& event) {
    if (event.IsShown()) {
        refreshFavoriteGrid();
    }
    event.Skip();
}

void favoritePage::refreshFavoriteGrid() {
    if (!favoriteGrid) return;

    int currentRows = favoriteGrid->GetNumberRows();
    if (currentRows > 0) {
        favoriteGrid->DeleteRows(0, currentRows);
    }

    std::string favoriteFilePath;

    switch (dicTypeInt) {
    case 0:
        favoriteFilePath = "Data_Storage/Favorite/EngToEng.bin";
        break;
    case 1:
        favoriteFilePath = "Data_Storage/Favorite/EngToVie.bin";
        break;
    case 2:
        favoriteFilePath = "Data_Storage/Favorite/VieToEng.bin";
        break;
    case 3:
        favoriteFilePath = "Data_Storage/Favorite/Slang.bin";
        break;
    case 4:
        favoriteFilePath = "Data_Storage/Favorite/Emoji.bin";
        break;
    default:
        wxLogError("Unknown dictionary type.");
        return;
    }
    favoriteManager.loadFavorite(favoriteFilePath);

    const auto& favoriteData = favoriteManager.getFavoriteData();
    int numRows = static_cast<int>(favoriteData.size());

    if (numRows > 0) {
        favoriteGrid->AppendRows(numRows);
    }

    for (int row = 0; row < numRows; ++row) {
        const auto& [word, definitions] = favoriteData[row];

        wxString wxWord = wxString::FromUTF8(word.c_str());
        wxString combinedDefinitions;
        for (const auto& def : definitions) {
            if (!def.empty()) {
                combinedDefinitions += wxString::FromUTF8(def.c_str()) + "\n";  // Combine into single cell with newlines
            }
        }

        if (!combinedDefinitions.IsEmpty()) {
            combinedDefinitions.RemoveLast();  // Remove the trailing newline
        }

        if (row < favoriteGrid->GetNumberRows()) {
            favoriteGrid->SetCellValue(row, 0, wxWord);
            favoriteGrid->SetCellValue(row, 1, combinedDefinitions);

            wxGridCellAttr* attr = new wxGridCellAttr();
            attr->SetOverflow(false);
            attr->SetReadOnly(true);
            attr->SetRenderer(new wxGridCellAutoWrapStringRenderer());
            favoriteGrid->SetAttr(row, 1, attr);

            int lineCount = std::count(combinedDefinitions.begin(), combinedDefinitions.end(), '\n') + 1;
            int rowHeight = lineCount * favoriteGrid->GetDefaultRowSize();
            favoriteGrid->SetRowSize(row, rowHeight);

            // Set "Remove" label for cells in the Remove column
            favoriteGrid->SetCellValue(row, 2, "Remove");
        }
    }

    favoriteGrid->ForceRefresh();  // Force the grid to refresh and display the new data
    mainSizer->Layout();
}

void favoritePage::OnRemoveButtonClicked(wxGridEvent& event) {
    int row = event.GetRow();
    int col = event.GetCol();

    if (col == 2) {
        wxString word = favoriteGrid->GetCellValue(row, 0);  // Get the word from the first column
        std::string favoriteFilePath;

        switch (dicTypeInt) {
        case 0:
            favoriteFilePath = "Data_Storage/Favorite/EngToEng.bin";
            break;
        case 1:
            favoriteFilePath = "Data_Storage/Favorite/EngToVie.bin";
            break;
        case 2:
            favoriteFilePath = "Data_Storage/Favorite/VieToEng.bin";
            break;
        case 3:
            favoriteFilePath = "Data_Storage/Favorite/Slang.bin";
            break;
        case 4:
            favoriteFilePath = "Data_Storage/Favorite/Emoji.bin";
            break;
        default:
            wxLogError("Unknown dictionary type.");
            return;
        }

        // Remove the favorite word from the file
        favoriteManager.removeFavorite(std::string(word.mb_str()), favoriteFilePath);
        refreshFavoriteGrid();  // Refresh grid after removing the favorite
    }
    else {
        // Ignore clicks on other columns
        event.Skip(); // Skip the event to allow other default processing (like selecting the cell)
    }
}


void favoritePage::OnDicTypeChanged(wxCommandEvent& event) {
    dicTypeInt = lists->getDicType();
    refreshFavoriteGrid();
}

