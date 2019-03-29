#include <wx/wx.h>
#include <memory>
#include "GUIMyFrame1.h"

class MyApp : public wxApp {

public:

    bool OnInit() override;

    int OnExit() override { return 0; }

};

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    wxFrame* mainFrame = new GUIMyFrame1(NULL);
    mainFrame->Show(true);
    SetTopWindow(mainFrame);

    return true;
}