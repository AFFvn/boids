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
    void setDestination(QVector3D &des);
signals:
    void finished_one_frame (QList<QVector3D> newPos);
 //   void finished_24_frame();
 //   void got_new_boid_pos(QVector3D pos, int index);
    void destination_reached();
public slots:
    void initialize_boids();
    void start_boids();
    void fly_boids_to_new_position();

private:
    QVector3D rule1(Boid * thisBoid);
    QVector3D rule2(Boid * thisBoid);
    QVector3D rule3(Boid * thisBoid);
    QVector3D rule4(Boid * thisBoid);
    QVector3D rule5(Boid * thisBoid);
    QVector3D centre_of_mass();

    bool close_to_destination();
    void limit_velocity(Boid * thisBoid);
    void reset_destination();

    //variables
    QList<Boid*> boidList;
    QVector3D destination_point;
    QVector3D destination_direction;
    float distance;
};

#endif // BOIDALGO_H
