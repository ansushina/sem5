#ifndef LIGHT_H
#define LIGHT_H
#include <QColor>
#include <vector>
#include "point.h"
#include "voxelgrid.h"
#include "matrix.h"

class Light {
public:
    Light(point center): lightCenter(center), Rmax(0), Rmin(-1) {}

    void smth (VoxelGrid *grid, std::vector<point> &pointsCache, std::vector<QColor> &colorCache, double densityDelta) {
        pointsCache.clear();
        colorCache.clear();
        if (!grid) return;
        point center(grid->getMaxX()/2, grid->getMaxY()/2, grid->getMaxZ()/2);
        Matrix mybuffer(grid->getMaxZ(),grid->getMaxX());
        for (int  yy = grid->getMaxY()-1; yy >= 0; yy--) {
            for (int  zz = 0 ; zz < grid->getMaxZ(); zz++ ) {
                for (int xx = 0; xx < grid->getMaxX(); xx++ ) {
                    if (grid->getVoxelDensity(xx,yy,zz) > 0.9 + densityDelta) {
                        const vec3 c = grid->getVoxelColor(xx,yy,zz);
                        QColor *color = new QColor((int)c[0],(int) c[1], (int) c[2], grid->getVoxelDensity(xx,yy,zz)*40);
                        pointsCache.push_back(point(xx*2-center.x()*2, yy*2-center.y()*2, zz*2 - center.z()*2));

                        int colorKoef = 1.5 * mybuffer[zz][xx];

                        color->setRed(color->red()-colorKoef);
                        color->setGreen(color->green()-colorKoef);
                        color->setBlue(color->blue()-colorKoef);
                        mybuffer[zz][xx] += 1;
                        colorCache.push_back(*color);
                    }
                }
            }
        }
    }

    void setCmin(QColor Cm) {
        Cmin = Cm;
    }

    void setCmax(QColor Cm) {
        Cmax = Cm;
    }
private:
    point lightCenter;
    double Rmax, Rmin;
    QColor Cmin, Cmax;

};

#endif // LIGHT_H
