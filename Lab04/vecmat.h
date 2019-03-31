//Extremely simple vector and matrix classes by Janusz Malinowski. 
#include <cstdio>

class Vector {
public:
    double data[3];

    Vector();

    Vector(double x, double y);

    void Print();

    void Set(double d1, double d2);

    double GetX();

    double GetY();
};

class Matrix {
public:
    double data[3][3];

    Matrix();

    void Print();

    Matrix operator*(const Matrix&);

    void Inverse() {
        double determinant = 0;
        for (int i = 0; i < 3; i++)
            determinant = determinant + ( data[0][i] * ( data[1][( i + 1 ) % 3] * data[2][( i + 2 ) % 3] -
                                                         data[1][( i + 2 ) % 3] * data[2][( i + 1 ) % 3] ));

        double temp[3][3];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                temp[i][j] = data[i][j];
            }
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
                data[i][j] = (( temp[( j + 1 ) % 3][( i + 1 ) % 3] * temp[( j + 2 ) % 3][( i + 2 ) % 3] ) -
                              ( temp[( j + 1 ) % 3][( i + 2 ) % 3] * temp[( j + 2 ) % 3][( i + 1 ) % 3] )) /
                             determinant;


        }
    }

    friend Vector operator*(const Matrix&, const Vector&);
};

Vector::Vector() {
    data[0] = 0.0;
    data[1] = 0.0;
    data[2] = 1.0;
}

Vector::Vector(double x, double y) {
    data[0] = x;
    data[1] = y;
    data[2] = 1.0;
}

void Vector::Print() {
    printf("(%2.3lf,%2.3lf,%2.3lf)\n", data[0], data[1], data[2]);
}

void Vector::Set(double d1, double d2) {
    data[0] = d1;
    data[1] = d2;
}

double Vector::GetX() {
    return data[0];
}

double Vector::GetY() {
    return data[1];
}

Matrix::Matrix() {
    data[0][0] = 0.0;
    data[0][1] = 0.0;
    data[0][2] = 0.0;
    data[1][0] = 0.0;
    data[1][1] = 0.0;
    data[1][2] = 0.0;
    data[2][0] = 0.0;
    data[2][1] = 0.0;
    data[2][2] = 1.0;
}

void Matrix::Print() {
    printf("\n|%2.3lf,%2.3lf,%2.3lf|\n", data[0][0], data[0][1], data[0][2]);
    printf("|%2.3lf,%2.3lf,%2.3lf|\n", data[1][0], data[1][1], data[1][2]);
    printf("|%2.3lf,%2.3lf,%2.3lf|\n", data[2][0], data[2][1], data[2][2]);
}

Matrix Matrix::operator*(const Matrix& gMatrix) {
    int i, j, k;
    Matrix tmp;

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++) {
            tmp.data[i][j] = 0.0;
            for (k = 0; k < 3; k++)
                tmp.data[i][j] = tmp.data[i][j] + ( data[i][k] * gMatrix.data[k][j] );
        }
    return tmp;
}

Vector operator*(const Matrix& gMatrix, const Vector& gVector) {
    unsigned int i, j;
    Vector tmp;

    for (i = 0; i < 3; i++) {
        tmp.data[i] = 0.0;
        for (j = 0; j < 3; j++) tmp.data[i] = tmp.data[i] + ( gMatrix.data[i][j] * gVector.data[j] );
    }
    return tmp;
}