#include "cloud.h"
#include "Noise.h"
#include <math.h>
#include <stdlib.h>

Cloud::Cloud(){}

Cloud::~Cloud(){
    //delete vGrid;
}

void Cloud::generateVoxelGridRandom(int seed)
{
    VoxelGrid grid(0.1, 50, 50, 50, 0);
    Noise *noise = new Noise(0.5, 5, seed); // Seed = 188

    // Get max length from grid center to grid surface
    vec3 center(grid.getMaxX()*0.5, grid.getMaxY()*0.5, grid.getMaxZ()*0.5);
    double max_distance = (vec3(0 + 0.5, 0 + 0.5, 0 + 0.5) - center).length();
    double max_ratio = 1/max_distance;

    // Generate random density
    for (int kk = 0; kk < grid.getMaxZ(); kk++) {
        for (int jj = 0; jj < grid.getMaxY(); jj++) {
            for (int ii = 0; ii < grid.getMaxX(); ii++) {
                double cloud = noise->PerlinNoise3(ii*grid.getVoxelSize(), jj*grid.getVoxelSize(), kk*grid.getVoxelSize());

                vec3 voxel(vec3(ii + 0.5, jj + 0.5, kk + 0.5));
                double distance = (voxel - center).length(); // Distance from current voxel to grid center
                double cover = distance*max_ratio + 0.2; // Amount of cloud (0.93)

                cloud = cloud - cover;
                if (cloud < 0) cloud = 0;
                grid.setVoxelDensity(ii, jj, kk, cloud);

                vec3 color(255, 255, 255);
                grid.setVoxelColor(ii, jj, kk, color);

                //grid.printVoxel(ii,jj,kk);
            }
        }
        // Cloud progress 0%-99%
        //CloudProgress(0, ((double)kk/(grid.getMaxZ() - 1))*100.0);
    }
    delete noise;
    vGrid = grid; // Set voxel grid
    // Cloud progress 100%
    //for (int ii = 0; ii < 100; ii++ ) { CloudProgress(0, 100); }
}

void Cloud::generateVoxelGridRandom(int seed, int x, int y, int z)
{
    VoxelGrid grid(0.1, x, y, z, 0);
    Noise *noise = new Noise(0.5, 5, seed);
    for (int kk = 0; kk < grid.getMaxZ(); kk++) {
        for (int jj = 0; jj < grid.getMaxY(); jj++) {
            for (int ii = 0; ii < grid.getMaxX(); ii++) {
                double cloud = noise->PerlinNoise3(ii*grid.getVoxelSize(), jj*grid.getVoxelSize(), kk*grid.getVoxelSize());
                grid.setVoxelDensity(ii, jj, kk, cloud);
                vec3 color(255, 255, 255);
                grid.setVoxelColor(ii, jj, kk, color);
            }
        }
    }
    delete noise;
    vGrid = grid;
}

void Cloud::putPointsToCache(double densityDelta) {
    VoxelGrid grid = vGrid;
    pointsCache.clear();
    colorCache.clear();
    //if (!grid) return;
    point center(grid.getMaxX()/2, grid.getMaxY()/2, grid.getMaxZ()/2);
    Matrix mybuffer(grid.getMaxZ(),grid.getMaxX());
    for (int  yy = grid.getMaxY()-1; yy >= 0; yy--) {
        for (int  zz = 0 ; zz < grid.getMaxZ(); zz++ ) {
            for (int xx = 0; xx < grid.getMaxX(); xx++ ) {
                if (grid.getVoxelDensity(xx,yy,zz) > densityDelta) {

                    const vec3 c = grid.getVoxelColor(xx,yy,zz);
                    QColor color((int)c[0],(int) c[1], (int) c[2], grid.getVoxelDensity(xx,yy,zz)*40);

                    int colorKoef = 1.5 * mybuffer[zz][xx];

                    color.setRed(color.red()-colorKoef);
                    color.setGreen(color.green()-colorKoef);
                    color.setBlue(color.blue()-colorKoef);
                    mybuffer[zz][xx] += 1;
                    colorCache.push_back(color);
                    pointsCache.push_back(point(xx*2-center.x()*2, yy*2-center.y()*2, zz*2 - center.z()*2));
                }
            }
        }
    }
}



void Cloud::renderFromCache(Scene &scene) {
    if (pointsCache.empty()) {return;}
    for (int i = 0; i < pointsCache.size(); i++)
    {
        scene.drawCircle(pointsCache[i], 1.5, colorCache[i]);
    }
}

void Cloud::saveToFile(std::string filename){
    FILE *f = fopen(filename.c_str(), "w");
    fprintf(f, "%d\n", pointsCache.size());
    for (int i = 0; i < pointsCache.size(); i++)
    {
        point p = pointsCache[i];
        QColor q = colorCache[i];
        fprintf(f, "%d %d %d %d %d %d %d\n", (int)p.x(), (int)p.y(), (int)p.z(), q.red(), q.green(), q.blue(), q.alpha());
    }
    fclose(f);
}

void Cloud::readFromFile(std::string filename){
    VoxelGrid grid(0.1, 5, 5, 5, 0);
    vGrid = grid;
    pointsCache.clear();
    colorCache.clear();
    FILE *f = fopen(filename.c_str(), "r");
    int size;
    fscanf(f, "%d\n", &size);
    for (int i = 0; i < size; i++)
    {
        int x,y,z;
        int r,g,b,a;
        fscanf(f, "%d%d%d%d%d%d%d", &x, &y, &z, &r, &g, &b, &a);
        point p(x,y,z);
        QColor q;
        q.setRed(r);q.setGreen(g);q.setBlue(b);q.setAlpha(a);
        pointsCache.push_back(p);
        colorCache.push_back(q);
    }
    fclose(f);
}

void Cloud::clear() {
    pointsCache.clear();
    colorCache.clear();
}

VoxelGrid &Cloud::getGrid()
{
    return vGrid;
}
