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
    double dx, dy,dz;

    Scene(): cam({0,0,900}){
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

    void drawTexture(point p, double r, QColor color = Qt::black) {
        painter->setPen(color);
        clear_flag = false;

        if (alphax) p.rorateX(alphax);
        if (alphay) p.rorateY(alphay);
        if (alphaz) p.rorateZ(alphaz);
        if (k != 1) {
            p.scaleUniform({0,0,0}, k);
            r *= k;
        }
        QPointF qp;
        qp.setX(XCENTER+p.x());
        qp.setY(YCENTER-p.y());
        QImage pixmap;
        if ( pixmap.load("i.png") )	{
            QBrush br(color,Qt::SolidPattern);
            painter->setBrush(br);
            painter->drawImage(qp,pixmap);
        }
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
        p = cam.ProjectVertex(p);
        QPointF qp;
        qp.setX(XCENTER+p.x());
        qp.setY(YCENTER-p.y());
        QBrush br(color,Qt::SolidPattern);
        painter->setBrush(br);
        painter->drawEllipse(qp,r,r);

    }

    void drawPoint(point p, QColor color = Qt::black) {
        painter->setPen(color);
        clear_flag = false;
        double z1 = 0;//sqrt(2)/2 * p.z();
        if (alphax) p.rorateX(alphax);
        if (alphay) p.rorateY(alphay);
        if (alphaz) p.rorateZ(alphaz);
        if (k != 1) p.scaleUniform({0,0,0}, k);
        p = cam.ProjectVertex(p);
        painter->drawPoint(XCENTER+p.x() - z1, YCENTER-p.y() + z1);
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

        double z1 = 0;//sqrt(2)/2 * p1.z();
        double z2 = 0;//sqrt(2)/2 * p2.z();
        p1 = cam.ProjectVertex(p1);
        p2 = cam.ProjectVertex(p2);
        painter->drawLine(XCENTER + p1.x() - z1, YCENTER - p1.y() + z1,
                             XCENTER+p2.x() - z2, YCENTER - p2.y() + z2);
    }

    void setColor(QColor color){
        painter->setPen(color);
    }
};

#endif // MESCENE_H
