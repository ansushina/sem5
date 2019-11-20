#ifndef CAMERA_H
#define CAMERA_H
#include <point.h>


class camera
{
public:
    camera();
    
    point pointToCameraView(point p) {
        return point(p.x()*d/p.z(), p.y()*d/p.z(), d);
    }

private:
    point center;
    int d;
    int pov; 
    int Vh, Vw;
};

#endif // CAMERA_H
