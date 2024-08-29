#pragma once

#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
#include <windows.h>         // Then include windows.h
#include <winsock2.h>        // Include winsock2.h first
#include <ws2tcpip.h>        // Additional networking headers if needed

#include"Random.h"
#include "SuffixArray.h"
#include "TernarySearchTree.h"
#include "timer.h"

class gameDialog : public wxDialog
{
public:
	CountdownTimer* timer;
	wxStaticText* point;
	wxStaticText* w;
	wxButton* buttons[4];
	std::vector<TST> tst;
	std::vector<SuffixArray> SA;
	int level = 0;
	int dicType = 0;
	int mode = 0;
	int score = 0; // Điểm số của người chơi
	bool gameEnded = false; // Trạng thái kết thúc game

	gameDialog(wxWindow* parent, const wxString& title, std::vector<TST> &tst,	std::vector<SuffixArray> &SA);
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
