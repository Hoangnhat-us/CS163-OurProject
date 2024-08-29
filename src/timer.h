#pragma once
#include <wx/wx.h>

class CountdownTimer : public wxPanel
{
public:
	CountdownTimer(wxWindow* parent, int startSeconds);

	~CountdownTimer();

private:
	wxStaticText* countdownDisplay;
	wxTimer* timer;
	int countdownTime;

	void OnTimer(wxTimerEvent& event);

	void UpdateDisplay();
};
