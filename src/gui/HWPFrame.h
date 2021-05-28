#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

class HWPFrame : public wxFrame {
public:
	HWPFrame();

protected:
	wxPanel* panel;
	wxButton* showButton;

private:
	void OnShow(wxCommandEvent& event);
};
