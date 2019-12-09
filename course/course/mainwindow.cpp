#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <stdio.h>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //grid = NULL;
    ui->setupUi(this);
    ui->draw_label->setPixmap(myScene.getPixmap());

    myScene.setColor(Qt::black);
    //sxyz.render(myScene);
    ui->draw_label->setPixmap(myScene.getPixmap());
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
   generateCloud.clear();

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
        myScene.alphax -= 5;
    }
    else if (event->key() == Qt::Key_D)
    {
        myScene.alphay -= 5;
    }
    else if (event->key() == Qt::Key_A)
    {
        myScene.alphay += 5;
    }
    else if (event->key() == Qt::Key_W)
    {
        myScene.alphax += 5;
    }
    else if (event->key() == Qt::Key_E)
    {
        myScene.alphaz += 5;
    }
    else if (event->key() == Qt::Key_Z)
    {
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
    renderFromCache();
    ui->draw_label->setPixmap(myScene.getPixmap());

}

void MainWindow::renderFromCache() {
    generateCloud.renderFromCache(myScene);
    ui->draw_label->setPixmap(myScene.getPixmap());
    ui->settings_list->clear();
    ui->settings_list->append("k = " +  QString::number(myScene.k));
    ui->settings_list->append("dx = " +  QString::number(myScene.dx));
    ui->settings_list->append("dy = " +  QString::number(myScene.dy));
    ui->settings_list->append("dz = " +  QString::number(myScene.dz));
    ui->settings_list->append("alphax = " +  QString::number(myScene.alphax));
    ui->settings_list->append("alphay = " +  QString::number(myScene.alphay));
    ui->settings_list->append("alphaz = " +  QString::number(myScene.alphaz));
}

void MainWindow::on_pushButton_2_clicked()
{

    density = 0;
    ui->draw_label->clear();
    myScene.clear();
    generateCloud.generateVoxelGridRandom(18);

    printf("generate DONE\n");
    grid = generateCloud.getGrid();
    generateCloud.putPointsToCache(0);
    renderFromCache();
    ui->draw_label->setPixmap(myScene.getPixmap());

    ui->main_list->clear();
    ui->main_list->append("Размер окна: " + QString::number(CW)+"x" + QString::number(CH));

    ui->main_list->append("Размер облака: " + QString::number(grid.getMaxX()) + "x" +
                          QString::number(grid.getMaxY()) + "x" + QString::number(grid.getMaxZ()));
    ui->main_list->append("Всего вокселей: "+QString::number(grid.getMaxX()*grid.getMaxY()* grid.getMaxZ()));
    ui->main_list->append("Из них значимых: "+QString::number(generateCloud.cacheCount()));

}



void MainWindow::on_densitySlider_valueChanged(int value)
{
    densityDelta = -(double)value/200;
    //printf("density: %lf (%lf)", 0.9 + densityDelta, densityDelta);

    ui->draw_label->clear();
    myScene.clear();

    //xyz.render(myScene);
    generateCloud.putPointsToCache(density+densityDelta);
    renderFromCache();
    ui->draw_label->setPixmap(myScene.getPixmap());
    ui->main_list->clear();
    ui->main_list->append("Размер окна: " + QString::number(CW)+"x" + QString::number(CH));
    ui->main_list->append("Размер облака: " + QString::number(grid.getMaxX()) + "x" +
                          QString::number(grid.getMaxY()) + "x" + QString::number(grid.getMaxZ()));
    ui->main_list->append("Всего вокселей: "+QString::number(grid.getMaxX()*grid.getMaxY()* grid.getMaxZ()));
    ui->main_list->append("Из них значимых: "+QString::number(generateCloud.cacheCount()));
}

void MainWindow::on_button_size_clicked()
{
    density = 0.9;
    int yy = ui->y_spin->value();
    int xx = ui->x_spin->value();
    int zz = ui->z_spin->value();
    ui->draw_label->clear();
    myScene.clear();
    generateCloud.generateVoxelGridRandom(18,xx,yy,zz);
    printf("generate DONE\n");

    generateCloud.putPointsToCache(density+densityDelta);

    grid = generateCloud.getGrid();
    ui->main_list->clear();
    ui->main_list->append("Размер окна: " + QString::number(CW)+"x" + QString::number(CH));
    ui->main_list->append("Размер облака: " + QString::number(grid.getMaxX()) + "x" +
                          QString::number(grid.getMaxY()) + "x" + QString::number(grid.getMaxZ()));
    ui->main_list->append("Всего вокселей: "+QString::number(grid.getMaxX()*grid.getMaxY()* grid.getMaxZ()));
    ui->main_list->append("Из них значимых: "+QString::number(generateCloud.cacheCount()));

    renderFromCache();
}

void MainWindow::on_clear_button_2_clicked()
{
      myScene.init();
      ui->draw_label->clear();
      myScene.clear();
      renderFromCache();
      ui->draw_label->setPixmap(myScene.getPixmap());
}

void MainWindow::on_button_exsample_2_clicked()
{
    ui->y_spin->setValue(30);
    ui->x_spin->setValue(100);
    ui->z_spin->setValue(100);
    myScene.alphax = 90;
    on_button_size_clicked();
    ui->densitySlider->setValue(20);
}

void MainWindow::on_button_exsample_3_clicked()
{
   ui->y_spin->setValue(30);
   ui->x_spin->setValue(100);
   ui->z_spin->setValue(100);
   myScene.alphax = 90;
   on_button_size_clicked();
   ui->densitySlider->setValue(-18);
}

void MainWindow::on_button_exsample_4_clicked()
{
    ui->y_spin->setValue(30);
    ui->x_spin->setValue(100);
    ui->z_spin->setValue(100);
    myScene.dz = -50;
    myScene.k = 1.2*1.2*1.2*1.2;
    on_button_size_clicked();
}

void MainWindow::on_action_triggered()
{
    QFileDialog dialog;
    QString fname = dialog.getOpenFileName();
    if (fname == NULL) {
        return;
    }
    std::string filename = fname.toStdString();
    generateCloud.readFromFile(filename);
    ui->draw_label->clear();
    myScene.clear();
    printf("generate DONE\n");
    grid = generateCloud.getGrid();
    ui->main_list->clear();
    ui->main_list->append("Размер окна: " + QString::number(CW)+"x" + QString::number(CH));
    ui->main_list->append("Размер облака: " + QString::number(grid.getMaxX()) + "x" +
                          QString::number(grid.getMaxY()) + "x" + QString::number(grid.getMaxZ()));
    ui->main_list->append("Всего вокселей: "+QString::number(grid.getMaxX()*grid.getMaxY()* grid.getMaxZ()));
    ui->main_list->append("Из них значимых: "+QString::number(generateCloud.cacheCount()));

    renderFromCache();

}

void MainWindow::on_action_2_triggered()
{
    QFileDialog dialog;
    QString fname = dialog.getSaveFileName();
    if (fname == NULL) {
        return;
    }
    std::string filename = fname.toStdString();
    generateCloud.saveToFile(filename);
}

void MainWindow::test(){
    setbuf(stdout, NULL);
    density = 0.9;
    densityDelta = 0;
    FILE *f = fopen("time.txt", "w");
    fprintf(f,"%5s,%10s,%10s,%10s\n", "N" , "1", "2", "-");
    printf("%5s,%10s,%10s,%10s\n", "N" , "1", "2", "-");
    std::clock_t time = 0;
    int repeat = 10;
    int start = 120;
    int end = 150;
    int step = 10;
    for (int i = start; i < end; i+=step) {
        fprintf(f, "%5d,", i*i*i);
        printf("%5d,", i*i*i);

        time = 0;
        for (int j = 0; j < repeat ; j++)
        {
            std::clock_t start = std::clock();
            generateCloud.generateVoxelGridRandom(18,i,i,i);
            std::clock_t end = std::clock();
            time += end-start;
        }
        printf("%10d,", time/repeat);
        fprintf(f,"%10d,", time/repeat);
        generateCloud.putPointsToCache(density+densityDelta);
        grid = generateCloud.getGrid();
        printf("%10d,",  generateCloud.cacheCount());
        fprintf(f,"%10d,",  generateCloud.cacheCount());
        time = 0;
        for (int j = 0; j < repeat ; j++)
        {
            std::clock_t start = std::clock();
            renderFromCache();
            std::clock_t end = std::clock();
            time += end-start;
        }
        printf("%10d,\n", time/repeat);
        fprintf(f,"%10d,\n", time/repeat);
    }
    fclose(f);
}

void MainWindow::on_action_4_triggered()
{
    QMessageBox msg;
    msg.setText("Клавиши W/S предназначены для вращения облака  вокруг оси OX."
                "Клавиши A/D предназначены для вращения облака  вокруг оси OY."
                "Клавиши Z/E предназначены для вращения облака  вокруг оси OZ."
                "Клавиши H/K предназначены для перемещения облака по оси OX."
                "Клавиши J/U предназначены  для перемещения облака по оси OY."
                "Клавиши N/I предназначены  для перемещения облака по оси OZ."
                "Клавиши +/- предназначены для масштабирования облака относительно начала координат.");
    msg.exec();
}

void MainWindow::on_pushButton_clicked()
{
    test();
}
