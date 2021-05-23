#include "HWPFrame.h"

HWPFrame::HWPFrame() : wxFrame(NULL, wxID_ANY, "Hello World Premium") {

	panel = new wxPanel(this);

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	showButton = new wxButton(panel, ID_showButton, "Show");
	sizer->Add(showButton, 0, wxALIGN_CENTER, 0);

	panel->SetSizer(sizer);

	// Fit();
}

void HWPFrame::OnShow(wxCommandEvent& event) {
	wxMessageBox("Hello, world!", "Hello World Premium", wxOK | wxCENTRE);
}

wxBEGIN_EVENT_TABLE(HWPFrame, wxFrame)
	EVT_BUTTON(ID_showButton, HWPFrame::OnShow)
wxEND_EVENT_TABLE()