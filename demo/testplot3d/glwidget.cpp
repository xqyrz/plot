#include "glwidget.h"
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLFunctions>

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    setMinimumSize(600, 400);
}

void GLWidget::addPoint(const QVector3D &point)
{
    points.append(point);
    update();
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 投影矩阵
    QMatrix4x4 projection;
    projection.perspective(45.0f, float(width())/height(), 0.1f, 100.0f);

    // 观察矩阵
    QMatrix4x4 view;
    view.translate(0, 0, -30 * zoom);  // 缩放
    view.rotate(rotX, 1, 0, 0);
    view.rotate(rotY, 0, 0, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(projection.constData());

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(view.constData());

    // 坐标轴
    glBegin(GL_LINES);
    glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(10,0,0);
    glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,10,0);
    glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,10);
    glEnd();

    // 曲线
    if (points.size() >= 2) {
        glColor3f(1,1,0);
        glBegin(GL_LINE_STRIP);
        for (const auto &p : points)
            glVertex3f(p.x(), p.y(), p.z());
        glEnd();
    }

    // 点
    glPointSize(6.0f);
    glBegin(GL_POINTS);
    glColor3f(1,0,1);
    for (const auto &p : points)
        glVertex3f(p.x(), p.y(), p.z());
    glEnd();
}

// 鼠标按下记录位置
void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

// 鼠标移动旋转
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        rotX += dy * 0.5f;
        rotY += dx * 0.5f;
    }

    lastPos = event->pos();
    update();
}

// 鼠标滚轮缩放
void GLWidget::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0)
        zoom *= 0.9f;
    else
        zoom *= 1.1f;
    update();
}