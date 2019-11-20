#ifndef RENDER_H
#define RENDER_H
#include "voxelgrid.h"
#include "camera.h"
#include "Noise.h"


class Render
{
public:
    Render();
    ~Render();
    void generateVoxelGridRandom(int seed);
    VoxelGrid* getGrid();
private:
    VoxelGrid *vGrid;
    camera *m_camera;
};

#endif // RENDER_H
