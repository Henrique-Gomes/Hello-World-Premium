#include "HWPApp.h"
#include "HWPFrame.h"

bool HWPApp::OnInit() {
	HWPFrame* frame = new HWPFrame();
	frame->Show(true);
	return true;
}