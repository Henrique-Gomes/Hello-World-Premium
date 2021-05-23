#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "HWPFrame.h"

class HWPApp : public wxApp {
public:
	virtual bool OnInit();
};

// This adds the 'main' to the program
wxIMPLEMENT_APP(HWPApp);

bool HWPApp::OnInit() {

	HWPFrame* frame = new HWPFrame();
	frame->Show(true);

	// wxMessageBox("Hello, world!", "Hello World Premium", wxOK | wxCENTRE);
	return true;
}