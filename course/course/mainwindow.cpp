#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->draw_label->setPixmap(myScene.getPixmap());

    myScene.setColor(Qt::black);
    xyz.render(myScene);
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
   ui->draw_label->setPixmap(myScene.getPixmap());
   xyz.tostart();
   xyz.render(myScene);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_S)
    {
        xyz.rotate(-5,0,0);
        alphax -= 5;
    }
    else if (event->key() == Qt::Key_D)
    {
        xyz.rotate(0,-5,0);
        alphay -= 5;
    }
    else if (event->key() == Qt::Key_A)
    {
        xyz.rotate(0,5,0);
        alphay += 5;
    }
    else if (event->key() == Qt::Key_W)
    {
        xyz.rotate(+5,0,0);
        alphax += 5;
    }
    else if (event->key() == Qt::Key_E)
    {
        xyz.rotate(0,0,-5);
        alphaz += 5;
    }
    else if (event->key() == Qt::Key_Z)
    {
        xyz.rotate(0,0,5);
        alphaz -= 5;
    }
    ui->draw_label->clear();
    myScene.clear();

    xyz.render(myScene);
    ui->draw_label->setPixmap(myScene.getPixmap());
}
