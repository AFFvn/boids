#ifndef BOID_H
#define BOID_H

#include "qglscenenode.h"

class Boid : public QGLSceneNode
{
    Q_OBJECT
public:
    explicit Boid(QObject *parent = 0);
    ~Boid();

signals:

public slots:
public:
    void setVelocity(const QVector3D &velo);
    QVector3D getVelocity() const;

private:
    static QGLSceneNode *boidObject();

    QGLTexture2D *m_texture;
    QVector3D velocity;
};

#endif // TANK_H
