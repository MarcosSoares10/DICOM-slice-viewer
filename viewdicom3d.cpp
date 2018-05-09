#include "viewdicom3d.h"
#include "ui_viewdicom3d.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewDicom3d)
{
    ui->setupUi(this);
}




MainWindow::~MainWindow()
{
    delete ui;
}

MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
   xRot=0;
   yRot=0;
   zRot=0;
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void MyGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}


void MyGLWidget::initializeGL()
{
    //qglClearColor(Qt::black);

    glEnable(GL_DEPTH_TEST);
   // glEnable(GL_CULL_FACE);
    //glShadeModel(GL_SMOOTH);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);

    //static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
   // glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -15.0);
   // glScalef(1.0,1.0,1.0); // ////// Escala
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
    draw();
}

void MyGLWidget::resizeGL(int width, int height)
{
    glViewport( 0, 0, (GLint)width, (GLint)height );

       /* create viewing cone with near and far clipping planes */
       glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
       glFrustum( -1.0, 1.0, -1.0, 1.0, 5.0, 30.0);

       glMatrixMode( GL_MODELVIEW );
}

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }

    lastPos = event->pos();
}

void MyGLWidget::draw()
{


        /* create 3D-Cube */
        glBegin(GL_QUADS);



        //
        //                     e3
        //          v5 o----------------o v4
        //            /|               /|
        //           / |              / |
        //      e10 /  |          e9 /  |e7
        //         /   |   e1       /   |
        //     v3 o----------------o v2 |
        //        |    |           |    |
        //        |    |e6         |    |
        //        |e5  |           |e4  |
        //        |    |    e2     |    |
        //        |    o-----------|----o v7
        //        |   /  v6        |   /
        //        |  /             |  /
        //        | /e11           | /e8
        //        |/               |/
        //   y    o----------------o
        //   | z  v0      e0       v1
        //   |/
        //   +---x


            //front
            glColor3f(1.0,0.0,0.0);

            glVertex3f(1.0,1.0,1.0);
            glVertex3f(-1.0,1.0,1.0);
            glVertex3f(-1.0,-1.0,1.0);
            glVertex3f(1.0,-1.0,1.0);


            //back

            glColor3f(0.0,1.0,0.0);

            glVertex3f(1.0,1.0,-1.0);
            glVertex3f(-1.0,1.0,-1.0);
            glVertex3f(-1.0,-1.0,-1.0);
            glVertex3f(1.0,-1.0,-1.0);


            //top
            glColor3f(0.0,0.0,1.0);

            glVertex3f(-1.0,1.0,1.0);
            glVertex3f(1.0,1.0,1.0);
            glVertex3f(1.0,1.0,-1.0);
            glVertex3f(-1.0,1.0,-1.0);


            //bottom
            glColor3f(0.0,1.0,1.0);

            glVertex3f(1.0,-1.0,1.0);
            glVertex3f(1.0,-1.0,-1.0);
            glVertex3f(-1.0,-1.0,-1.0);
            glVertex3f(-1.0,-1.0,1.0);

            //right
            glColor3f(1.0,0.0,1.0);

            glVertex3f(1.0,1.0,1.0);
            glVertex3f(1.0,-1.0,1.0);
            glVertex3f(1.0,-1.0,-1.0);
            glVertex3f(1.0,1.0,-1.0);


            //left
            glColor3f(1.0,1.0,0.0);

            glVertex3f(-1.0,1.0,1.0);
            glVertex3f(-1.0,-1.0,1.0);
            glVertex3f(-1.0,-1.0,-1.0);
            glVertex3f(-1.0,1.0,-1.0);


        glEnd();
}
