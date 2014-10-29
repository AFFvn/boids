#include "boid.h"

#include "boidscene.h"
#include "boidalgo.h"

#include "qglscenenode.h"
#include "qray3d.h"
#include "qplane3d.h"

#include <QMouseEvent>
#include <QThread>
#include <QTime>


#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QMessageBox>
#include <QGLBuilder>

BoidScene::BoidScene(QWindow * parent)
    : QGLView(parent),
      m_boidScene(new QGLSceneNode)
{
    m_boidScene->setParent(this);
    m_boidScene->setPalette(QSharedPointer<QGLMaterialCollection>(new QGLMaterialCollection(this)));
    m_boidScene->setEffect(QGL::LitMaterial);
    setTitle(QString("Boids"));
    srand(QTime::currentTime().msec());

    QGLBuilder builder;
    QGeometryData triangle;
    QVector3D a(-100, 0, 0);
    QVector3D b(0, -100, 0);
    QVector3D c(0, 0, -100);
    triangle.appendVertex(a, b, c);
    builder << triangle;
    QGLSceneNode * node = builder.finalizedSceneNode();
    m_boidScene->addNode(node);


    for (int i = 0; i < 1000; i++)
    {
        Boid * boid = addBoid();
        boid->setPosition(QVector3D(rand()%6,rand()%6,rand()%6));
    }
    thread = new QThread;
    worker = new BoidAlgo(myboids);
    qRegisterMetaType<QList<QVector3D> >("QList<QVector3D>");
    worker->moveToThread(thread);
    connect(thread, SIGNAL(started()), worker, SLOT(start_boids()));
    connect(worker, SIGNAL(finished_one_frame(QList<QVector3D>)), this, SLOT(update_one_frame(QList<QVector3D>)));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();

}


BoidScene::~BoidScene()
{}

Boid * BoidScene::addBoid()
{
    Boid * boid = new Boid(m_boidScene);
    myboids.append(boid);
    boid->setObjectName(QString("A Boid"));
    connect(boid, SIGNAL(updated()), this, SLOT(update()));
    return boid;

}

void BoidScene::paintGL(QGLPainter *painter)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_boidScene->draw(painter);
}

void BoidScene::initializeGL(QGLPainter *painter)
{
    painter->setClearColor(Qt::white);
    camera()->setEye(camera()->eye() + QVector3D(0.0f, 0.0f, 100.0f));
    glEnable(GL_BLEND);
}

void BoidScene::fly_boids()
{ // main function, calling the threads to calculating new boids position
}

void BoidScene::update_one_frame(QList<QVector3D> newPos)
{
    QParallelAnimationGroup * groupanim = new QParallelAnimationGroup();
    for (int i = 0 ; i < myboids.size(); i++)
    {
        Boid * boid = myboids.at(i);
        QPropertyAnimation * boidanim = new QPropertyAnimation(boid, "position", this);
        boidanim->setStartValue(boid->position());
        boidanim->setEndValue(newPos.at(i));
    //    qDebug() << newPos.at(i) << boid->position();
        boidanim->setDuration(1000/36);
        boidanim->setEasingCurve(QEasingCurve::InOutCirc);
        groupanim->addAnimation(boidanim);
    }
    groupanim->start();
    connect(groupanim, SIGNAL(finished()), worker, SLOT(fly_boids_to_new_position()));
}

void BoidScene::animate_boids()
{
}

