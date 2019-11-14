#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    clear_flag(true)
{
    ui->setupUi(this);

    scene = new QPixmap(900, 900);
    scene->fill(QColor("transparent"));
    scene->fill(QColor(Qt::white));

    painter = new QPainter(scene);
    painter->setPen(QPen(Qt::black));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete painter;
    delete scene;
}

void MainWindow::on_clear_button_clicked()
{
    delete painter;
    delete scene;
    ui->draw_label->clear();
    scene = new QPixmap(900,900);
    scene->fill(QColor(Qt::white));
    painter = new QPainter(scene);
    ui->draw_label->setPixmap(*scene);
    clear_flag = true;
}
