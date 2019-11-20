#ifndef VOXELGRID_H
#define VOXELGRID_H
#include <vector>
#include <QColor>
#include "vector3.h"


struct Voxel {
    QColor qcolor;
    vec3 color;

    double density; //плотность
    double transmissivity; // прозратчность
};

class VoxelGrid
{
public:
    VoxelGrid();
    VoxelGrid(double size, int x, int y, int z, double d);
    ~VoxelGrid(){
        grid.clear();
    }

    void setVoxelColor(int x, int y, int z, vec3 rgb);
    void setVoxelDensity(int x, int y, int z, double q);
    void setVoxelTransmissivity(int x, int y, int z, double q);

    vec3 getVoxelColor(int x, int y, int z);
    double getVoxelDensity(int x, int y, int z);
    double getVoxelTransmissivity(int x, int y, int z);


    int getVoxelIndex(int x, int y, int z);
    std::vector<Voxel> getVoxelGrid();
    double getVoxelSize();
    double getDefaultDensity();
    int getMaxX(); int getMaxY(); int getMaxZ();
private:
    bool outside(int x, int y, int z);

    int xcount, ycount, zcount;
    double voxelsize;
    double defaultDensity;

    std::vector<Voxel> grid;
};

#endif // VOXELGRID_H
