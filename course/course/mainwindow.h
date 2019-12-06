#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include "myscene.h"
#include "axis.h"
#include "cloud.h"
#include "camera.h"
#include "light.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_clear_button_clicked();

    void on_pushButton_2_clicked();


    void on_densitySlider_valueChanged(int value);

    void on_button_size_clicked();

private:
    void liting();
    void renderGrid();
    void renderFromCache();

    Ui::MainWindow *ui;
    Scene myScene;
    Axis xyz;
    Cloud generateCloud;
    VoxelGrid *grid;
    double densityDelta;
    std::vector<point> pointsCache;
    std::vector<QColor> colorCache;
    Light light;
};

#endif // MAINWINDOW_H
