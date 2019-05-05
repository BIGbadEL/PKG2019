#include <iostream>
#include "CImg.h"
#include "GUIMyFrame1.h"
#include "FreeImage.h"

GUIMyFrame1::GUIMyFrame1(wxWindow* parent)
        :
        MyFrame1(parent) {
    image = wxImage(1, 1);
}

void GUIMyFrame1::WindowSizeChanged(wxSizeEvent& event) {
    window_width = event.GetSize().GetWidth();
    window_height = event.GetSize().GetHeight();
    Repaint();
}

void GUIMyFrame1::WindowUpdate(wxUpdateUIEvent& event) {
    Repaint();
}

void GUIMyFrame1::WczytajObrazekClick(wxCommandEvent& event) {
    wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("JPEG file (*.jpg)|*.jpg"),
                                  wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (WxOpenFileDialog.ShowModal() == wxID_OK) {
        if (!image.LoadFile(WxOpenFileDialog.GetPath())) {
            wxMessageBox(_("Nie udało si\u0119 za\u0142adowa\u0107 obrazka"));
        } else {
            image.LoadFile(WxOpenFileDialog.GetPath());
            path = WxOpenFileDialog.GetPath();
            Repaint();
            copy = image.Copy();
        }

        FreeImage_Initialise();
        FIBITMAP* dib = nullptr;
        dib = FreeImage_Load(FIF_JPEG, path);
        int h = FreeImage_GetHeight(dib);
        int w = FreeImage_GetWidth(dib);
        FITAG* tagMake = nullptr;
        FreeImage_GetMetadata(FIMD_EXIF_MAIN, dib, "Artist", &tagMake);
        std::string out = "Rozmiar obrazka: " + std::to_string(w) + "*" + std::to_string(h) + "\n";
        out += "Artist: " + std::string((char*) FreeImage_GetTagValue(tagMake)) + "\n";
        FreeImage_GetMetadata(FIMD_EXIF_MAIN, dib, "Copyright", &tagMake);
        out += "Copyright: " + std::string((char*) FreeImage_GetTagValue(tagMake)) + "\n";
        FreeImage_GetMetadata(FIMD_EXIF_MAIN, dib, "ResolutionUnit", &tagMake);
        out += "ResolutionUnit: " + std::string(FreeImage_TagToString(FIMD_EXIF_MAIN, tagMake)) + "\n";
        FreeImage_GetMetadata(FIMD_EXIF_MAIN, dib, "XResolution", &tagMake);
        out += "XResolution: " + std::string(FreeImage_TagToString(FIMD_EXIF_MAIN, tagMake)) + "\n";
        FreeImage_GetMetadata(FIMD_EXIF_MAIN, dib, "YCbCrPositioning", &tagMake);
        out += "YCbCrPositioning: " + std::string(FreeImage_TagToString(FIMD_EXIF_MAIN, tagMake)) + "\n";
        FreeImage_GetMetadata(FIMD_EXIF_MAIN, dib, "YResolution", &tagMake);
        out += "YResolution: " + std::string(FreeImage_TagToString(FIMD_EXIF_MAIN, tagMake)) + "\n";
        wxString Label(out);
        m_staticText1->SetLabel(Label);
    }
}

void GUIMyFrame1::CenzuraClick(wxCommandEvent& event) {
    anim = false;
    if (!image.Ok()) return;
    image = copy.Copy();
    wxClientDC dc(m_panel3);
    int beginW = static_cast<int>(image.GetWidth() / 1.75);
    int beginH = image.GetHeight() / 25;
    int width = static_cast<int>(image.GetWidth() / 1.40);
    int height = image.GetHeight() / 6;
    cimg_library::CImg<unsigned char> cImage(width, height, 1, 3);
    for (int i = beginW - 10; i < width; i++) {
        for (int j = beginH - 10; j < height; j++) {
            cImage(i, j, 0) = image.GetRed(i, j);
            cImage(i, j, 1) = image.GetGreen(i, j);
            cImage(i, j, 2) = image.GetBlue(i, j);
        }
    }
    cImage.blur(2.5);
    for (int i = beginW; i < width; i++) {
        for (int j = beginH; j < height; j++) {
            image.SetRGB(i, j, cImage(i, j, 0), cImage(i, j, 1), cImage(i, j, 2));
        }
    }
    Repaint();
}

void GUIMyFrame1::ErodeClick(wxCommandEvent& event) {
    anim = false;
    if (!image.Ok()) return;
    image = copy.Copy();
    wxClientDC dc(m_panel3);
    int width = static_cast<int>(image.GetWidth());
    int height = image.GetHeight();
    cimg_library::CImg<unsigned char> cImage(width, height, 1, 3);
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            cImage(i, j, 0) = image.GetRed(i, j);
            cImage(i, j, 1) = image.GetGreen(i, j);
            cImage(i, j, 2) = image.GetBlue(i, j);
        }
    }
    cImage.erode(5, 5);
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            image.SetRGB(i, j, cImage(i, j, 0), cImage(i, j, 1), cImage(i, j, 2));
        }
    }
    Repaint();
}

void GUIMyFrame1::AnimacjaCheck(wxCommandEvent& event) {
    anim = !anim;
    Repaint();
}


void GUIMyFrame1::Repaint() {
    // pobiera kontekst okna
    wxClientDC dc(m_panel3);
    // resize
    m_panel3->SetSize(window_width - 215, window_height - 45);
    wxImage image_temp = image.Scale(window_width - 215, window_height - 45);
    // tworzy tymczasowa bitmape na podstawie image_temp
    wxBitmap bitmap(image_temp);
    // rysuje

    if (anim) {
        static int step = 0;
        step += 5;
        step = step > 180 ? -180 : step;
        if (!image.Ok()) return;
        //image = copy.Copy();
        int width = image.GetWidth();
        int height = image.GetHeight();
        cimg_library::CImg<float> gauss(width, height, 1, 3);
        int x = 1;
        gauss.draw_gaussian(width / 2 + 300 * sin(step * M_PI / 180.0), height / 2 + 100 * cos(step * M_PI / 180.0),
                            100.0, &x);

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                image.SetRGB(i, j, copy.GetRed(i, j) * gauss(i, j), copy.GetGreen(i, j) * gauss(i, j),
                             copy.GetBlue(i, j) * gauss(i, j));
            }
        }
    }

    dc.DrawBitmap(bitmap, 0, 0, true);


}