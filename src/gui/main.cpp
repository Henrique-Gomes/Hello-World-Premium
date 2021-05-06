#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class HWPApp : public wxApp {
public:
	virtual bool OnInit();
};

// This add the 'main' to the program
wxIMPLEMENT_APP(HWPApp);

bool HWPApp::OnInit() {
	wxMessageBox("Hello, world!", "Hello World Premium", wxOK | wxCENTRE);
	return false;
}