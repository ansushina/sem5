#ifndef MESCENE_H
#define MESCENE_H
#include <QPainter>
#include <QColor>

#include "point.h"

typedef struct myscene myscene_t;

#define XCENTER 450
#define YCENTER 450


class Scene {
private:
    QPainter *painter;
    QPixmap *scene;
    bool clear_flag;

public:
    Scene() {
        scene = new QPixmap(900, 900);
        scene->fill(QColor(Qt::black));

        painter = new QPainter(scene);
        painter->setPen(QPen(Qt::black));
        clear_flag = true;
    }
    ~Scene() {
        delete painter;
        delete scene;
    }

    void clear() {
        delete painter;
        delete scene;
        scene = new QPixmap(900,900);
        scene->fill(QColor(Qt::black));
        painter = new QPainter(scene);
        clear_flag = true;
    }

    QPixmap getPixmap() {
        return *(this->scene);
    }

    void drawPoint(point p, QColor color = Qt::black) {
        painter->setPen(color);
        clear_flag = false;
        double z1 = sqrt(2)/2 * p.z();
        painter->drawPoint(XCENTER+p.x() - z1, YCENTER-p.y() + z1);
    }

    void drawLine(point p1, point p2) {
        clear_flag = false;
        double z1 = 0;//sqrt(2)/2 * p1.z();
        double z2 = 0;//sqrt(2)/2 * p2.z();
        painter->drawLine(XCENTER + p1.x() - z1, YCENTER - p1.y() + z1,
                             XCENTER+p2.x() - z2, YCENTER - p2.y() + z2);
    }

    void setColor(QColor color){
        painter->setPen(color);
    }
};

#endif // MESCENE_H
