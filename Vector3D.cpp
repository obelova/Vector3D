// Vector3D.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include<iostream>
#include<cmath>
#include<optional>
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
double Vector3D::norm() const {
    return sqrt(x() * x() + y() * y() + z() * z());
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
ostream& operator << (ostream& s, const Vector3D& v) {
    s << "(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
    return s;
}

double dot(const Vector3D v1, const Vector3D v2) {
    return (v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z());
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
double Segment3D::norm() const {
    return toVector3D().norm();
}

ostream& operator << (ostream& s, const Segment3D& seg) {
    s << seg.START << " -> " << seg.END;
    return s;
}

int max_col(double matr[3][3], int col) { //  функция ищет номер ряда, в котором находится максимальный по модулю элемент под диагональю
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
void swap_rows(double matr[3][3], int r1, int r2) { // меняет ряды r1 и r2 местами
    for (int i = 0; i < 3; i++)
        swap(matr[r1][i], matr[r2][i]);
}
void triangularize(double matr[3][3]) {
    double c;
    int n;

    for (int j = 0; j < 2; j++) { // достаточно очистить элементы столбцов 0 и 1, j -- номер столбца
        n = max_col(matr, j); // ищем строку с максимальным элементом под диагональю в столбце j
        if (n != j) 
            swap_rows(matr, j, n); // меняем ряды, если строка не номера j
        c = matr[j][j]; // запоминаем первый элемент ведущей строки
        if (abs(c) < eps) // если столбец пустой, переходим к следующему
            continue;
        for (int k = j; k < 3; k++) // нормируем строку j так, чтобы первый элемент был равен 1.
            matr[j][k] /= c;
        for (int i = j + 1; i < 3; i++) { // i -- номер строки, от которой отнимаем с соответсвующим коэф. ведущую строку
            c = matr[i][j]; // запоминаем элемент строки i столбца j
            for (int k = j; k < 3; k++) // отнимаем строку так, чтобы элемент [i][j] занулился
                matr[i][k] -= c * matr[j][k];
        }
    }
}

optional<Vector3D> Intersect(const Segment3D& v1, const Segment3D& v2) {
    if (v1.norm() < eps && v2.norm() < eps) { // проверка на совпадение вырожденных точек
        if ((v1.START - v2.START).norm() < eps)
            return v1.START;
        return {};
    }
   
    double matr[3][3];

   //заполнение матрицы { v1, -v2 | s2-s1 }
   matr[0][0] = v1.x(); matr[0][1] = -v2.x(); matr[0][2] = v2.START.x() - v1.START.x();
   matr[1][0] = v1.y(); matr[1][1] = -v2.y(); matr[1][2] = v2.START.y() - v1.START.y();
   matr[2][0] = v1.z(); matr[2][1] = -v2.z(); matr[2][2] = v2.START.z() - v1.START.z();

   triangularize(matr);

   double a, b;
   if (abs(matr[2][2]) > eps) // нижняя строка не пустая -- решений нет
       return {};
   if (abs(matr[1][1]) < eps) { 
       if (abs(matr[1][2]) > eps) // вторая строка 0 * b != 0 -- нет решений
           return {};
       // вторая строка пустая
       if (abs(matr[0][0]) < eps && abs(matr[0][1]) < eps) // нельзя найти ни а ни b
           return {};
       if (abs(matr[0][0]) < eps && abs(matr[0][1]) > eps) { // можно найти b, v1 -- точка
           b = matr[0][2] / matr[0][1];
           if (b < 0. || b > 1.) // проверка, что точка лежит в пределах v2
               return {};
           return v1.START;
       }
       else if (abs(matr[0][0]) > eps && abs(matr[0][1]) < eps) { // можно найти a, v2 -- точка
           a = matr[0][2] / matr[0][0];
           if (a < 0. || a > 1.) // проверка, что точка лежит в пределах v1
               return {};
           return v2.START;
       }
       double dot_prod = dot(v1.toVector3D(), v2.toVector3D()); // векторы коллинеарны, знак скалярных произведений указывает взаимное направление
       if (dot_prod > eps) // если векторы сонаправлены
           if ((v1.START - v2.END).norm() < eps) // либо начало первого вектора == конец второго
               return v1.START;
           else if ((v1.END - v2.START).norm() < eps) // либо начало второго вектора == начало первого
               return v1.END;
           else 
               return {}; // либо векторы наложены => нет единственного решения
       if ((v1.START - v2.START).norm() < eps) // случай с разнонаправленными векторами, либо сопадают начала
           return v1.START;
       else if ((v1.END - v2.END).norm() < eps) // либо концы
           return v1.END;
       return {}; // иначе наложение, т.е. нет единственного решения
   }
   b = matr[1][2] / matr[1][1];
   a = (matr[0][2] - matr[0][1] * b) / matr[0][0];
   if (b < 0. || b > 1. || a < 0. || a > 1.) 
       return {};
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

    optional<Vector3D> intersect = Intersect(v1, v2);
    if (intersect)
        cout << intersect.value();
    else 
        cout << "Unique solution does not exist";
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
