#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <common/Common.h>

#include <cctype>

class HWPApp : public wxApp {
public:
	virtual bool OnInit();
};

// This add the 'main' to the program
wxIMPLEMENT_APP(HWPApp);

bool HWPApp::OnInit() {

	std::string hello = Common::hello;
	std::string world = Common::world;

	hello[0] = std::toupper(hello[0]);

	std::string helloWorld = hello;

	helloWorld += ", ";

	helloWorld += world;

	helloWorld += "!";

	wxMessageBox(helloWorld, "Hello World Premium", wxOK | wxCENTRE);
	return false;
}