#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include "myscene.h"
#include "axis.h"
#include "render.h"

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

private:
    void renderGrid();

    Ui::MainWindow *ui;
    Scene myScene;
    Axis xyz;
    Render generateCloud;
    VoxelGrid *grid;
};

#endif // MAINWINDOW_H
