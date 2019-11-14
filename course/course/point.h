#ifndef POINT_H
#define POINT_H

struct point
{
    point():X(0),Y(0),Z(0){}
    point(double x, double y): X(x), Y(y), Z(0){}
    point(double x, double y, double z):X(x),Y(y),Z(z){}
    point(const point &p)
    {
        this->X = p.x();
        this->Y = p.y();
        this->Z = p.z();
    }
    double X;
    double Y;
    double Z;

    double x() const {return this->X;}
    double y() const {return this->Y;}
    double z() const {return this->Z;}
    void setY(double y){this->Y = y;}
    void setX(double x){this->X = x;}
    void setZ(double z){this->Z = z;}

    point_t& operator =(const point_t &p)
    {
        this->X = p.x();
        this->Y = p.y();
        this->Z = p.z();
        return *this;
    }
};

#endif // POINT_H
