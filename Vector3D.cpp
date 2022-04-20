// Vector3D.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<cmath>
#include<vector>
#include "Vector3D.h"

#define eps 1.e-20

using namespace std;

Vector3D::Vector3D() : X(0), Y(0), Z(0) {}
Vector3D::Vector3D(double x, double y, double z) : X(x), Y(y), Z(z) {}

double Vector3D::x() const {
    return this->X;
}
double Vector3D::y() const {
    return this->Y;
}
double Vector3D::z() const {
    return this->Z;
}
double Vector3D::norm() const {
    return (sqrt(abs(this->x() * this->x() + this->y() * this->y() + this->z() * this->z())));
}
vector<double> Vector3D::vectorize() const {
    return {this->x(), this->y(), this->z()};
}

void Vector3D::operator *= (double a) {
    *this = Vector3D(this->x() * a, this->y() * a, this->z() * a);
}

Vector3D Vector3D::operator + (const Vector3D& other) const {
    return Vector3D(this->x() + other.x(), this->y() + other.y(), this->z() + other.z());
}
Vector3D Vector3D::operator - (const Vector3D& other) const {
    return Vector3D(this->x() - other.x(), this->y() - other.y(), this->z() - other.z());
}
Vector3D operator * (const Vector3D& v, double a) {
    return Vector3D(a * v.x(), a * v.y(), a * v.z());
}
std::ostream& operator << (std::ostream& s, const Vector3D& v) {
    s << "(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
    return s;
}

Segment3D::Segment3D() : START(Vector3D()), END(Vector3D()) {}
Segment3D::Segment3D(Vector3D start, Vector3D end) : START(start), END(end) {}

Vector3D Segment3D::toVector3D() const {
    return (this->END - this->START);
}
double Segment3D::x() const {
    return this->toVector3D().x();
}
double Segment3D::y() const {
    return this->toVector3D().y();
}
double Segment3D::z() const {
    return this->toVector3D().z();
}
double Segment3D::norm() const {
    return this->toVector3D().norm();
}

//void Segment3D::start(const Vector3D& s) {
//    *this = ;
//}

Vector3D Intersect(const Segment3D& v1, const Segment3D& v2) {
    vector<vector<double>> matr;
    for (int i = 0; i < 3; i++) {
        matr[i][0] = v1.toVector3D().vectorize()[i];
        matr[i][1] = -v2.toVector3D().vectorize()[i];
        matr[i][2] = v2.START.vectorize()[i] - v2.START.vectorize()[i];
    }
    triangulize(matr);
    if (abs(matr[2][2]) > eps) return;
    if (abs(matr[1][1]) < eps || matr[0][0] < eps) return;
    double b = matr[1][2] / matr[1][1];
    if (b < 0. || b > 1.) return;
    return v2.START + v2.toVector3D() * b;
}
int max_col(const vector<vector<double>>& matrix, int col) {
    double max = abs(matrix[col][col]);
    int max_pos = col;
    for (int i = col + 1; i < 3; i++) {
        double temp = abs(matrix[i][col]);
        if (temp > max) {
            max = temp;
            max_pos = i;
        }
    }
    return max_pos;
}
void triangulize(vector<vector<double>>& matr) {
    double c;
    for (int k = 0; k < 2; k++) {
        int m = max_col(matr, k);
        swap(matr[k], matr[m]);
        c = matr[k][k];
        if (abs(c) < eps) continue;
        for (int j = k + 1; j < 3; j++) {
            for (int i = k + 1; i < 3; i++)
                matr[j][i] -= matr[j][i] * (matr[j][k] / c);
        }
    }
}

std::ostream& operator << (std::ostream& s, const Segment3D& seg) {
    s << seg.START << " -> " << seg.END;
    return s;
}

 
int main()
{
    double x, y, z;
    Vector3D s, e;

    cout << "\n input v1 coord: ";
    cin >> x >> y >> z;
    s = Vector3D(x, y, z);
    cin >> x >> y >> z;
    e = Vector3D(x, y, z);
    Segment3D v1 = Segment3D(s, e);
    
    cout << "\n input v2 coord: ";
    cin >> x >> y >> z;
    s = Vector3D(x, y, z);
    cin >> x >> y >> z;
    e = Vector3D(x, y, z);
    Segment3D v2 = Segment3D(s, e);

    Vector3D intersection = Intersect(v1, v2);
    cout << intersection;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
