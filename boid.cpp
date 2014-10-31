#include "boid.h"

#include "qglbuilder.h"
#include "qglsphere.h"
#include "qglmaterial.h"
#include "qgltexture2d.h"
#include "qgraphicsscale3d.h"
#include "qgraphicsrotation3d.h"
#include "qglcube.h"

#include <QTime>

Boid::Boid(QObject *parent)
    :QGLSceneNode(parent),
      m_texture(0),
      velocity(0, 0, 0)
{
    addNode(boidObject());
}

Boid::~Boid()
{
}

void Boid::setVelocity(const QVector3D &velo)
{
    velocity = velo;
}

QVector3D Boid::getVelocity() const
{
    return velocity;
}

QGLSceneNode * Boid::boidObject()
{
    static QGLSceneNode *v = 0;
    if (!v)
    {
        QGLBuilder build;
        build << QGLSphere(2.0f);
        v = build.finalizedSceneNode();
        v->setObjectName("Boid");
        //setting colour
        //default
        QGraphicsRotation3D * rot = new QGraphicsRotation3D(v);
        rot->setAngle(90.0f);
        rot->setAxis(QVector3D(1, 0, 0));
        v->addTransform(rot);

        v->setY(-v->boundingBox().minimum().y());
    }
    return v;
}

void Boid::setColour(int i)
{
    QGLMaterial *mat = new QGLMaterial;
    QColor colour;
    switch(i){
    case 0:
        colour = Qt::blue;
        break;
    case 1:
        colour = Qt::red;
        break;
    case 2:
        colour = Qt::green;
        break;
    case 3:
        colour = Qt::darkBlue;
        break;
    case 4:
        colour = Qt::gray;
        break;
    default:
        qDebug() << "WHY AM I HERE";
        break;
    }
    colour.setAlpha(128);
    mat->setColor(colour);
    mat->setShininess(2.0f);
    this->setMaterial(mat);
}
