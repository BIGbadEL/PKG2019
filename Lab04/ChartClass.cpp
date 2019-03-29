#include <wx/dc.h>
#include <memory>

#include "ChartClass.h"
#include "vecmat.h"

ChartClass::ChartClass(std::shared_ptr<ConfigClass> c) {
    x_min = 9999.9;
    x_max = -9999.9;
    y_min = 9999.9;
    y_max = -9999.9;
    cfg = std::move(c);
    x_step = 200;
    Set_Range();
    trans = new Matrix;
}

void ChartClass::Set_Range() {
    double ymin = 9999.9, ymax = -9999.9;
    double x, y, step;
    int i;

    double xmin = cfg->Get_x_start();
    double xmax = cfg->Get_x_stop();

    step = ( cfg->Get_x_stop() - cfg->Get_x_start()) / (double) x_step;
    x = cfg->Get_x_start();

    for (i = 0; i <= x_step; i++) {
        y = GetFunctionValue(x);
        if (y > ymax) ymax = y;
        if (y < ymin) ymin = y;
        x = x + step;
    }

    y_min = ymin;
    y_max = ymax;
    x_min = xmin;
    x_max = xmax;
}


double ChartClass::GetFunctionValue(double x) {
    if (cfg->Get_F_type() == 1) return x * x;
    if (cfg->Get_F_type() == 2) return 0.5 * exp(4 * x - 3 * x * x);
    return x + sin(x * 4.0);
}

void TranslatePoint(wxPoint& point, const Matrix& mat) {
    Vector vec(point.x, point.y);
    vec = mat * vec;
    point.x = static_cast<int>(vec.GetX());
    point.y = static_cast<int>(vec.GetY());
}

wxPoint TranslatePoint(double x, double y, const Matrix& mat) {
    Vector vec(x, y);
    vec = mat * vec;
    x = vec.GetX();
    y = vec.GetY();

    return wxPoint(static_cast<int>(x), static_cast<int>(y));
}

void ChartClass::Draw(wxDC* dc, int w, int h) {
    dc->SetBackground(*wxWHITE_BRUSH);
    dc->Clear();
    dc->SetPen(*wxRED_PEN);
    dc->DrawRectangle(10, 10, w - 20, h - 20);

    dc->SetPen(*wxBLUE_PEN);

    SetTransformationMat(w, h);

    dc->DrawText("Tu trzeba narysowac wykres", wxPoint(20, 20));

    auto warden = new wxDCClipper(*dc, 10, 10, w - 20, h - 20);

    //axis X
    wxPoint beginX = TranslatePoint(x_min, 0, *trans);
    wxPoint EndX = TranslatePoint(x_max, 0, *trans);
    dc->DrawLine(beginX, EndX);

    //arrowX

    wxPoint arrowB = TranslatePoint(x_max - 0.1, 0.1, *trans);
    dc->DrawLine(arrowB, EndX);
    arrowB = TranslatePoint(x_max - 0.1, -0.1, *trans);
    dc->DrawLine(arrowB, EndX);

    //axis Y
    wxPoint beginY(0, static_cast<int>(-y_max)), EndY(0, static_cast<int>(-y_min));
    TranslatePoint(beginY, *trans);
    TranslatePoint(EndY, *trans);
    dc->DrawLine(beginY, EndY);

    //arrowY
    arrowB = TranslatePoint(0.05, -y_max + 1.1, *trans);
    dc->DrawLine(arrowB, beginY);
    arrowB = TranslatePoint(-0.05, -y_max + 1.1, *trans);
    dc->DrawLine(arrowB, beginY);


    dc->SetPen(*wxGREEN_PEN);
    double step = std::abs(x_max - x_min) / x_step;
    double y = GetFunctionValue(x_min);
    wxPoint P1 = TranslatePoint(x_min, -y, *trans);
    for (double iter = x_min + step; iter <= x_max; iter += step) {
        wxPoint P2 = TranslatePoint(iter, -GetFunctionValue(iter), *trans);
        dc->DrawLine(P1, P2);
        P1 = P2;
    }


    delete warden;
}

void ChartClass::line2d(Matrix t, double* x1, double* y1, double* x2, double* y2) {

}

double ChartClass::Get_Y_min() {
    Set_Range();
    return y_min;
}

double ChartClass::Get_Y_max() {
    Set_Range();
    return y_max;
}

double toRadians(double angle) {
    return -M_PI * angle / 180.0;
}

void ChartClass::SetTransformationMat(double w, double h) {
    Matrix temp1; //macierz translacji

    temp1.data[0][2] = cfg->Get_dX();
    temp1.data[1][2] = cfg->Get_dY();

    Matrix temp4; //macierz translacji

    temp4.data[0][2] = w / 2.0;
    temp4.data[1][2] = h / 2.0;


    Matrix temp2; //macierz obrotu
    temp2.data[0][0] = std::cos(toRadians(cfg->Get_Alpha()));
    temp2.data[1][1] = temp2.data[0][0];
    temp2.data[0][1] = -std::sin(toRadians(cfg->Get_Alpha()));
    temp2.data[1][0] = -temp2.data[0][1];

    temp2 = temp4 * temp2;

    temp4.data[0][2] = -temp4.data[0][2];
    temp4.data[1][2] = -temp4.data[1][2];

    temp2 = temp2 * temp4;

    Matrix temp3; //macierz transformacji do wsp ekranu
    double Sx = w / ( cfg->Get_x1() - cfg->Get_x0());
    double Sy = h / ( cfg->Get_y1() - cfg->Get_y0());
    temp3.data[0][0] = Sx;
    temp3.data[1][1] = Sy;
    temp3.data[0][2] = 10 - Sx * cfg->Get_x0();
    temp3.data[1][2] = -10 - Sy * cfg->Get_y0();

    *trans = temp1 * temp2 * temp3;
}