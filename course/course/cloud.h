#ifndef CLOUD_H
#define CLOUD_H
#include "voxelgrid.h"
#include "camera.h"
#include "Noise.h"


class Cloud
{
public:
    Cloud();
    ~Cloud();
    void generateVoxelGridRandom(int seed);
    VoxelGrid* getGrid();

    point getCenter() {
        return point(vGrid->getMaxX()/2, vGrid->getMaxY()/2, vGrid->getMaxZ()/2);
    }

    void scalePoint(point p, double k) {
        p.scaleUniform(this->getCenter(), k);
    }

    point rotateCloudPoint(double alphax=0, double alphay=0, double alphaz=0);

private:
    VoxelGrid *vGrid;
    camera *m_camera;
};

#endif // CLOUD_H
