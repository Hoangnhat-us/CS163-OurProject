#include "gameDia1.h"
#include <wx/dcbuffer.h> 

gameDia1::gameDia1(wxWindow* parent) : wxPanel(parent, wxID_ANY)
{
	wxImage image;
	if (image.LoadFile(wxT("../../../../picture/gameBackground.png"), wxBITMAP_TYPE_PNG))
	{
		backgroundBitmap = wxBitmap(image);
	}

	// Bind the paint event to draw the background image
	Bind(wxEVT_PAINT, &gameDia1::OnPaint, this);

	// Use double-buffering to avoid flickering
	SetBackgroundStyle(wxBG_STYLE_PAINT);

	wxBitmap bm1(wxT("../../../../picture/wordMode.png"), wxBITMAP_TYPE_PNG);
	word = new wxBitmapButton(this, wxID_ANY, bm1, wxPoint(295, 68), wxDefaultSize);

	wxBitmap bm2(wxT("../../../../picture/defMode.png"), wxBITMAP_TYPE_PNG);
	def = new wxBitmapButton(this, wxID_ANY, bm2, wxPoint(295, 230), wxDefaultSize);

	Bind(wxEVT_PAINT, &gameDia1::OnPaint, this);

}


void gameDia1::OnPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(this);  // Double-buffered drawing

	// If the background bitmap is loaded, draw it
	if (backgroundBitmap.IsOk())
	{
		wxSize size = this->GetClientSize();
		dc.DrawBitmap(backgroundBitmap, 0, 0, true);  // Draw the image at position (0, 0)

		// You may need to scale or stretch the bitmap to fit the window
		// wxImage scaledImage = backgroundBitmap.ConvertToImage().Scale(size.GetWidth(), size.GetHeight());
		// dc.DrawBitmap(wxBitmap(scaledImage), 0, 0, true);
	}
}
