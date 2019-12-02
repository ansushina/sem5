#ifndef POINT_H
#define POINT_H

#include"matrix.h"
#include<math.h>
#include<iostream>
#include"constants.h"

struct point
{
    point():X(0),Y(0),Z(0){}
    point(double x, double y): X(x), Y(y), Z(0){}
    point(double x, double y, double z):X(x),Y(y),Z(z){}
    point(double mas[3])  {
        X = mas[0];
        Y = mas[1];
        Z = mas[2];
    }
    point(const point &p)
    {
        this->X = p.x();
        this->Y = p.y();
        this->Z = p.z();
    }
    double X;
    double Y;
    double Z;

    void print(){
        printf("%lf, %lf, %lf;\n", X, Y, Z);
    }

    double x() const {return this->X;}
    double y() const {return this->Y;}
    double z() const {return this->Z;}
    void setY(double y){this->Y = y;}
    void setX(double x){this->X = x;}
    void setZ(double z){this->Z = z;}

    point& operator =(const point &p)
    {
        this->X = p.x();
        this->Y = p.y();
        this->Z = p.z();
        return *this;
    }

    void rorateX(double a) {
        if (a == 0)
            return;

        double alpha = a * PI / 180;
        Matrix m1(4,4), m2(1,4);
        m1.setMatrix({1, 0,          0, 0,
                      0, cos(alpha), -sin(alpha), 0,
                      0, sin(alpha), cos(alpha), 0,
                      0, 0,          0,          1});
        m2.setMatrix({this->x(), this->y(), this->z(), 1});

        Matrix res = m2.Mul(m1);
        //this->setX(res[0][0]);
        this->setY(res[0][1]);
        this->setZ(res[0][2]);
    }

    void rorateY(double a) {
        if (a == 0)
            return;

        double alpha = a * PI / 180;
        Matrix m1(4,4), m2(1,4);

        m1.setMatrix({cos(alpha),  0, sin(alpha), 0,
                      0,           1, 0,          0,
                      -sin(alpha), 0, cos(alpha), 0,
                      0,           0,  0,         1});

       m2.setMatrix({this->x(), this->y(), this->z(), 1});

        Matrix res = m2*m1;
        this->setX(res[0][0]);
        //this->setY(res[0][1]);
        this->setZ(res[0][2]);
    }

    void rorateZ(double a) {
        if (a == 0)
            return;

        double alpha = a * PI / 180;
        Matrix m1(4,4), m2(1,4);

        m1.setMatrix({cos(alpha), -sin(alpha), 0, 0,
                      sin(alpha), cos(alpha),  0, 0,
                      0,          0 ,          1, 0,
                      0,          0,           0, 1});

       m2.setMatrix({this->x(), this->y(), this->z(), 1});

        Matrix res = m2*m1;
        this->setX(res[0][0]);
        this->setY(res[0][1]);
        //this->setZ(res[0][2]);
    }

    void move(double dx, double dy, double dz) {
        if (dx == 0 && dy == 0 && dz == 0){
           return;
        }
        this->setX(this->X+dz);
        this->setY(this->Y+dy);
        this->setZ(this->Z+dz);
    }

    void scaleUniform(point c, double k) {
        double x = c.x() + k*(this->x()- c.x());
        double y = c.y() + k*(this->y() - c.y());
        double z = c.z() + k*(this->z() - c.z());
        setX(x);
        setY(y);
        setZ(z);
    }
};

#endif // POINT_H
