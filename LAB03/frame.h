//
// Created by grzegorz on 19.03.19.
//

#pragma once

#include <wx-3.0/wx/wx.h>

class Frame : public wxFrame {
public:
    Frame() :
            wxFrame(nullptr, wxID_ANY, "PGK_LAB03", wxDefaultPosition, wxSize(800, 600)) {
        wxPanel* menu_panel = new wxPanel(this, wxID_ANY, wxPoint(500, 0));
        menu_panel->SetBackgroundColour(wxColour(*wxLIGHT_GREY));

        _saveToFileButton = new wxButton(menu_panel, wxID_ANY, wxT("Zapis do pliku"), wxPoint(610, 20));


        _bananaCheckBox = new wxCheckBox(menu_panel, wxID_ANY, "banan", wxPoint(630, 50));

        _slider = new wxScrollBar(menu_panel, wxID_ANY, wxPoint(550, 100), wxSize(200, 50));
        _slider->SetScrollbar(0, 1, 100, 1);
        _slider->Disable();

        _handPos = new wxGauge(menu_panel, wxID_ANY, 100, wxPoint(550, 150), wxSize(200, 20));
        _starColor = new wxButton(menu_panel, wxID_ANY, wxT("kolor gwiazdy"), wxPoint(610, 200));
        _text = new wxTextCtrl(menu_panel, wxID_ANY, wxString("Tekst"), wxPoint(600, 250), wxSize(100, 20));
        _typeOfObject = new wxComboBox(menu_panel, wxID_ANY, "gwiazda", wxPoint(600, 400));
        _typeOfObject->Append("gwiazda");
        _typeOfObject->Append("ksiezyc");
        _typeOfObject->Append("slocne");



        wxPanel* draw_panel = new wxPanel(menu_panel, wxID_ANY, wxPoint(10, 10), wxSize(500, 545));

        wxClientDC draw_place = wxClientDC(draw_panel);
        draw_place.SetBackgroundMode(1);

        Centre();

        Bind(wxEVT_SCROLL_THUMBTRACK, [&](wxCommandEvent&){
                _handPos->SetValue(_slider->GetThumbPosition());
        });

        Bind(wxEVT_CHECKBOX, [&](wxCommandEvent&){
                _slider->Enable(_bananaCheckBox->IsChecked());
        });


    }

private:


private:
    wxButton* _saveToFileButton;
    wxCheckBox* _bananaCheckBox;
    wxScrollBar* _slider;
    wxGauge* _handPos;
    wxButton* _starColor;
    wxTextCtrl* _text;
    wxComboBox* _typeOfObject;
};


//LAB03_FRAME_H
