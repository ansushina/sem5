#ifndef CLOUD_H
#define CLOUD_H
#include "voxelgrid.h"
#include "camera.h"
#include "Noise.h"
#include "myscene.h"


class Cloud
{
public:
    Cloud();
    ~Cloud();
    void generateVoxelGridRandom(int seed);
    void generateVoxelGridRandom(int seed, int x, int y, int z);
    void putPointsToCache(double densityDelta);
    void renderFromCache(Scene &scene);

    VoxelGrid* getGrid();

    point getCenter() {
        return point(vGrid->getMaxX()/2, vGrid->getMaxY()/2, vGrid->getMaxZ()/2);
    }

    size_t cacheCount() {
        return pointsCache.size();
    }
    void clear();

private:
    VoxelGrid *vGrid;
    camera *m_camera;

    std::vector<point> pointsCache;
    std::vector<QColor> colorCache;
};

#endif // CLOUD_H
