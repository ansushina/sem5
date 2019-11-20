#ifndef VOXELGRID_H
#define VOXELGRID_H
#include <vector>
#include <QColor>
#include "vector3.h"
#include <stdio.h>

struct Voxel {
    QColor qcolor;
    vec3 color;

    double density; //плотность
    double transmissivity; // прозратчность

    void print(){
        printf("voxel: color(%lf, %lf, %lf), density: %lf, transm.: %lf \n", color[0], color[1], color[2], density, transmissivity);
    }
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

    void printVoxel(int x, int y, int z) {
        if (outside(x,y,z)) {
            return;
        }

        printf("[%d, %d, %d]", x, y, z);
        int index = getVoxelIndex(x, y, z);
        grid[index].print();
    }
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
