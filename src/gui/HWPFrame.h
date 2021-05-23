#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

class HWPFrame : public wxFrame {
public:
	HWPFrame();

protected: // should be private maybe?
	wxPanel* panel;
	wxButton* showButton;

private:
	void OnShow(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

enum {
	ID_showButton = wxID_HIGHEST + 1
};