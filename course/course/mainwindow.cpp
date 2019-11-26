#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <stdio.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->draw_label->setPixmap(myScene.getPixmap());

    myScene.setColor(Qt::black);
    xyz.render(myScene);
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
   xyz.tostart();
   xyz.render(myScene);
   ui->draw_label->setPixmap(myScene.getPixmap());

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() != Qt::Key_S && event->key() != Qt::Key_W &&
        event->key() != Qt::Key_A && event->key() != Qt::Key_D &&
        event->key() != Qt::Key_E && event->key() != Qt::Key_Z &&
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
    ui->draw_label->clear();
    myScene.clear();

    xyz.render(myScene);
    renderGrid();
    ui->draw_label->setPixmap(myScene.getPixmap());

}

void MainWindow::renderGrid() {
    for (int kk = 0; kk < grid->getMaxZ(); kk++) {
        for (int jj = 0; jj < grid->getMaxY(); jj++) {
            for (int ii = 0; ii < grid->getMaxX(); ii++) {
                if (grid->getVoxelDensity(ii,jj,kk)) {
                    const vec3 c = grid->getVoxelColor(ii,jj,kk);
                    QColor *color = new QColor((int)c[0],(int) c[1], (int) c[2], grid->getVoxelDensity(ii,jj,kk)*255);
                    myScene.drawPoint(point(ii, jj, kk), *color);
                }
            }
        }
    }
    printf("render done\n");

}

void MainWindow::on_pushButton_2_clicked()
{
    generateCloud.generateVoxelGridRandom(18);

    printf("generate DONE\n");
    grid = generateCloud.getGrid();
    renderGrid();
    ui->draw_label->setPixmap(myScene.getPixmap());
}
