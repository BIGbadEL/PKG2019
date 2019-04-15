#include <iostream>
#include "GUIMyFrame1.h"
#include <wx/rawbmp.h>
#include <wx/image.h>

#define KIND_OF_SMALL_NUMBER 2

GUIMyFrame1::GUIMyFrame1(wxWindow* parent)
        :
        MyFrame1(parent) {
    m_staticText1->SetLabel(( L"Jasno\u015B\u0107" ));
    m_b_threshold->SetLabel(( L"Pr\u00F3g 128" ));
    this->SetBackgroundColour(wxColor(192, 192, 192));
    m_scrolledWindow->SetScrollbars(25, 25, 52, 40);
    m_scrolledWindow->SetBackgroundColour(wxColor(192, 192, 192));
}

void GUIMyFrame1::m_scrolledWindow_update(wxUpdateUIEvent& event) {
    Repaint();
}

void GUIMyFrame1::m_b_grayscale_click(wxCommandEvent& event) {
    Img_Cpy = Img_Org.ConvertToGreyscale();
    // TO DO: Konwersja do skali szarosci
}

void GUIMyFrame1::m_b_blur_click(wxCommandEvent& event) {
    Img_Cpy = Img_Org.Blur(5);
    // TO DO: Rozmywanie obrazu (blur)
}

void GUIMyFrame1::m_b_mirror_click(wxCommandEvent& event) {
    Img_Cpy = isMirror ? Img_Org : Img_Org.Mirror(true);
    isMirror = !isMirror;
    // TO DO: Odbicie lustrzane
}

void GUIMyFrame1::m_b_replace_click(wxCommandEvent& event) {
    Img_Cpy = Img_Org;
    Img_Cpy.Replace(254, 0, 0, 0, 0, 255);
    // TO DO: Zamiana kolorow
}

void GUIMyFrame1::m_b_rescale_click(wxCommandEvent& event) {
    Img_Cpy = Img_Org.Copy();
    Img_Cpy.Rescale(320, 240);
    wxClientDC dc(m_scrolledWindow);
    m_scrolledWindow->DoPrepareDC(dc);
    dc.Clear();
    wasRescale = true;
    // TO DO: Zmiana rozmiarow do 320x240
}

void GUIMyFrame1::m_b_rotate_click(wxCommandEvent& event) {
    int w, h;
    Img_Cpy = Img_Org.Copy();
    wxSize temp = Img_Org.GetSize();
    w = temp.GetX();
    h = temp.GetY();
    Img_Cpy = Img_Cpy.Rotate(M_PI / 6, wxPoint(w / 2, h / 2));
    wasRotation = true;
    // TO DO: Obrot o 30 stopni
}

void GUIMyFrame1::m_b_rotate_hue_click(wxCommandEvent& event) {
    Img_Cpy = Img_Org.Copy();
    Img_Cpy.RotateHue(180.0 / 360.0);
    // TO DO: Przesuniecie Hue o 180 stopni
}

void GUIMyFrame1::m_b_mask_click(wxCommandEvent& event) {
    Img_Cpy = Img_Org.Copy();
    Img_Cpy.SetMaskFromImage(Img_Mask, 0, 0, 0);
    Img_Cpy.RotateHue(1); //obrót o 360 stopni xDD
    ClearBackground();
    // TO DO: Ustawienie maski obrazu
}

void GUIMyFrame1::m_s_brightness_scroll(wxScrollEvent& event) {
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Brightness(...), ktora zmienia jasnosc. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Brightness(...)
    Brightness(m_s_brightness->GetValue() - 100);
    Repaint();
}

void GUIMyFrame1::m_s_contrast_scroll(wxScrollEvent& event) {
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Contrast(...), ktora zmienia kontrast. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Contrast(...)
    Contrast(m_s_contrast->GetValue() - 100);
    Repaint();
}

constexpr double weight[3][3] = {
    { -1, 0, 1},
    { -1, 0, 1},
    { -1, 0, 1}
};

void GUIMyFrame1::m_b_prewitt_click(wxCommandEvent& event) {
    int size = Img_Org.GetHeight() * Img_Org.GetWidth() * 3;
    unsigned char* data = Img_Org.GetData();
    unsigned char* new_data = Img_Cpy.GetData();
    int width = Img_Org.GetWidth();
    data += width + 1;
    new_data += width + 1;
    for(int i = 0; i < size - (width - 1) * 3; i++){
        if( i % width != 0 && i % width != width - 1) {
            int index1 = ( -width - 1) * 3;
            int index2 = index1 + 3;
            int index3 = index2 + 3;
            int index5 = 0;
            int index4 = index5 - 3;
            int index6 = index5 + 3;
            int index7 = ( width - 1) * 3;
            int index8 = index7 + 3;
            int index9 = index8 + 3;
            double s = weight[0][0] * data[index1] + weight[0][1] * data[index2] + weight[0][2] * data[index3]
                       + weight[1][0] * data[index4] + weight[1][1] * data[index5] + weight[1][2] * data[index6]
                       + weight[2][0] * data[index7] + weight[2][1] * data[index8] + weight[2][2] * data[index9];
            s = sqrt(s * s + s * s) / 3;
            new_data[0] = static_cast<unsigned char> (s > 255 ? 255 : s);
        } else {
            new_data[0] = 0;
        }
        new_data += 1;
        data += 1;
    }


    // TO DO: Pionowa maska Prewitta
}

void GUIMyFrame1::m_b_threshold_click(wxCommandEvent& event) {
    int size = Img_Org.GetHeight() * Img_Org.GetWidth();
    unsigned char* data = Img_Org.GetData();
    unsigned char* new_data = Img_Cpy.GetData();
    for(int i = 0; i < size; i++){
        new_data[0] = data[0] < 128 ? 0 : 255;
        new_data[1] = data[1] < 128 ? 0 : 255;
        new_data[2] = data[2] < 128 ? 0 : 255;
        new_data += 3;
        data += 3;
    }
    // TO DO: Prog o wartosci 128 dla kazdego kanalu niezaleznie
}


void GUIMyFrame1::Contrast(int value) {
    if(wasRescale || wasRotation){
        wasRescale = false;
        wasRotation = false;
        auto ev = wxCommandEvent{};
        m_b_blur_click(ev);
    }
    static int prev_contrast = value;
    double factor = (value + 100.0 ) / 10;
    if (abs(prev_contrast - value) > KIND_OF_SMALL_NUMBER) {
        int size = Img_Org.GetHeight() * Img_Org.GetWidth();
        unsigned char* data = Img_Org.GetData();
        unsigned char* new_data = Img_Cpy.GetData();
        for(int i = 0; i < size; i++){
            double r = (data[0] - 127) * factor + 127;
            new_data[0] = static_cast<unsigned char> (r < 0 ? 0 : (r > 255 ? 255 : r));
            r = (data[1] - 127) * factor + 127;
            new_data[1] = static_cast<unsigned char> (r < 0 ? 0 : (r > 255 ? 255 : r));
            r = (data[2] - 127) * factor + 127;
            new_data[2] = static_cast<unsigned char> (r < 0 ? 0 : (r > 255 ? 255 : r));
            new_data += 3;
            data += 3;
        }
        prev_contrast = value;
    }
    // TO DO: Zmiana kontrastu obrazu. value moze przyjmowac wartosci od -100 do 100
}

void GUIMyFrame1::Repaint() {
    wxBitmap bitmap(Img_Cpy);          // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
    wxClientDC dc(m_scrolledWindow);   // Pobieramy kontekst okna
    m_scrolledWindow->DoPrepareDC(dc); // Musimy wywolac w przypadku wxScrolledWindow, zeby suwaki prawidlowo dzialaly
    dc.DrawBitmap(bitmap, 0, 0, true); // Rysujemy bitmape na kontekscie urzadzenia
}


void GUIMyFrame1::Brightness(int value) {
    if(wasRescale || wasRotation){
        wasRescale = false;
        wasRotation = false;
        auto ev = wxCommandEvent{};
        m_b_blur_click(ev);
    }
    static int prev_val = value;
//    Img_Cpy = Img_Org.Copy();
    if (KIND_OF_SMALL_NUMBER < std::abs(prev_val - value)) {
        wxColor fadeto = wxColor(255, 255, 255);

        auto fade_factor = value; //static_cast<unsigned int>(( value + 100 ) / 200. * 255);

        int fade_r = fadeto.Red() * fade_factor;
        int fade_g = fadeto.Green() * fade_factor;
        int fade_b = fadeto.Blue() * fade_factor;
        int fade_complement = 255 - abs(fade_factor);

        unsigned int pixelcount = Img_Org.GetHeight() * Img_Org.GetWidth();
        unsigned char* data = Img_Org.GetData();
        unsigned char* data_out = Img_Cpy.GetData();
        if (value > 0) {
            for (unsigned int i = 0; i < pixelcount; i++) {
                data_out[0] = static_cast<int>( data[0] * fade_complement + fade_r ) >> 8;
                data_out[1] = static_cast<int>( data[1] * fade_complement + fade_g ) >> 8;
                data_out[2] = static_cast<int>( data[2] * fade_complement + fade_b ) >> 8;
                data += 3;
                data_out += 3;
            }
        } else {
            for (unsigned int i = 0; i < pixelcount; i++) {
                data_out[0] = data[0] + value < 0 ? 0 : abs(data[0] + value);
                data_out[1] = data[1] + value < 0 ? 0 : abs(data[1] + value);
                data_out[2] = data[2] + value < 0 ? 0 : abs(data[2] + value);
//                std::cout << (( data[0] * fade_complement + fade_r ) >> 8) << " x " <<  (( data[1] * fade_complement + fade_r ) >> 8) << " x " <<  (( data[2] * fade_complement + fade_r ) >> 8) << "\n";
                data += 3;
                data_out += 3;
            }
        }
        prev_val = value;
    }
}


