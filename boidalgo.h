#ifndef BOIDALGO_H
#define BOIDALGO_H

#include <QList>
#include <QCoreApplication>
#include <QVector3D>

class Boid;

class BoidAlgo : public QObject
{
       Q_OBJECT
public:
    BoidAlgo(QList<Boid*> boidList);

signals:
    void finished_one_frame (QList<QVector3D> newPos);
 //   void finished_24_frame();
 //   void got_new_boid_pos(QVector3D pos, int index);
public slots:
    void initialize_boids();
    void start_boids();
    void fly_boids_to_new_position();

private:
    QVector3D rule1(Boid * thisBoid);
    QVector3D rule2(Boid * thisBoid);
    QVector3D rule3(Boid * thisBoid);

    //variables
    QList<Boid*> boidList;
};

#endif // BOIDALGO_H
