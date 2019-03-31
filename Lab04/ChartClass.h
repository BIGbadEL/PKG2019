#ifndef __ChartClass__
#define __ChartClass__

#include <memory>
#include "ConfigClass.h"

class Matrix;

class ChartClass {
private:
    std::shared_ptr<ConfigClass> cfg;
    int x_step;         // liczba odcinkow z jakich bedzie sie skladal wykres
    double x_min, x_max; // zakres zmiennej x
    double y_min, y_max; // zakres wartosci przyjmowanych przez funkcje
    double GetFunctionValue(double x); // zwraca wartosci rysowanej funkcji
    Matrix* trans;
    GUIMyFrame1* MainWindow;

    // powyzej sugerowana funkcja transformujaca odcinki (jesli ktos ma
    // inny pomysl mozna ja usunac)

public:
    explicit ChartClass(std::shared_ptr<ConfigClass> c, GUIMyFrame1* win);

    ~ChartClass();

    void Set_Range();   // ustala wartosci zmiennych x_min,y_min,x_max,y_max
    double Get_Y_min(); // zwraca y_min
    double Get_Y_max(); // zwraca y_max
    void Draw(wxDC* dc, int w, int h);  // rysuje wykres
    void SetTransformationMat(double w, double h);
};

#endif
