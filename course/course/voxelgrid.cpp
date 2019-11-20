#include "voxelgrid.h"

VoxelGrid::VoxelGrid():
    xcount(0),
    ycount(0),
    zcount(0),
    voxelsize(0),
    defaultDensity(0)
{}

VoxelGrid::VoxelGrid(double size, int x, int y, int z, double d):
    xcount(x),
    ycount(y),
    zcount(z),
    voxelsize(size),
    defaultDensity(d)
{
    for (double kk = 0; kk < zcount; kk++) {
        for (double jj = 0; jj < ycount; jj++) {
            for (double ii = 0; ii < xcount; ii++) {
                Voxel voxel;
                voxel.density = defaultDensity;
                grid.push_back(voxel);
            }
        }
    }
}

bool VoxelGrid::outside(int x, int y, int z) {
    if ((x >= xcount) || (y >= ycount) || (z >= zcount) || (x < 0) || (y < 0) || (z < 0)) {
        return true;
    }
    return false;
}

int VoxelGrid::getVoxelIndex(int x, int y, int z)
{
    return x + y*xcount + z*xcount*ycount;
}

void VoxelGrid::setVoxelColor(int x, int y, int z, vec3 rgb)
{
    if (outside(x,y,z)) {
        return;
    }

    int index = getVoxelIndex(x, y, z);
    grid[index].color = rgb;
}

void VoxelGrid::setVoxelDensity(int x, int y, int z, double d)
{
    if (outside(x,y,z)) {
        return;
    }

    int index = getVoxelIndex(x, y, z);
    grid[index].density = d;
}

void VoxelGrid::setVoxelTransmissivity(int x, int y, int z, double q)
{
    if (outside(x,y,z)) {
        return;
    }

    int index = getVoxelIndex(x, y, z);
    grid[index].transmissivity = q;
}


vec3 VoxelGrid::getVoxelColor(int x, int y, int z)
{
    if (outside(x,y,z)) {
        return vec3(0, 0, 0);
    }

    int index = getVoxelIndex(x, y, z);
    return grid[index].color;
}

double VoxelGrid::getVoxelDensity(int x, int y, int z)
{
    if (outside(x,y,z)) {
        return defaultDensity;
    }

    int index = getVoxelIndex(x, y, z);
    return grid[index].density;
}

double VoxelGrid::getVoxelTransmissivity(int x, int y, int z)
{
    if (outside(x,y,z)) {
        return 0;
    }

    int index = getVoxelIndex(x, y, z);
    return grid[index].transmissivity;
}

std::vector<Voxel> VoxelGrid::getVoxelGrid() { return grid; }
double VoxelGrid::getVoxelSize() { return voxelsize; }
double VoxelGrid::getDefaultDensity() { return defaultDensity; }
int VoxelGrid::getMaxX() { return xcount; }
int VoxelGrid::getMaxY() { return ycount; }
int VoxelGrid::getMaxZ() { return zcount; }

