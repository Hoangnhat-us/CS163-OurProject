#pragma once
#include "gameDia1.h"
#include "gameDia2.h"
#include <wx/dialog.h>
#include <wx/simplebook.h>
#include <wx/wx.h>

class gameDialog : public wxDialog
{
public:
	CountdownTimer* timer;
	wxStaticText* point;
	wxStaticText* w;
	wxButton* buttons[4];
	TST* tst;
	SuffixArray* SA;
	int level = 0;
	int dicType = 0;
	int mode = 0;
	int score = 0; // Điểm số của người chơi
	bool gameEnded = false; // Trạng thái kết thúc game

	gameDialog(wxWindow* parent, const wxString& title);
	void OnButtonClicked(wxCommandEvent& event);

private:
	void LoadQuestion();
	void NextQuestion();
	void EndGame();
	std::vector<QuestionGenerator> LuuTru;
	std::string word;
	std::vector<std::string> DapAn;
	int correctAnswerIndex; // Lưu trữ chỉ số đáp án đúng
	void SetUpButtons();
};
