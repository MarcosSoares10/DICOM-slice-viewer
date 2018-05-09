#ifndef VIEWDICOM3D_H
#define VIEWDICOM3D_H

#include <QMainWindow>
#include <QSettings>
#include <QPoint>
#include <QMouseEvent>


namespace Ui {
class ViewDicom3d;
}

#include <QGLWidget>

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);

signals:

public slots:

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

   // QSize minimumSizeHint() const;
    //QSize sizeHint() const;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);




public slots:
    // slots for xyz-rotation slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);




signals:
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);




private:
    void draw();

    int xRot;
    int yRot;
    int zRot;



    QPoint lastPos;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:


private:
    Ui::ViewDicom3d *ui;
    MyGLWidget *view;
};

#endif // VIEWDICOM3D_H
