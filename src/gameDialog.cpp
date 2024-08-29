#include "gameDialog.h"

gameDialog::gameDialog(wxWindow* parent, const wxString& title, std::vector<TST>& tst, std::vector<SuffixArray>& SA, int& level, int& dicType, int& mode) : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(720, 460))
{
	this->SetBackgroundColour(wxColour(240, 240, 240));
	this->tst = tst;
	this->SA = SA;
	this->level = level;
	this->dicType = dicType;
	this->mode = mode;
	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

	wxFont font(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_MAX, wxFONTWEIGHT_SEMIBOLD, false, "Kadwa Bold");

	//Load câu hỏi dựa trên mức độ khó
	LoadQuestion();

	//Tạo đối tượng wxStaticText để hiển thị câu hỏi (từ vựng hoặc định nghĩa)
	w = new wxStaticText(this, wxID_ANY, word, wxDefaultPosition, wxDefaultSize);
	w->SetFont(font);
	vbox->Add(w, 0, wxALIGN_CENTER);

	//Tạo lưới các nút (buttons) để hiển thị các lựa chọn đáp án
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

	Bind(wxEVT_BUTTON, &gameDialog::OnButtonClicked, this, 10001);
	Bind(wxEVT_BUTTON, &gameDialog::OnButtonClicked, this, 10002);
	Bind(wxEVT_BUTTON, &gameDialog::OnButtonClicked, this, 10003);
	Bind(wxEVT_BUTTON, &gameDialog::OnButtonClicked, this, 10004);
}

void gameDialog::OnButtonClicked(wxCommandEvent& event)
{
	if (gameEnded) return;

	int id = event.GetId();
	int clickedIndex = id - 10001;

	if (clickedIndex == correctAnswerIndex) {
		buttons[clickedIndex]->SetBackgroundColour(wxColour(0, 255, 0));
		score++;
		NextQuestion();
	}
	else {
		buttons[clickedIndex]->SetBackgroundColour(wxColour(255, 0, 0));
		buttons[correctAnswerIndex]->SetBackgroundColour(wxColour(0, 255, 0));
		EndGame();
	}
}

void gameDialog::LoadQuestion()
{
	//Xử lý theo kiểu từ điển và chế độ
	if (dicType == 0) { // Eng-Eng
		if (mode == 1) { // Chế độ 1: 1 từ vựng ra 4 định nghĩa
			if (level == 0) { // Easy
				LuuTru = chooseCorrectDefinition("Data_Storage/Eng2Eng/Games/Words/EasyMode.txt", tst[0]);
			}
			else if (level == 1) { // Medium
				LuuTru = chooseCorrectDefinition("Data_Storage/Eng2Eng/Games/Words/MediumMode.txt", tst[0]);
			}
			else if (level == 2) { // Difficult
				LuuTru = chooseCorrectDefinition("Data_Storage/Eng2Eng/Games/Words/HardMode.txt", tst[0]);
			}
		}
		else if (mode == 2) { // Chế độ 2: 1 định nghĩa và 4 từ vựng
			if (level == 0) { // Easy
				LuuTru = chooseCorrectWord("Data_Storage/Eng2Eng/Games/Words/EasyMode.txt", tst[0]);
			}
			else if (level == 1) { // Medium
				LuuTru = chooseCorrectWord("Data_Storage/Eng2Eng/Games/Words/MediumMode.txt", tst[0]);
			}
			else if (level == 2) { // Difficult
				LuuTru = chooseCorrectWord("Data_Storage/Eng2Eng/Games/Words/HardModet.txt", tst[0]);
			}
		}
	}
	else if (dicType == 1) { // Eng-Viet
		if (mode == 1) { // Chế độ 1: 1 từ vựng ra 4 định nghĩa
			if (level == 0) { // Easy
				LuuTru = chooseCorrectDefinition("Data_Storage/Eng2Viet/Games/Words/EasyMode.txt", tst[dicType]);
			}
			else if (level == 1) { // Medium
				LuuTru = chooseCorrectDefinition("Data_Storage/Eng2Viet/Games/Words/MediumMode.txt", tst[dicType]);
			}
			else if (level == 2) { // Difficult
				LuuTru = chooseCorrectDefinition("Data_Storage/Eng2Viet/Games/Words/HardMode.txt", tst[dicType]);
			}
		}
		else if (mode == 2) { // Chế độ 2: 1 định nghĩa và 4 từ vựng
			if (level == 0) { // Easy
				LuuTru = chooseCorrectWord("Data_Storage/Eng2Viet/Games/Words/EasyMode.txt", tst[dicType]);
			}
			else if (level == 1) { // Medium
				LuuTru = chooseCorrectWord("Data_Storage/Eng2Viet/Games/Words/MediumMode.txt", tst[dicType]);
			}
			else if (level == 2) { // Difficult
				LuuTru = chooseCorrectWord("Data_Storage/Eng2Viet/Games/Words/MediumMode.txt", tst[dicType]);
			}
		}
	}
	else if (dicType == 2) { // Viet-Eng
		if (mode == 1) { // Chế độ 1: 1 từ vựng ra 4 định nghĩa
			QuestionGenerator q = chooseCorrectDefinition(SA[dicType], tst[dicType]);
			LuuTru.push_back(q);
		}
		else if (mode == 2) { // Chế độ 2: 1 định nghĩa và 4 từ vựng
			QuestionGenerator q = chooseCorrectWord(SA[dicType], tst[dicType]);
			LuuTru.push_back(q);
		}
		//Generate 1000 questions
		while (LuuTru.size() < 1000) {
			if (mode == 1) {
				QuestionGenerator q = chooseCorrectDefinition(SA[dicType], tst[dicType]);
				LuuTru.push_back(q);
			}
			else if (mode == 2) {
				QuestionGenerator q = chooseCorrectWord(SA[dicType], tst[dicType]);
				LuuTru.push_back(q);
			}
		}
	}
	else if (dicType == 3) { // Slang
		if (mode == 1) { // Chế độ 1: 1 từ vựng ra 4 định nghĩa
			QuestionGenerator q = chooseCorrectDefinition(SA[dicType], tst[dicType]);
			LuuTru.push_back(q);
		}
		else if (mode == 2) { // Chế độ 2: 1 định nghĩa và 4 từ vựng
			QuestionGenerator q = chooseCorrectWord(SA[dicType], tst[dicType]);
			LuuTru.push_back(q);
		}
		// Generate 1000 questions
		while (LuuTru.size() < 1000) {
			if (mode == 1) {
				QuestionGenerator q = chooseCorrectDefinition(SA[dicType], tst[dicType]);
				LuuTru.push_back(q);
			}
			else if (mode == 2) {
				QuestionGenerator q = chooseCorrectWord(SA[dicType], tst[dicType]);
				LuuTru.push_back(q);
			}
		}
	}
	else if (dicType == 4) { // Emoji
		if (mode == 1) { // Chế độ 1: 1 emoji ra 4 nghĩa
			QuestionGenerator q = chooseCorrectDefinition(SA[dicType], tst[dicType]);
			LuuTru.push_back(q);
		}
		else if (mode == 2) { // Chế độ 2: 1 nghĩa và 4 emoji
			QuestionGenerator q = chooseCorrectWord(SA[dicType], tst[dicType]);
			LuuTru.push_back(q);
		}
		// Generate 1000 questions
		while (LuuTru.size() < 1000) {
			if (mode == 1) {
				QuestionGenerator q = chooseCorrectDefinition(SA[dicType], tst[dicType]);
				LuuTru.push_back(q);
			}
			else if (mode == 2) {
				QuestionGenerator q = chooseCorrectWord(SA[dicType], tst[dicType]);
				LuuTru.push_back(q);
			}
		}
	}

	//Cập nhật câu hỏi và đáp án
	if (!LuuTru.empty()) {
		word = LuuTru[0].question;
		DapAn = LuuTru[0].answers;
		correctAnswerIndex = LuuTru[0].correctAnswerIndex;
	}
}

void gameDialog::NextQuestion()
{
	//Remove the current question
	if (!LuuTru.empty()) {
		LuuTru.erase(LuuTru.begin());
		//Load the next question
		if (!LuuTru.empty()) {
			LoadQuestion();
			w->SetLabel(word);
			for (int i = 0; i < 4; ++i) {
				buttons[i]->SetLabel(wxString::Format("%c. %s", 'A' + i, DapAn[i]));
				buttons[i]->SetBackgroundColour(wxColour(0, 128, 0)); // Reset button background color
			}
		}
		else {
			EndGame(); // If no more questions, end the game
		}
	}
}

void gameDialog::EndGame()
{
	gameEnded = true;

	//Show the game result
	wxMessageDialog* dlg = new wxMessageDialog(this,
		wxString::Format("Game Over! Your score is %d.", score),
		"Game Over",
		wxOK | wxICON_INFORMATION);

	if (dlg->ShowModal() == wxID_OK) {
		Close(true); // Close the game window when the user clicks OK
	}
	delete dlg;
}

void gameDialog::SetUpButtons()
{
	wxString labels[4] = { "A.", "B.", "C.", "D." };
	for (int i = 0; i < 4; ++i) {
		buttons[i] = new wxButton(this, 10001 + i, labels[i] + " " + wxString::FromUTF8(DapAn[i].c_str()), wxDefaultPosition, wxSize(200, 50),wxTE_MULTILINE);
	}
}
