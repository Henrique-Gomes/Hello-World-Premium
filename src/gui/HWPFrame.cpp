#include "HWPFrame.h"

HWPFrame::HWPFrame() : wxFrame(NULL, wxID_ANY, "Hello World Premium") {

	panel = new wxPanel(this);

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	showButton = new wxButton(panel, wxID_ANY, "Show");
	showButton->Bind(wxEVT_BUTTON, &HWPFrame::OnShow, this);
	sizer->Add(showButton, 0, 0, 0);

	panel->SetSizerAndFit(sizer);
	Fit();
	
}

void HWPFrame::OnShow(wxCommandEvent& event) {
	wxMessageBox("Hello, world!", "Hello World Premium", wxOK | wxCENTRE);
}