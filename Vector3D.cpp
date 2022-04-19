// Vector3D.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<cmath>
#include "Vector3D.h"

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

void Vector3D::x(double x) {
    this->X = x;
}
void Vector3D::y(double y) {
    this->Y = y;
}
void Vector3D::z(double z) {
    this->Z = z;
}

void Vector3D::operator += (const Vector3D& other) {
    *this = Vector3D(this->x() + other.x(), this->y() + other.y(), this->z() + other.z());
}
void Vector3D::operator -= (const Vector3D& other) {
    *this = Vector3D(this->x() - other.x(), this->y() - other.y(), this->z() - other.z());
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
double Vector3D::operator * (const Vector3D& other) const {
    return (this->x() * other.x() + this->y() * other.y() + this->z() * other.z());
}
Vector3D operator * (const Vector3D& v, double a) {
    return Vector3D(v.x() * a, v.y() * a, v.z() * a);
}
Vector3D Vector3D::cross_prod(const Vector3D& other) const {
    return Vector3D(this->y() * other.z() - this->x() * other.y(), this->z() * other.x() - this->x() * other.z(), this->x() * other.y() - this->y() * other.x());
}

Segment3D::Segment3D() : start(Vector3D(0, 0, 0)), end(Vector3D(0, 0, 0)) {}
Segment3D::Segment3D(Vector3D START, Vector3D END) : start(START), end(END) {}

Vector3D Segment3D::toVector3D() const {
    return (this->end - this->start);
}
double Segment3D::x() const {
    return (this->end - this->start).x();
}
double Segment3D::y() const {
    return (this->end - this->start).y();
}
double Segment3D::z() const {
    return (this->end - this->start).z();
}
double Segment3D::norm() const {
    return (this->end - this->start).norm();
}
double Segment3D::dist(const Segment3D& other) const {
    Vector3D e = this->toVector3D().cross_prod(other.toVector3D()) * (1 / this->norm() / other.norm());
    return abs((other.end - this->end) * e);
}
Vector3D Segment3D::Intersect(const Segment3D& other) const {
    if (this->dist(other) > 0.) return Vector3D();
    else {
        double alpha = (other.start - this->start) * (this->toVector3D() * other.norm() * other.norm() - other.toVector3D() * (this->toVector3D() * other.toVector3D()));
        alpha *= (1 / (this->norm() * this->norm() * other.norm() * other.norm() - (this->toVector3D() * other.toVector3D()) * (this->toVector3D() * other.toVector3D())));
        return this->start * (1. - alpha) + this->end * alpha;
    }
}

 
int main()
{
    double x1, y1, z1, x2, y2, z2;

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
