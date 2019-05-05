///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version May  1 2019)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 300,100 ), wxDefaultSize );

	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* panelSizer;
	panelSizer = new wxBoxSizer( wxVERTICAL );

	panelSizer->SetMinSize( wxSize( 200,-1 ) );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	wczytajObrazekButton = new wxButton( this, wxID_ANY, wxT("Wczytaj Obrazek"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( wczytajObrazekButton, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	cenzuraButton = new wxButton( this, wxID_ANY, wxT("Cenzura"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( cenzuraButton, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	erodeButton = new wxButton( this, wxID_ANY, wxT("Erode"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( erodeButton, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	animacjaCheck = new wxCheckBox( this, wxID_ANY, wxT("Animacja"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( animacjaCheck, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );


	panelSizer->Add( bSizer4, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );

	bSizer7->SetMinSize( wxSize( 100,100 ) );
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("test"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText1->Wrap( -1 );
	m_staticText1->SetMinSize( wxSize( 260,100 ) );

	bSizer7->Add( m_staticText1, 0, wxALL, 5 );


	panelSizer->Add( bSizer7, 1, wxEXPAND, 5 );


	mainSizer->Add( panelSizer, 0, wxEXPAND, 5 );

	m_panel3 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTAB_TRAVERSAL );
	m_panel3->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BACKGROUND ) );
	m_panel3->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );
	m_panel3->SetMinSize( wxSize( 800,533 ) );

	mainSizer->Add( m_panel3, 1, wxEXPAND, 5 );


	this->SetSizer( mainSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( MyFrame1::WindowSizeChanged ) );
	this->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MyFrame1::WindowUpdate ) );
	wczytajObrazekButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::WczytajObrazekClick ), NULL, this );
	cenzuraButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::CenzuraClick ), NULL, this );
	erodeButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::ErodeClick ), NULL, this );
	animacjaCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::AnimacjaCheck ), NULL, this );
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( MyFrame1::WindowSizeChanged ) );
	this->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MyFrame1::WindowUpdate ) );
	wczytajObrazekButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::WczytajObrazekClick ), NULL, this );
	cenzuraButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::CenzuraClick ), NULL, this );
	erodeButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::ErodeClick ), NULL, this );
	animacjaCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::AnimacjaCheck ), NULL, this );

}
