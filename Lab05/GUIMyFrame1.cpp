#include "GUIMyFrame1.h"
#include <vector>
#include <fstream>
#include "vecmat.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


struct Color {
 int R, G, B;
 Color(int _R, int _G, int _B) : R(_R), G(_G), B(_B) {}
};

struct Segment {
 Point begin, end;
 Color color;
 Segment(Point _begin, Point _end, Color _color) : begin(_begin), end(_end), color(_color) {}
};

std::vector<Segment> data;

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_button_load_geometry->SetLabel(_("Wczytaj Geometri\u0119"));
 m_staticText25->SetLabel(_("Obr\u00F3t X:"));
 m_staticText27->SetLabel(_("Obr\u00F3t Y:"));
 m_staticText29->SetLabel(_("Obr\u00F3t Z:"));

 WxSB_TranslationX->SetRange(0, 200); WxSB_TranslationX->SetValue(100);
 WxSB_TranslationY->SetRange(0, 200); WxSB_TranslationY->SetValue(100);
 WxSB_TranslationZ->SetRange(0, 200); WxSB_TranslationZ->SetValue(100);

 WxSB_RotateX->SetRange(0, 360); WxSB_RotateX->SetValue(0);
 WxSB_RotateY->SetRange(0, 360); WxSB_RotateY->SetValue(0);
 WxSB_RotateZ->SetRange(0, 360); WxSB_RotateZ->SetValue(0);

 WxSB_ScaleX->SetRange(1, 200); WxSB_ScaleX->SetValue(100);
 WxSB_ScaleY->SetRange(1, 200); WxSB_ScaleY->SetValue(100);
 WxSB_ScaleZ->SetRange(1, 200); WxSB_ScaleZ->SetValue(100);
}

void GUIMyFrame1::WxPanel_Repaint( wxUpdateUIEvent& event )
{
 Repaint();
}

void GUIMyFrame1::m_button_load_geometry_click( wxCommandEvent& event )
{
 wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Geometry file (*.geo)|*.geo"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

 if (WxOpenFileDialog.ShowModal() == wxID_OK)
 {
  double x1, y1, z1, x2, y2, z2;
  int r, g, b;

  std::ifstream in(WxOpenFileDialog.GetPath().ToAscii());
  if (in.is_open())
  {
   data.clear();
   while (!in.eof())
   {
    in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> r >> g >> b;
    data.emplace_back(Segment(Point(x1, y1, z1), Point(x2, y2, z2), Color(r, g, b)));
   }
   in.close();
  }
 }
}

void GUIMyFrame1::Scrolls_Updated( wxScrollEvent& event )
{
WxST_TranslationX->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationX->GetValue() - 100) / 50.0));
WxST_TranslationY->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationY->GetValue() - 100) / 50.0));
WxST_TranslationZ->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationZ->GetValue() - 100) / 50.0));

WxST_RotateX->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateX->GetValue()));
WxST_RotateY->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateY->GetValue()));
WxST_RotateZ->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateZ->GetValue()));

WxST_ScaleX->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleX->GetValue() / 100.0));
WxST_ScaleY->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleY->GetValue() / 100.0));
WxST_ScaleZ->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleZ->GetValue() / 100.0));


Repaint();
}

double toRadian(double z){
    return z * M_PI / 180.0;
}

Matrix4 makeIdentity(){
    Matrix4 result;
    result.data[0][0] = 1.0;
    result.data[1][1] = 1.0;
    result.data[2][2] = 1.0;
    return  result;
}

Matrix4 makeTranslation(double x, double y, double z){
    Matrix4 result = makeIdentity();
    result.data[0][3] = x;
    result.data[1][3] = y;
    result.data[2][3] = z;
    return result;
}

Matrix4 makeRotation(double xRot, double yRot, double zRot){
    Matrix4 X = makeIdentity();
    X.data[1][1] = std::cos(toRadian(xRot));
    X.data[2][2] = std::cos(toRadian(xRot));
    X.data[1][2] = - std::sin(toRadian(xRot));
    X.data[2][1] = std::sin(toRadian(xRot));

    Matrix4 Y = makeIdentity();
    Y.data[0][0] = std::cos(toRadian(yRot));
    Y.data[0][2] = - std::sin(toRadian(yRot));
    Y.data[2][0] = std::sin(toRadian(yRot));
    Y.data[2][2] = std::cos(toRadian(yRot));

    Matrix4 Z = makeIdentity();
    Z.data[0][0] = std::cos(toRadian(zRot));
    Z.data[0][1] = - std::sin(toRadian(zRot));
    Z.data[1][0] = std::sin(toRadian(zRot));
    Z.data[1][1] = std::cos(toRadian(zRot));

    return X * Y * Z;
}

Matrix4 makeScale(double Sx, double Sy, double Sz){
    Matrix4 result = makeIdentity();
    result.data[0][0] = Sx;
    result.data[1][1] = Sy;
    result.data[2][2] = Sz;
    return result;
}

Matrix4 makePerspective(double near, double far, double left, double right, double top, double bottom){
    Matrix4 result = makeIdentity();
    result.data[0][0] = (2 * near) / (right - left);
    result.data[0][2] = (right + left) / (right - left);
    result.data[1][1] = (2 * near) / (top - bottom);
    result.data[1][2] = (top + bottom) / (top - bottom);
    result.data[2][2] = -(far + near) / (far - near);
    result.data[2][3] = (-2 * far * near) / (far - near);
    result.data[3][2] = -1.0;
    return  result;
}

Matrix4 makePer(){
    Matrix4 result = makeIdentity();
    result.data[0][3] = 0.5;
    result.data[1][3] = 0.5;
    return result;
}

Matrix4 myMove(){
    Matrix4 result = makeIdentity();
    result.data[0][3] = - 0.005;
    result.data[1][3] = -0.0025;
    result.data[2][3] = 2;
    return result;
}

void update(Vector4& vec) {
    vec.data[0] /= vec.data[2];
    vec.data[1] /= vec.data[2];
}

void GUIMyFrame1::Repaint()
{
    Matrix4 matrix = myMove() * makeTranslation((WxSB_TranslationX->GetValue() - 100.0) / 50.0, -((WxSB_TranslationY->GetValue() - 100.0) / 50.0), (WxSB_TranslationZ->GetValue() - 100.0) / 50.0)
                * makeRotation(WxSB_RotateX->GetValue(), WxSB_RotateY->GetValue(), WxSB_RotateZ->GetValue() + 180)
                * makeScale(WxSB_ScaleX->GetValue() / 100.0, WxSB_ScaleY->GetValue() / 100.0, WxSB_ScaleZ->GetValue() / 100.0);

    int width, height;
    WxPanel->GetSize(&width, &height);

    wxClientDC drawPlace(WxPanel);
    wxBufferedDC dc(&drawPlace);

    dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();

    for(auto el : data){
        dc.SetPen(wxColour(el.color.R, el.color.B, el.color.G));
        Vector4 begin(el.begin), end(el.end);
        begin = matrix * begin;
        end = matrix *  end;
        update(begin);
        update(end);
        begin = makePer() * begin;
        end = makePer() * end;
        if(begin.GetZ() > 0.025 && end.GetZ() > 0.025)
            dc.DrawLine(begin.GetX() * width, begin.GetY() * height, end.GetX() * width, end.GetY() * height);
    }

// tu rysowac
}