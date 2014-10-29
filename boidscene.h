#ifndef BOIDSCENE_H
#define BOIDSCENE_H

#include "qglview.h"
#include "boidalgo.h"
#include "QParallelAnimationGroup"
#include <QQueue>

class QGLSceneNode;

class Boid;

class BoidScene : public QGLView
{
    Q_OBJECT
public:
    BoidScene(QWindow * parent = 0);
    ~BoidScene();
signals:

protected:
    void initializeGL(QGLPainter *painter);
    void paintGL(QGLPainter *painter);
private slots:
    void update_one_frame(QList<QVector3D> newPos);
    void fly_boids();
    void animate_boids();
private:
    Boid * addBoid();
    //variables
    QGLSceneNode * m_boidScene;
    QList<Boid*> myboids;
    QList<QVector3D> boid_pos;

    QQueue<QParallelAnimationGroup*> animlist;
    BoidAlgo * worker;
    QThread * thread;
};

#endif // BOIDSCENE_H
