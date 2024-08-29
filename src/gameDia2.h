#pragma once
#include "timer.h"
#include <wx/wx.h>
#include "Random.h"
#include "SuffixArray.h"
#include "TernarySearchTree.h"

class gameDia2 : public wxPanel
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

    gameDia2(wxWindow* parent);
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
