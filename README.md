# Vector3D
Есть класс трехмерного вектора: 
class Vector3D {
    double X;
    double Y;
    double Z;
    ...
}
и трехмерного отрезка:
class Segment3D {
    Vector3D start;
    Vector3D end;
    ...
}
Функция Intersect получает на вход два отрезка Segment3D и возвращает вектор Vector3D их пересечения.
