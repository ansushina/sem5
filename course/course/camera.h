#ifndef CAMERA_H
#define CAMERA_H
#include <point.h>


class camera
{
public:
    camera(point c):
      center(c),
      d(YCENTER),
      pov(90),
      Vh(CH),
      Vw(CH) // По стандарту пусть задается угол обзора по y = 90, по иксу тоже 90.
    {}

    camera(point c, int d, int pov):
      center(c),
      d(YCENTER),
      Vh(CH),
      Vw(CH)
    {}
    
    point pointToCameraView(point p) {
        return point(p.x()*d/p.z(), p.y()*d/p.z(), d);
    }

    point ViewportToCanvas(point p) {
        return point(p.x()*CW/Vw, p.y()*CH/Vh, d);
    }

    point ProjectVertex(point p) {
        return ViewportToCanvas(pointToCameraView(p));
    }

private:
    point center;
    int d;
    int pov; 
    int Vh, Vw;
};

#endif // CAMERA_H
