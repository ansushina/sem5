#ifndef MESCENE_H
#define MESCENE_H
#include <QPainter>
#include <QColor>

#include "point.h"
#include "constants.h"
#include "camera.h"

typedef struct myscene myscene_t;


const QColor background(190,190,255);


class Scene {
private:
    QPainter *painter;
    QPixmap *scene;
    bool clear_flag;
    camera cam;

public:
    double alphax=0, alphay=0, alphaz=0;
    double k = 1;
    double dx = 0, dy = 0, dz = 0;

    Scene() {
        scene = new QPixmap(900, 900);
        scene->fill(background);

        painter = new QPainter(scene);
        painter->setPen(background);
        clear_flag = true;
    }
    ~Scene() {
        delete painter;
        delete scene;
    }
    void init() {
        alphax = 0;
        alphay = 0;
        alphaz = 0;
        k = 1;
        dx = 0;
        dy = 0;
        dz = 0;
    }

    void clear() {
        delete painter;
        delete scene;
        scene = new QPixmap(900,900);
        scene->fill(background);
        painter = new QPainter(scene);
        clear_flag = true;
    }

    QPixmap getPixmap() {
        return *(this->scene);
    }

    void drawCircle(point p, double r, QColor color = Qt::black) {
        painter->setPen(color);
        clear_flag = false;

        if (alphax) p.rorateX(alphax);
        if (alphay) p.rorateY(alphay);
        if (alphaz) p.rorateZ(alphaz);
        if (k != 1) {
            p.scaleUniform({0,0,0}, k);
            r *= k;
        }
        if (dx != 0 || dy != 0 || dz != 0) p.move(dx,dy,dz);
        if (cam.inCameraView(p) ) {
            p = cam.ProjectVertex(p,r);
            QPointF qp;
            qp.setX(p.x());
            qp.setY(p.y());
            QBrush br(color,Qt::SolidPattern);
            painter->setBrush(br);
            painter->drawEllipse(qp,r,r);
        }

    }

    void drawPoint(point p, QColor color = Qt::black) {
        painter->setPen(color);
        clear_flag = false;
        double r = 0;
        if (alphax) p.rorateX(alphax);
        if (alphay) p.rorateY(alphay);
        if (alphaz) p.rorateZ(alphaz);
        if (k != 1) p.scaleUniform({0,0,0}, k);
        if (cam.inCameraView(p) ) {
            p = cam.ProjectVertex(p,r);
            painter->drawPoint(p.x(), p.y());
        }
    }

    void drawLine(point p1, point p2) {
        clear_flag = false;
        if (alphax) {
            p1.rorateX(alphax);
            p2.rorateX(alphax);
        }
        if (alphay){
            p1.rorateY(alphay);
            p2.rorateY(alphay);
        }
        if (alphaz) {
            p1.rorateZ(alphaz);
            p2.rorateZ(alphaz);
        }
        double r = 0;
        p1 = cam.ProjectVertex(p1,r);
        p2 = cam.ProjectVertex(p2,r);
        painter->drawLine(p1.x(),p1.y(),p2.x(),p2.y());
    }

    void setColor(QColor color){
        painter->setPen(color);
    }
};

#endif // MESCENE_H
