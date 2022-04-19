class Vector3D {
public:
    double X;
    double Y;
    double Z;

    Vector3D();
    Vector3D(double, double, double);

    double x() const;
    double y() const;
    double z() const;
    double norm() const;

    void x(double a);
    void y(double a);
    void z(double a);

    void operator+=(const Vector3D& other);
    void operator-=(const Vector3D& other);
    void operator*=(double a);

    Vector3D operator+(const Vector3D& other) const;
    Vector3D operator-(const Vector3D& other) const;
    double operator*(const Vector3D& other) const;
    friend Vector3D operator*(const Vector3D& v, double a);
    Vector3D cross_prod(const Vector3D& other) const;

};

class Segment3D {
public:
    Vector3D start;
    Vector3D end;

    Segment3D();
    Segment3D(Vector3D, Vector3D);

    Vector3D toVector3D() const;
    double x() const;
    double y() const;
    double z() const;
    double norm() const;

    double dist(const Segment3D& other) const;
    Vector3D Intersect(const Segment3D& other) const;
    
};