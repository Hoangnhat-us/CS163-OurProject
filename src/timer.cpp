#include "timer.h"

CountdownTimer::CountdownTimer(wxWindow* parent, int startSeconds)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize),
	countdownTime(startSeconds)
{
	// Create a static text control to display the countdown time
	countdownDisplay = new wxStaticText(this, wxID_ANY, wxString::Format("%d", countdownTime), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);

	// Create a timer that triggers every second
	timer = new wxTimer(this);

	// Bind the timer event to the event handler
	Bind(wxEVT_TIMER, &CountdownTimer::OnTimer, this);

	// Start the timer with 1000ms (1 second) interval
	timer->Start(1000);
}

CountdownTimer::~CountdownTimer()
{
	// Stop the timer and clean up
	timer->Stop();
	delete timer;
}

void CountdownTimer::OnTimer(wxTimerEvent& event)
{
	// Decrement the countdown time
	countdownTime--;

	// Update the display with the current countdown time
	UpdateDisplay();

	// Stop the timer when the countdown reaches 0
	if (countdownTime <= 0)
	{
		timer->Stop();
		wxMessageBox("Time's up!", "Countdown Complete", wxOK | wxICON_INFORMATION);
	}
}

void CountdownTimer::UpdateDisplay()
{
	// Convert the countdown time to a string and display it
	countdownDisplay->SetLabel(wxString::Format("%d", countdownTime));
}