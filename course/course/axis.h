#ifndef AXIS_H
#define AXIS_H
#include "point.h"
#include "myscene.h"


class Axis {
public:
    Axis():
    center(0,0,0),
      ox(900,0,0),
      oy(0,900,0),
      oz(0,0,900)
    {}

    void tostart() {
        center = point(0,0,0);
          ox = point(900,0,0);
          oy = point(0,900,0);
          oz = point(0,0,900);
    }

    void rotate(double ax, double ay, double az) {
       ox.rorateX(ax);
       ox.rorateY(ay);
       ox.rorateZ(az);
       oy.rorateX(ax);
       oy.rorateY(ay);
       oy.rorateZ(az);
       oz.rorateX(ax);
       oz.rorateY(ay);
       oz.rorateZ(az);
       ox.print();
       oy.print();
       oz.print();
    }

    void render(Scene &scene) {
        scene.setColor(Qt::red);
        scene.drawLine(center, ox);
        scene.setColor(Qt::green);
        scene.drawLine(center, oy);
        scene.setColor(Qt::blue);
        scene.drawLine(center, oz);
        ox.print();
        oy.print();
        oz.print();
    }

private:
    point center;
    point ox;
    point oy;
    point oz;

};


#endif // AXIS_H
