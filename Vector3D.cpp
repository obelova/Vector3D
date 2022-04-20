// Vector3D.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<cmath>
#include "Vector3D.h"

constexpr double eps = std::numeric_limits<double>::epsilon();

using namespace std;

Vector3D::Vector3D() : X(0), Y(0), Z(0) {}
Vector3D::Vector3D(double x, double y, double z) : X(x), Y(y), Z(z) {}

double Vector3D::x() const {
    return X;
}
double Vector3D::y() const {
    return Y;
}
double Vector3D::z() const {
    return Z;
}

void Vector3D::operator *= (double a) {
    *this = Vector3D(x() * a, y() * a, z() * a);
}

Vector3D Vector3D::operator + (const Vector3D& other) const {
    return Vector3D(x() + other.x(), y() + other.y(), z() + other.z());
}
Vector3D Vector3D::operator - (const Vector3D& other) const {
    return Vector3D(x() - other.x(), y() - other.y(), z() - other.z());
}
Vector3D operator * (const Vector3D& v, double a) {
    return Vector3D(a * v.x(), a * v.y(), a * v.z());
}
ostream& operator << (std::ostream& s, const Vector3D& v) {
    s << "(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
    return s;
}

Segment3D::Segment3D() : START(Vector3D()), END(Vector3D()) {}
Segment3D::Segment3D(Vector3D start, Vector3D end) : START(start), END(end) {}

Vector3D Segment3D::toVector3D() const {
    return (END - START);
}
double Segment3D::x() const {
    return toVector3D().x();
}
double Segment3D::y() const {
    return toVector3D().y();
}
double Segment3D::z() const {
    return toVector3D().z();
}
ostream& operator << (std::ostream& s, const Segment3D& seg) {
    s << seg.START << " -> " << seg.END;
    return s;
}

int max_col(double* matr[], int col) { //  функция ищет номер ряда, в котором находится максимальный по модулю элемент под диагональю
    double max = abs(matr[col][col]);
    int m = col;
    for (int i = col + 1; i < 3; i++) {
        double temp = abs(matr[i][col]);
        if (temp > max) {
            max = temp;
            m = i;
        }
    }
    return m;
}
void swap_rows(double* matr[], int r1, int r2) { // меняет ряды r1 и r2 местами
    for (int i = 0; i < 3; i++)
        swap(matr[r1][i], matr[r2][i]);
}
void triangularize(double* matr[]) {
    double c, temp;

    int n = max_col(matr, 0); // поиск ведущего ряда для нулевого столбца
    swap_rows(matr, 0, n); // меняем первую и ведущую строку
    if (abs(matr[0][0]) > eps) // проверяем элемент [0][0], еси нулевой -> переходим к столбцу 1
        for (int i = 1; i < 3; i++) {
            temp = matr[i][0];
            if (abs(temp) < eps) continue; // если элемент  нулевого столбца в данном ряду 0, переходим к следующей строке
            c = matr[0][0] / temp; // коэф. пропорциональности
            for (int j = 0; j < 3; j++) // отнимаем от рядов 1 и 2 строку 0 с учетом коэф.
                matr[i][j] -= c * matr[i][j];
        }

    n = max_col(matr, 1); //аналогично для 1 столбца
    swap_rows(matr, 1, n);
    if (abs(matr[1][1]) > eps) { // проверяем элемент [1][1], если нулевой, то приведение окончено
        temp = matr[2][1];
        if (abs(temp) > eps) { // если элемент [2][1] нулевой, приведение окончено
            c = matr[1][1] / temp;
            for (int i = 0; i < 3; i++)
                matr[2][i] -= c * matr[2][i]; // отнимаем от ряда 2 ряд 1 с учетом коэф.
        }
    }
}
Vector3D Intersect(const Segment3D& v1, const Segment3D& v2) {
   double* matr[3];

   //заполнение матрицы { v1, -v2 | s2-s1 }
   matr[0][0] = v1.x(); matr[0][1] = -v2.x(); matr[0][2] = v2.START.x() - v1.START.x();
   matr[1][0] = v1.y(); matr[1][1] = -v2.y(); matr[1][2] = v2.START.y() - v1.START.y();
   matr[2][0] = v1.z(); matr[2][1] = -v2.z(); matr[2][2] = v2.START.z() - v1.START.z();

   triangularize(matr);

    if (abs(matr[2][2]) > eps) return Vector3D();
    if (abs(matr[1][1]) < eps || matr[0][0] < eps) return Vector3D();
    double b = matr[1][2] / matr[1][1];
    if (b < 0. || b > 1.) return Vector3D();
    return v2.START + v2.toVector3D() * b;
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
