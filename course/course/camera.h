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

    ScreenPoint ProjectVertex(point p, double &r) {
        if (p.z() && (p.z()+d)) r *= d/(p.z()+d);
        return  CamToScreenStandart(pointToCam(p));
    }

    bool inCameraView(point p) {
        if (p.z() < -d) {
            //printf("pz %lf \n", p.z());
            return false;
        }
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
