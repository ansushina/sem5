#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <stdio.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    light(point(0,1450,0))
{
    grid = NULL;
    ui->setupUi(this);
    ui->draw_label->setPixmap(myScene.getPixmap());

    myScene.setColor(Qt::black);
    //sxyz.render(myScene);
    ui->draw_label->setPixmap(myScene.getPixmap());

    vec3 d(1,1,1);
    printf("%d %d %d\n", (int)d[0],(int)d[1],(int)d[2]);
    const vec3 d1(1,1,1);
    //printf("%lf %lf %lf\n", d1[0],d1[1],d1[2]);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_clear_button_clicked()
{
   ui->draw_label->clear();
   myScene.clear();
   myScene.init();
   ui->draw_label->setPixmap(myScene.getPixmap());
   densityDelta = ui->densitySlider->value();
   pointsCache.clear();
   colorCache.clear();

   ui->settings_list->clear();
   ui->settings_list->append("k = " +  QString::number(myScene.k));
   ui->settings_list->append("dx = " +  QString::number(myScene.dx));
   ui->settings_list->append("dy = " +  QString::number(myScene.dy));
   ui->settings_list->append("dz = " +  QString::number(myScene.dz));
   ui->settings_list->append("alphax = " +  QString::number(myScene.alphax));
   ui->settings_list->append("alphay = " +  QString::number(myScene.alphay));
   ui->settings_list->append("alphaz = " +  QString::number(myScene.alphaz));

   ui->draw_label->setPixmap(myScene.getPixmap());
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() != Qt::Key_S && event->key() != Qt::Key_W &&
        event->key() != Qt::Key_A && event->key() != Qt::Key_D &&
        event->key() != Qt::Key_E && event->key() != Qt::Key_Z &&
        event->key() != Qt::Key_U && event->key() != Qt::Key_J &&
        event->key() != Qt::Key_H && event->key() != Qt::Key_K &&
        event->key() != Qt::Key_N && event->key() != Qt::Key_I&&
        event->key() != Qt::Key_Plus && event->key() != Qt::Key_Minus    )
        return;

    if (event->key() == Qt::Key_S)
    {
        //xyz.rotate(-5,0,0);
        myScene.alphax -= 5;
    }
    else if (event->key() == Qt::Key_D)
    {
       // xyz.rotate(0,-5,0);
        myScene.alphay -= 5;
    }
    else if (event->key() == Qt::Key_A)
    {
       // xyz.rotate(0,5,0);
        myScene.alphay += 5;
    }
    else if (event->key() == Qt::Key_W)
    {
       // xyz.rotate(+5,0,0);
        myScene.alphax += 5;
    }
    else if (event->key() == Qt::Key_E)
    {
        //xyz.rotate(0,0,-5);
        myScene.alphaz += 5;
    }
    else if (event->key() == Qt::Key_Z)
    {
       // xyz.rotate(0,0,5);
        myScene.alphaz -= 5;
    }
    else if (event->key() == Qt::Key_Plus)
    {
        myScene.k *= 1.2;
    }
    else if (event->key() == Qt::Key_Minus)
    {
       myScene.k *= (double)5/6;
    }
    else if (event->key() == Qt::Key_H)
    {
       myScene.dx -= 10;
    }
    else if (event->key() == Qt::Key_K)
    {
       myScene.dx += 10;
    }
    else if (event->key() == Qt::Key_U)
    {
       myScene.dy += 10;
    }
    else if (event->key() == Qt::Key_J)
    {
       myScene.dy -= 10;
    }
    else if (event->key() == Qt::Key_I)
    {
       myScene.dz += 10;
    }
    else if (event->key() == Qt::Key_N)
    {
       myScene.dz -= 10;
    }


    ui->draw_label->clear();
    myScene.clear();

    //xyz.render(myScene);
    renderFromCache();
    ui->draw_label->setPixmap(myScene.getPixmap());

}

void MainWindow::renderFromCache() {
    if (pointsCache.empty()) {renderGrid(); return;}
    ui->settings_list->clear();
    ui->settings_list->append("k = " +  QString::number(myScene.k));
    ui->settings_list->append("dx = " +  QString::number(myScene.dx));
    ui->settings_list->append("dy = " +  QString::number(myScene.dy));
    ui->settings_list->append("dz = " +  QString::number(myScene.dz));
    ui->settings_list->append("alphax = " +  QString::number(myScene.alphax));
    ui->settings_list->append("alphay = " +  QString::number(myScene.alphay));
    ui->settings_list->append("alphaz = " +  QString::number(myScene.alphaz));
    //printf("dx %lf dy %lf dz %lf;;; k %lf;;; ax %lf, ay %lf, az %lf;\n", myScene.dx, myScene.dy, myScene.dz, myScene.k, myScene.alphax, myScene.alphay,myScene.alphaz);
    for (int i = 0; i < pointsCache.size(); i++)
    {
        myScene.drawCircle(pointsCache[i], 1.5, colorCache[i]);
        //printf("color %d", colorCache[i].red());
    }
}

void MainWindow::renderGrid() {
    pointsCache.clear();
    colorCache.clear();
    if (!grid) return;
    point center = generateCloud.getCenter();

    ui->settings_list->clear();
    ui->settings_list->append("k = " +  QString::number(myScene.k));
    ui->settings_list->append("dx = " +  QString::number(myScene.dx));
    ui->settings_list->append("dy = " +  QString::number(myScene.dy));
    ui->settings_list->append("dz = " +  QString::number(myScene.dz));
    ui->settings_list->append("alphax = " +  QString::number(myScene.alphax));
    ui->settings_list->append("alphay = " +  QString::number(myScene.alphay));
    ui->settings_list->append("alphaz = " +  QString::number(myScene.alphaz));
/*
    //printf("dx %lf dy %lf dz %lf;;; k %lf;;; ax %lf, ay %lf, az %lf;\n", myScene.dx, myScene.dy, myScene.dz, myScene.k, myScene.alphax, myScene.alphay,myScene.alphaz);
    for (int kk = 0; kk < grid->getMaxZ(); kk++) {
        for (int jj = 0; jj < grid->getMaxY(); jj++) {
            for (int ii = 0; ii < grid->getMaxX(); ii++) {
                if (grid->getVoxelDensity(ii,jj,kk) > 0.9 + densityDelta) {
                    //printf("density [%d %d %d]: %lf\n", kk, jj, ii, grid->getVoxelDensity(ii,jj,kk) );
                    const vec3 c = grid->getVoxelColor(ii,jj,kk);
                    QColor *color = new QColor((int)c[0],(int) c[1], (int) c[2], grid->getVoxelDensity(ii,jj,kk)*40);
                    //myScene.drawPoint(point(ii, jj, kk), *color);
                    //myScene.drawCircle(point(ii*2-center.x()*2, jj*2-center.y()*2, kk*2 - center.z()*2), 1.5, *color);
                    pointsCache.push_back(point(ii*2-center.x()*2, jj*2-center.y()*2, kk*2 - center.z()*2));
                    colorCache.push_back(*color);
                }
            }
        }
    }
    liting();*/
    light.smth(grid,pointsCache,colorCache,densityDelta);
    renderFromCache();
    printf("render done\n");
    ui->main_list->clear();
    ui->main_list->append("Размер окна: " + QString::number(CW)+"x" + QString::number(CH));

    ui->main_list->append("Размер облака: " + QString::number(grid->getMaxX()) + "x" +
                          QString::number(grid->getMaxY()) + "x" + QString::number(grid->getMaxZ()));
    ui->main_list->append("Всего вокселей: "+QString::number(grid->getMaxX()*grid->getMaxY()* grid->getMaxZ()));
    ui->main_list->append("Из них значимых: "+QString::number(pointsCache.size()));


}

void MainWindow::on_pushButton_2_clicked()
{
    ui->draw_label->clear();
    myScene.clear();
    //xyz.render(myScene);
    generateCloud.generateVoxelGridRandom(18);

    printf("generate DONE\n");
    grid = generateCloud.getGrid();
    renderGrid();
    ui->draw_label->setPixmap(myScene.getPixmap());

    ui->main_list->clear();
    ui->main_list->append("Размер окна: " + QString::number(CW)+"x" + QString::number(CH));

    ui->main_list->append("Размер облака: " + QString::number(grid->getMaxX()) + "x" +
                          QString::number(grid->getMaxY()) + "x" + QString::number(grid->getMaxZ()));
    ui->main_list->append("Всего вокселей: "+QString::number(grid->getMaxX()*grid->getMaxY()* grid->getMaxZ()));
    ui->main_list->append("Из них значимых: "+QString::number(pointsCache.size()));

}



void MainWindow::on_densitySlider_valueChanged(int value)
{
    densityDelta = -(double)value/200;
    printf("density: %lf (%lf)", 0.9 + densityDelta, densityDelta);

    ui->draw_label->clear();
    myScene.clear();

    //xyz.render(myScene);
    renderGrid();
    ui->draw_label->setPixmap(myScene.getPixmap());
}

void MainWindow::on_button_size_clicked()
{
    int yy = ui->y_spin->value();
    int xx = ui->x_spin->value();
    int zz = ui->z_spin->value();
    ui->draw_label->clear();
    myScene.clear();
    //xyz.render(myScene);
    generateCloud.generateVoxelGridRandom(18,xx,yy,zz);

    printf("generate DONE\n");
    grid = generateCloud.getGrid();
    renderGrid();
    ui->draw_label->setPixmap(myScene.getPixmap());

    ui->main_list->clear();
    ui->main_list->append("Размер окна: " + QString::number(CW)+"x" + QString::number(CH));

    ui->main_list->append("Размер облака: " + QString::number(grid->getMaxX()) + "x" +
                          QString::number(grid->getMaxY()) + "x" + QString::number(grid->getMaxZ()));
    ui->main_list->append("Всего вокселей: "+QString::number(grid->getMaxX()*grid->getMaxY()* grid->getMaxZ()));
    ui->main_list->append("Из них значимых: "+QString::number(pointsCache.size()));
}
