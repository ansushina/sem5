#include "render.h"
#include "Noise.h"
#include <math.h>

Render::Render()
{
    vGrid = new VoxelGrid;
}

Render::~Render(){
    delete vGrid;
}

void Render::generateVoxelGridRandom(int seed)
{
    VoxelGrid *grid = new VoxelGrid(0.1, 50, 50, 50, 0);
    Noise *noise = new Noise(0.5, 5, seed); // Seed = 188

    // Get max length from grid center to grid surface
    vec3 center(grid->getMaxX()*0.5, grid->getMaxY()*0.5, grid->getMaxZ()*0.5);
    double max_distance = (vec3(0 + 0.5, 0 + 0.5, 0 + 0.5) - center).length();
    double max_ratio = 1/max_distance;

    // Generate random density
    for (int kk = 0; kk < grid->getMaxZ(); kk++) {
        for (int jj = 0; jj < grid->getMaxY(); jj++) {
            for (int ii = 0; ii < grid->getMaxX(); ii++) {
                double cloud = noise->PerlinNoise3(ii*grid->getVoxelSize(), jj*grid->getVoxelSize(), kk*grid->getVoxelSize());

                vec3 voxel(vec3(ii + 0.5, jj + 0.5, kk + 0.5));
                double distance = (voxel - center).length(); // Distance from current voxel to grid center
                double cover = distance*max_ratio + 0.3; // Amount of cloud (0.93)
                double sharpness = 0.5; // Cloud fuzziness and sharpness
                double density = 5; // Cloud density

                cloud = cloud - cover;
                if (cloud < 0) cloud = 0;
                cloud = cloud*density;
                cloud = 1.0 - powf(sharpness, cloud);

                grid->setVoxelDensity(ii, jj, kk, cloud);

                vec3 color(255, 255, 255);
                grid->setVoxelColor(ii, jj, kk, color);

                //grid->printVoxel(ii,jj,kk);
            }
        }
        // Render progress 0%-99%
        //renderProgress(0, ((double)kk/(grid->getMaxZ() - 1))*100.0);
    }

    vGrid = grid; // Set voxel grid
    // Render progress 100%
    //for (int ii = 0; ii < 100; ii++ ) { renderProgress(0, 100); }
}

VoxelGrid* Render::getGrid()
{
    return vGrid;
}
