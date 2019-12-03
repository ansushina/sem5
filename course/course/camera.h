#ifndef CAMERA_H
#define CAMERA_H
#include <point.h>
#include "vector3.h"

typedef point CamPoint;
typedef point ScreenPoint;
typedef point CloudPoint;


class camera
{
public:
    
    camera():
        center({0,0,-YCENTER}),
        d(YCENTER),
        pov(90),
        Vh(CH),
        Vw(CH),
        up(0,YCENTER,0),
        straight(0,0,d),
        right(XCENTER,0,0)
    {

    }
    
    camera(point c):
      center(c),
      d(YCENTER),
      pov(90),
      Vh(CH),
      Vw(CH) // По стандарту пусть задается угол обзора по y = 90, по иксу тоже 90.
    {}

    CamPoint pointToCam(CloudPoint p) {
        return point(p.x()/XCENTER, p.y()/YCENTER, (p.z()+d)/d);
    }

    ScreenPoint CamToScreenStandart(CamPoint p){
        if (p.z() == 0) return p;
        ScreenPoint p1;
        p1.setX(XCENTER + XCENTER * p.x()/p.z());
        p1.setY(YCENTER - YCENTER * p.y()/p.z());
        p1.setZ(p.z());
        return p1;
    }
    
    point pointToCameraView(point p) {
        if (p.z() == 0) return p;
        return point(p.x()*d/p.z(), p.y()*d/p.z(), 0);
    }

    point ViewportToCanvas(point p) {
        return point(p.x()*CW/Vw, p.y()*CH/Vh, 0);
    }

    ScreenPoint ProjectVertex(point p, double &r) {
        /*point p1 =CamToScreenStandart(p) ;
        point p2 =pointToCam(CamToScreenStandart(p));
        printf("normal   %lf %lf %lf\n", p.x(), p.y(), p.z());
        printf("tocamera %lf %lf %lf\n", p1.x(), p1.y(), p1.z());
        printf("tocanvas %lf %lf %lf\n", p2.x(), p2.y(), p2.z());*/
        if (p.z()) r *= d/(p.z()+d);
        return  CamToScreenStandart(pointToCam(p));
    }

    bool inCameraView(point p) {
        if (p.z() < -d) {
            //printf("pz %lf \n", p.z());
            return false;
        }
        return true;
    }

    bool isInCameraView(point p) {
        if (p.z() < d) return false;
        if (p.y() < -Vh/2 || p.y() > Vh/2) return false;
        if (p.x() < -Vw/2 || p.x() > Vw/2) return false;
        return true;
    }

private:
    point center;
    int d;
    int pov; 
    int Vh, Vw;
    vec3 up, straight, right;
};

#endif // CAMERA_H
