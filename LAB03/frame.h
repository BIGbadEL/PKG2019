//
// Created by grzegorz on 19.03.19.
//

#pragma once

#include <wx-3.0/wx/wx.h>
#include <wx-3.0/wx/dcbuffer.h>
#include <wx-3.0/wx/dcgraph.h>
#include <wx-3.0/wx/colordlg.h>
#include <unistd.h>
#include <future>

enum operations {
    ID_SAVE_FILE,
    ID_COLOR_CHANGE
};

class Frame : public wxFrame {
public:
    Frame() :
            wxFrame(nullptr, wxID_ANY, "PGK_LAB03", wxDefaultPosition, wxSize(800, 600)) {

        _size = wxSize(800, 600);

        this->SetBackgroundColour(wxColour(*wxLIGHT_GREY));
        _menu_panel = new wxPanel(this, wxID_ANY, wxPoint(500, 0), wxSize(300, 600), wxTAB_TRAVERSAL);
        _menu_panel->SetBackgroundColour(wxColour(*wxLIGHT_GREY));

        _saveToFileButton = new wxButton(_menu_panel, ID_SAVE_FILE, wxT("Zapis do pliku"), wxPoint(100, 10),
                                         wxSize(100, 30));


        _bananaCheckBox = new wxCheckBox(_menu_panel, wxID_ANY, "banan", wxPoint(115, 60));

        _slider = new wxScrollBar(_menu_panel, wxID_ANY, wxPoint(30, 100), wxSize(250, 20));
        _slider->SetScrollbar(0, 1, 100, 1);
        _slider->Disable();

        _handPos = new wxGauge(_menu_panel, wxID_ANY, 99, wxPoint(38, 130), wxSize(230, 20));
        _ChoseStarColor = new wxButton(_menu_panel, ID_COLOR_CHANGE, wxT("kolor gwiazdy"), wxPoint(95, 170));
        _text = new wxTextCtrl(_menu_panel, wxID_ANY, wxString("Tekst"), wxPoint(98, 230));
        _typeOfObject = new wxComboBox(_menu_panel, wxID_ANY, "gwiazda", wxPoint(85, 300));
        _typeOfObject->Append("gwiazda");
        _typeOfObject->Append("ksiezyc");
        _typeOfObject->Append("slocne");


        _draw_panel = new wxPanel(this, wxID_ANY, wxPoint(10, 10), wxSize(500, 545));
        _draw_panel->SetBackgroundColour(wxColour(*wxWHITE));

        Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
            wxFileDialog choseFile(nullptr, "Save", "", "", "PNG files (*.png)|*.png", wxFD_SAVE);
            if (choseFile.ShowModal() == wxID_CANCEL) return;
            wxImage image = _toImage.ConvertToImage();
            image.AddHandler(new wxPNGHandler);
            image.SaveFile(choseFile.GetPath());
        }, ID_SAVE_FILE);


        Bind(wxEVT_SCROLL_THUMBTRACK, [&](wxCommandEvent&) {
            _handPos->SetValue(_slider->GetThumbPosition());
            Draw();
        });

        Bind(wxEVT_CHECKBOX, [&](wxCommandEvent&) {
            _slider->Enable(_bananaCheckBox->IsChecked());
            Draw();
        });

        Bind(wxEVT_TEXT, [&](wxCommandEvent&) {
            _actualText = _text->GetValue();
            Draw();
        });

        Bind(wxEVT_COMBOBOX, [&](wxCommandEvent&) {
            std::cout << _typeOfObject->GetValue() << '\n';
            if ("gwiazda" == _typeOfObject->GetValue()) {
                _actualShape = 0;
            } else if ("ksiezyc" == _typeOfObject->GetValue()) {
                _actualShape = 1;
            } else {
                _actualShape = 2;
            }

            Draw();
        });

        Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
            wxColourDialog dialog(this, nullptr);
            if (dialog.ShowModal() == wxID_CANCEL) return;
            _starColor = dialog.GetColourData().GetColour();
            Draw();
        }, ID_COLOR_CHANGE);

        Bind(wxEVT_UPDATE_UI, [&](wxCommandEvent&) {
            Draw();
        });


        wxImage temp_banan = wxImage();
        wxPNGHandler temp{};
        temp_banan.AddHandler(&temp);
        temp_banan.LoadFile("banan.png", wxBITMAP_TYPE_PNG);
        _banana = wxBitmap(temp_banan);

    }

    ~Frame(){
        delete _saveToFileButton;
        delete _bananaCheckBox;
        delete _slider;
        delete _handPos;
        delete _ChoseStarColor;
        delete _text;
        delete _typeOfObject;
        delete _draw_panel;
        delete _menu_panel;
    }

private:

    void Draw() {


        _size.x = this->GetSize().x;
        _size.y = this->GetSize().y;

        _menu_panel->SetPosition(wxPoint(_size.x - 300 > 500 ? _size.x - 300 : 500, 0));
        _draw_panel->SetSize(_size.x - 300 > 500 ? _size.x - 300 : 500,
                             this->GetSize().y < 600 ? 540 : this->GetSize().y - 60);
        wxClientDC drawHandler(_draw_panel);
        drawHandler.SetDeviceOrigin(_draw_panel->GetSize().x / 2 - drawHandler.GetSize().x / 2 , _draw_panel->GetSize().y / 2 - drawHandler.GetSize().y / 2);


        _toImage = wxBitmap(_draw_panel->GetSize().x, _draw_panel->GetSize().y);
        wxBufferedDC bufferToDrewIn(&drawHandler, _toImage);
        wxGCDC MyDC(bufferToDrewIn);


        wxSize size = _draw_panel->GetSize();
        int x = ( size.x - 377 ) / 2;
        int y = ( size.y - 346 ) / 2;

        MyDC.SetBackground(*wxWHITE_BRUSH);
        MyDC.Clear();

        if (_bananaCheckBox->IsChecked()) {
            MyDC.DrawBitmap(_banana, x + 149 - _banana.GetWidth() / 2,
                            static_cast<wxCoord>(y + 192 - 0.38f * _handPos->GetValue() - _banana.GetHeight() / 2));
        }

        MyDC.DrawCircle(x + 188, y + 143, 20);
        MyDC.DrawEllipse(x + 176, y + 135, 10, 7);

        if (_bananaCheckBox->IsChecked()) {
            MyDC.DrawEllipticArc(x + 174, y + 148, 26, 5, 180, 360);
            MyDC.DrawEllipse(x + 191, y + 135, 10, 7);
        } else {
            MyDC.DrawEllipticArc(x + 174, y + 148, 26, 5, 0, 180);
            MyDC.DrawEllipse(x + 191, y + 133, 7, 10);
        }

        MyDC.DrawLine(x + 188, y + 164, x + 188, y + 234);
        MyDC.DrawLine(x + 188, y + 234, x + 159, y + 262);
        MyDC.DrawLine(x + 188, y + 234, x + 217, y + 262);
        MyDC.DrawLine(x + 188, y + 173, x + 227, y + 192);
        MyDC.DrawLine(x + 188, y + 173, x + 149, static_cast<wxCoord>(y + 192 - 0.38f * _handPos->GetValue()));

        wxString text1(_actualText);
        MyDC.SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Calibri"));
        MyDC.DrawText(text1, x + 98, y + 253);
        wxString text2(_actualText);
        MyDC.SetFont(
                wxFont(30, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD, false, "Lato"));
        MyDC.DrawRotatedText(_actualText, x + 239, y + 263, 90);

        switch (_actualShape) {
            case 0: {
                MyDC.SetBrush(wxBrush(_starColor));
                MyDC.SetPen(wxPen(_starColor));
                wxPoint starPoints[5] = {
                        wxPoint(128, 83),
                        wxPoint(153, 128),
                        wxPoint(98, 103),
                        wxPoint(158, 103),
                        wxPoint(108, 128)
                };

                MyDC.DrawPolygon(5, starPoints, x, y);

                break;
            }
            case 1:
                MyDC.SetBrush(wxBrush(*wxLIGHT_GREY));
                MyDC.SetPen(wxPen(*wxLIGHT_GREY));
                MyDC.DrawCircle(x + 100, y + 100, 30);

                MyDC.SetBrush(wxBrush(*wxWHITE));
                MyDC.SetPen(wxPen(*wxWHITE));
                MyDC.DrawCircle(x + 80, y + 80, 30);

                MyDC.SetBrush(wxBrush(*wxBLACK));
                MyDC.SetPen(wxPen(*wxBLACK));
                MyDC.DrawCircle(x + 110, y + 95, 5);

                MyDC.DrawLine(x + 100, y + 105, x + 110, y + 110);
                break;
            case 2:
                MyDC.SetBrush(wxBrush(*wxYELLOW));
                MyDC.SetPen(wxPen(*wxYELLOW));
                MyDC.DrawCircle(x + 100, y + 100, 30);
                break;
            default:break;
        }

    }

private:
    wxButton* _saveToFileButton;
    wxCheckBox* _bananaCheckBox;
    wxScrollBar* _slider;
    wxGauge* _handPos;
    wxButton* _ChoseStarColor;
    wxTextCtrl* _text;
    wxComboBox* _typeOfObject;
    wxBitmap _banana;
    wxPanel* _draw_panel;
    wxPanel* _menu_panel;
    wxBitmap _toImage;
    int _actualShape = 0;
    wxString _actualText{"Tekst"};
    wxColour _starColor = wxColour(*wxBLACK);
    wxSize _size;
};


//LAB03_FRAME_H
