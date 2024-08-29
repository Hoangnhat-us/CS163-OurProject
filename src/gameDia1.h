#pragma once
#include <wx/wx.h>

class gameDia1 : public wxPanel
{
public:
	gameDia1(wxWindow* parent);

	wxBitmapButton* word;
	wxBitmapButton* def;
	wxBitmap backgroundBitmap;

	void OnPaint(wxPaintEvent& event);
};
