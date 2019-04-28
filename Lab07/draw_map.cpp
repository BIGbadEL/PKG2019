#include <wx/wx.h>
#include "GUIMyFrame1.h"
// UWAGA: TO JEST JEDYNY PLIK, KTORY NALEZY EDYTOWAC **************************

double wk(double x, double y, double xk, double yk) {
    return 1.0 / (( x - xk ) * ( x - xk ) + ( y - yk ) * ( y - yk ));
}

double sheppardZ(double x, double y, int N, float points[100][3]) {
    double licznik = 0.0;
    double mianowink = 0.0;

    for (int i = 0; i < N; i++) {
        if (x == points[i][0] && y == points[i][1]) {
            return points[i][2];
        }
        double temp = wk(x, y, points[i][0], points[i][1]);
        licznik += temp * points[i][2];
        mianowink += temp;
    }
    return licznik / mianowink;
}

void GUIMyFrame1::DrawMap(int N, float d[100][3], bool Contour, int MappingType, int NoLevels, bool ShowPoints) {
    wxMemoryDC memDC;
    memDC.SelectObject(MemoryBitmap);
    memDC.SetBackground(*wxWHITE_BRUSH);
    memDC.Clear();


    double diagram[500][500];
    double min = d[0][2];
    double max = d[0][2];

    for (int x = 0; x < 500; ++x) {
        for (int y = 0; y < 500; ++y) {
            diagram[x][y] = sheppardZ(x / 100.0 - 2.5, y / 100.0 - 2.5, N, d);
            if (min > diagram[x][y]) {
                min = diagram[x][y];
            } else if (max < diagram[x][y]) {
                max = diagram[x][y];
            }
        }
    }

    switch (MappingType) {
        case 0:
            break;
        case 1:
            for (int x = 0; x < 500; ++x) {
                for (int y = 0; y < 500; ++y) {
                    auto out = static_cast<unsigned char>(fabs(( diagram[x][y] - min ) * 255 / ( max - min )));
                    memDC.SetPen(wxColor(255 - out, 0, out));
                    memDC.DrawPoint(wxPoint(x, 500 - y));
                }
            }
            break;
        case 2:
            for (int x = 0; x < 500; ++x) {
                for (int y = 0; y < 500; ++y) {
                    int col = 2 * static_cast<int>(fabs(( diagram[x][y] - min ) * 255 / ( max - min )));
                    auto R = static_cast<unsigned char>(255 - col < 0 ? 0 : 255 - col);
                    auto B = static_cast<unsigned char>( col - 255 < 0 ? 0 : col - 255);
                    auto G = static_cast<unsigned char>(255 - abs(R - B));
                    memDC.SetPen(wxColor(R, G, B));
                    memDC.DrawPoint(wxPoint(x, 500 - y));
                }
            }
            break;
        case 3:
            for (int x = 0; x < 500; ++x) {
                for (int y = 0; y < 500; ++y) {
                    int col = static_cast<int>(fabs(( diagram[x][y] - min ) * 255 / ( max - min )));
                    memDC.SetPen(wxColor(col, col, col));
                    memDC.DrawPoint(wxPoint(x, 500 - y));
                }
            }
            break;
    }

    if (Contour) {
        double step = ( max - min ) / ( NoLevels  + 1);
        bool cont_map[500][500];
        int8_t ouput[250][250];
        for (int i = 1; i <= NoLevels; ++i) {
            double cont_val = min + i * step;
            for (int x = 0; x < 500; ++x) {
                for (int y = 0; y < 500; ++y) {
                    cont_map[x][y] = diagram[x][y] > cont_val;
                }
            }

            memDC.SetPen(wxColor(0, 0, 0));
            for (int x = 0; x < 500 - 2; x += 1) {
                for (int y = 0; y < 500 - 2; y += 1) {
                    if (cont_map[x][y] == false &&
                        cont_map[x + 1][y] == false &&
                        cont_map[x][y + 1] == false &&
                        cont_map[x + 1][y + 1] == false) {
//                        ouput[x / 2][y / 2] = 15;
                    } else if (cont_map[x][y] == true &&
                               cont_map[x + 1][y] == true &&
                               cont_map[x][y + 1] == true &&
                               cont_map[x + 1][y + 1] == true) {
//                        ouput[x / 2][y / 2] = 0;
                    } else if (cont_map[x][y] == false &&
                               cont_map[x + 1][y] == false &&
                               cont_map[x][y + 1] == false &&
                               cont_map[x + 1][y + 1] == true) {
                        memDC.DrawPoint(wxPoint(x + 1, 500 - y - 1));
                    } else if (cont_map[x][y] == false &&
                               cont_map[x + 1][y] == false &&
                               cont_map[x][y + 1] == true &&
                               cont_map[x + 1][y + 1] == true) {
//                        memDC.DrawPoint(wxPoint(x + 1, y + 1));
//                        memDC.DrawPoint(wxPoint(x + 1, y));
                        memDC.DrawLine(wxPoint(x + 1, 500 - y - 1), wxPoint(x + 1, 500 - y));
                    } else if (cont_map[x][y] == false &&
                               cont_map[x + 1][y] == true &&
                               cont_map[x][y + 1] == false &&
                               cont_map[x + 1][y + 1] == false) {
                        memDC.DrawPoint(wxPoint(x + 1, 500 - y));
                    } else if (cont_map[x][y] == false &&
                               cont_map[x + 1][y] == true &&
                               cont_map[x][y + 1] == true &&
                               cont_map[x + 1][y + 1] == false) {
                        memDC.DrawLine(wxPoint(x, 500 - y - 1), wxPoint(x + 1, 500 - y));
                    } else if (cont_map[x][y] == false &&
                               cont_map[x + 1][y] == true &&
                               cont_map[x][y + 1] == false &&
                               cont_map[x + 1][y + 1] == true) {
                        memDC.DrawLine(wxPoint(x + 1, 500 - y), wxPoint(x + 1, 500 - y - 1));
                    } else if (cont_map[x][y] == false &&
                               cont_map[x + 1][y] == true &&
                               cont_map[x][y + 1] == true &&
                               cont_map[x + 1][y + 1] == true) {
                        memDC.DrawLine(wxPoint(x, 500 - y - 1), wxPoint(x + 1, 500 - y));
                    } else if (cont_map[x][y] == true &&
                               cont_map[x + 1][y] == false &&
                               cont_map[x][y + 1] == false &&
                               cont_map[x + 1][y + 1] == false) {
                        memDC.DrawPoint(x, 500 - y);
                    } else if (cont_map[x][y] == true &&
                               cont_map[x + 1][y] == false &&
                               cont_map[x][y + 1] == true &&
                               cont_map[x + 1][y + 1] == false) {
                        memDC.DrawLine(wxPoint(x, 500 - y), wxPoint(x, 500 - y - 1));
                    } else if (cont_map[x][y] == true &&
                               cont_map[x + 1][y] == false &&
                               cont_map[x][y + 1] == false &&
                               cont_map[x + 1][y + 1] == true) {
                        memDC.DrawLine(wxPoint(x, 500 - y), wxPoint(x + 1, 500 - y - 1));
                    } else if (cont_map[x][y] == true &&
                               cont_map[x + 1][y] == true &&
                               cont_map[x][y + 1] == false &&
                               cont_map[x + 1][y + 1] == false) {
                        memDC.DrawLine(wxPoint(x, 500 - y), wxPoint(x + 1, 500 - y - 1));
                    } else if (cont_map[x][y] == true &&
                               cont_map[x + 1][y] == true &&
                               cont_map[x][y + 1] == false &&
                               cont_map[x + 1][y + 1] == false) {
                        memDC.DrawLine(wxPoint(x, 500 - y), wxPoint(x + 1, 500 - y));
                    } else if (cont_map[x][y] == true &&
                               cont_map[x + 1][y] == true &&
                               cont_map[x][y + 1] == true &&
                               cont_map[x + 1][y + 1] == false) {
                        memDC.DrawLine(wxPoint(x, 500 - y - 1), wxPoint(x + 1, 500 - y));
                    } else if (cont_map[x][y] == true &&
                               cont_map[x + 1][y] == true &&
                               cont_map[x][y + 1] == true &&
                               cont_map[x + 1][y + 1] == false) {
                        memDC.DrawLine(wxPoint(x, 500 - y), wxPoint(x + 1, 500 - y - 1));
                    } else if (cont_map[x][y] == false &&
                               cont_map[x + 1][y] == false &&
                               cont_map[x][y + 1] == true &&
                               cont_map[x + 1][y + 1] == false) {
                        memDC.DrawPoint(x, 500 - y - 1);
                    }
                }
            }
        }

    }

    // demo.....
    memDC.SetPen(*wxBLACK_PEN);

    if (ShowPoints) {
        for (int i = 0; i < N; i++) {
            //memDC.DrawPoint(wxPoint(((d[i][0] + 2.5) * 100.0), ((d[i][1])+ 2.5) * 100.0));
            auto temp = wxPoint((( d[i][0] + 2.5 ) * 100.0 ), (( d[i][1] ) + 2.5 ) * 100.0);
            memDC.DrawLine(wxPoint(temp.x + 5, 500 - temp.y), wxPoint(temp.x - 5, 500 - temp.y));
            memDC.DrawLine(wxPoint(temp.x, 500 - temp.y + 5), wxPoint(temp.x, 500 - temp.y - 5));
        }
    }

}
