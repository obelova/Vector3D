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

    void operator*=(double a);

    Vector3D operator+(const Vector3D& other) const;
    Vector3D operator-(const Vector3D& other) const;
    friend Vector3D operator*(const Vector3D& v, double a);
    friend std::ostream& operator << (std::ostream&, const Vector3D&);
};

class Segment3D {
public:
    Vector3D START;
    Vector3D END;

    Segment3D();
    Segment3D(Vector3D, Vector3D);

    Vector3D toVector3D() const;
    double x() const;
    double y() const;
    double z() const;

    friend std::ostream& operator << (std::ostream&, const Segment3D&);
};