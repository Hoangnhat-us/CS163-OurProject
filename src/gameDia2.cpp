#include "gameDia2.h"

gameDia2::gameDia2(wxWindow* parent) : wxPanel(parent, wxID_ANY)
{
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    wxFont font(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_MAX, wxFONTWEIGHT_SEMIBOLD, false, "Kadwa Bold");

    // Load câu hỏi dựa trên mức độ khó
    LoadQuestion();

    // Tạo đối tượng wxStaticText để hiển thị câu hỏi (từ vựng hoặc định nghĩa)
    w = new wxStaticText(this, wxID_ANY, word, wxDefaultPosition, wxDefaultSize);
    w->SetFont(font);
    vbox->Add(w, 0, wxALIGN_CENTER);

    // Tạo lưới các nút (buttons) để hiển thị các lựa chọn đáp án
    wxGridSizer* gSizer = new wxGridSizer(2, 2, 20, 20);
    wxColour buttonColor(0, 128, 0);

    SetUpButtons();
    for (int i = 0; i < 4; ++i) {
        buttons[i]->SetFont(font);
        buttons[i]->SetBackgroundColour(buttonColor);
        buttons[i]->SetForegroundColour(*wxWHITE);
        gSizer->Add(buttons[i], 0, wxEXPAND | wxALL, 10);
    }

    vbox->Add(gSizer, 1, wxEXPAND | wxALL, 20);
    this->SetSizer(vbox);

    Bind(wxEVT_BUTTON, &gameDia2::OnButtonClicked, this, 10001);
    Bind(wxEVT_BUTTON, &gameDia2::OnButtonClicked, this, 10002);
    Bind(wxEVT_BUTTON, &gameDia2::OnButtonClicked, this, 10003);
    Bind(wxEVT_BUTTON, &gameDia2::OnButtonClicked, this, 10004);

    SetBackgroundColour(wxColour(240, 240, 240));
}

void gameDia2::LoadQuestion() {
    // Xử lý theo kiểu từ điển
    if (dicType == 0) { // Eng-Eng
        if (mode == 1) { // Chế độ 1: 1 từ vựng ra 4 định nghĩa
            LuuTru = chooseCorrectDefinition("engeng_mode1.txt", TST);
        }
        else if (mode == 2) { // Chế độ 2: 1 định nghĩa và 4 từ vựng
            LuuTru = chooseCorrectWord("engeng_mode2.txt", TST);
        }
    }
    else if (dicType == 1) { // Eng-Viet
        if (mode == 1) { // Level 1 (Easy): 1 từ vựng ra 4 định nghĩa
            LuuTru = chooseCorrectDefinition("engviet_easy.txt", TST);
        }
        else if (mode == 2) { // Level 2 (Medium): 1 định nghĩa và 4 từ vựng
            LuuTru = chooseCorrectWord("engviet_medium.txt", TST);
        }
        else if (mode == 3) { // Level 3 (Difficult): 1 từ vựng ra 4 định nghĩa
            LuuTru = chooseCorrectDefinition("engviet_difficult.txt", TST);
        }
    }
    else if (dicType == 2) { // Viet-Eng
        if (mode == 1) { // Level 1 (Easy): 
            LuuTru = chooseCorrectDefinition("vieteng_easy.txt", TST);
        }
        else if (mode == 2) { // Level 2 (Medium):
            LuuTru = chooseCorrectWord("vieteng_medium.txt", TST);
        }
        else if (mode == 3) { // Level 3 (Difficult): 
            LuuTru = chooseCorrectDefinition("vieteng_difficult.txt", TST);
        }
    }
    else if (dicType == 3) { // Slang
        if (mode == 1) { 
            LuuTru = chooseCorrectDefinition("slang_mode1.txt", TST);
        }
        else if (mode == 2) {
            LuuTru = chooseCorrectWord("slang_mode2.txt", TST);
        }
    }
    else if (dicType == 4) { // Emoji
        if (mode == 1) { 
            LuuTru = chooseCorrectDefinition("emoji_mode1.txt", TST);
        }
        else if (mode == 2) { 
            LuuTru = chooseCorrectWord("emoji_mode2.txt", TST);
        }
    }

  
    if (!LuuTru.empty()) {
        word = LuuTru[0].question;
        DapAn = LuuTru[0].answers;
        correctAnswerIndex = LuuTru[0].correctAnswerIndex;
    }
}


void gameDia2::SetUpButtons() {
    wxString labels[4] = { "A.", "B.", "C.", "D." };
    for (int i = 0; i < 4; ++i) {
        buttons[i] = new wxButton(this, 10001 + i, labels[i] + " " + DapAn[i], wxDefaultPosition, wxSize(200, 50));
    }
}

void gameDia2::OnButtonClicked(wxCommandEvent& event)
{
    if (gameEnded) return; 

    int id = event.GetId();
    int clickedIndex = id - 10001;

    if (clickedIndex == correctAnswerIndex) {
        buttons[clickedIndex]->SetBackgroundColour(wxColour(0, 255, 0));
        score++; 
    }
    else {
        buttons[clickedIndex]->SetBackgroundColour(wxColour(255, 0, 0)); 
        buttons[correctAnswerIndex]->SetBackgroundColour(wxColour(0, 255, 0));
        EndGame(); 
        return; 
    }

   
    NextQuestion();
}

void gameDia2::NextQuestion() {
    LoadQuestion();
    if (LuuTru.empty()) {
        EndGame(); 
        return;
    }

    w->SetLabel(word);
    SetUpButtons();
    for (int i = 0; i < 4; ++i) {
        buttons[i]->SetBackgroundColour(wxColour(0, 128, 0)); 
        buttons[i]->Enable();
        buttons[i]->SetLabel(wxString::Format("%s %s", wxString("ABCD")[i], DapAn[i]));
    }
}

void gameDia2::EndGame() {
    gameEnded = true; 
    wxString msg = wxString::Format("Game Over! Your score is %d", score);
        wxMessageBox(msg, "Game Over", wxOK | wxICON_INFORMATION);
}
