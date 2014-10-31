#include "boidalgo.h"

#include "boid.h"

#include <QVector3D>
#include <QTime>
#include <qmath.h>


BoidAlgo::BoidAlgo(QList<Boid*> birds) :
   destination_point(0.0f, 0.0f, 0.0f),
   destination_direction(0.0f, 0.0f, 0.0f)
{
    boidList = birds;
    srand(QTime::currentTime().msec());
}

void BoidAlgo::setDestination(QVector3D &des)
{
    destination_point = des;
    destination_direction = des;
}

void BoidAlgo::initialize_boids()
{ // initalize every boid positions

}

void BoidAlgo::start_boids()
{//draw boids at EACH frame
    fly_boids_to_new_position();

    //calculate new positions for each boid
    //access using indexes
}

void BoidAlgo::fly_boids_to_new_position()
{// actual boids algorithm
    QList<QVector3D> newPos;
    QVector3D v1, v2, v3, v4, v5;
//    distance_to_destination();
    for (int i = 0; i < boidList.size(); i++)
    {
        Boid * boid = boidList.at(i);
        v1 = rule1(boid);
        v2 = rule2(boid);
        v3 = rule3(boid);
        v4 = rule4(boid);
        v5 = rule5(boid);
        QVector3D velo = boid->getVelocity() + v1 + v2 + v3 + v4 + v5;
        boid->setVelocity(velo);
        limit_velocity(boid);
        QVector3D pos = boid->position() + velo;
        newPos.push_back(pos);
    }
    emit finished_one_frame(newPos);
}

QVector3D BoidAlgo::rule1(Boid * thisBoid)
{//move toward centre of mass
    QVector3D sum;
    for (int i = 0; i < boidList.size(); i++)
    {
        Boid * boid = boidList.at(i);
        if (boid == thisBoid){}
        else
        {
            sum += boid->position();
        }
    }
    sum = sum/(boidList.size()-1);
    return (sum - thisBoid->position())/100;
}

QVector3D BoidAlgo::rule2(Boid * thisBoid)
{//stay away from near birds avoid collision
    QVector3D c;
    for (int i = 0 ; i < boidList.size(); i++)
    {
        Boid * boid = boidList.at(i);
        if (boid == thisBoid){}
        else
        {//checking distance
            if (boid->position().distanceToPoint(thisBoid->position()) < 3.0f)
            {
                c = c - (boid->position() - thisBoid->position());
            }
        }

    }
    return c;
}

QVector3D BoidAlgo::rule3(Boid * thisBoid)
{
    QVector3D v;
    for (int i = 0; i < boidList.size(); i++)
    {
        Boid * boid = boidList.at(i);
        if (boid == thisBoid){}
        else
        {
            v += boid->getVelocity();
        }
    }
    v = v/(boidList.size()-1);
    return (v-thisBoid->getVelocity())/8;
}

QVector3D BoidAlgo::rule4(Boid *thisBoid)
{//moving rule
    QVector3D v;
    if (close_to_destination())
    {
        emit destination_reached();
    }
    v = (destination_direction - thisBoid->position())/100;
    return v;
}

QVector3D BoidAlgo::rule5(Boid *thisBoid)
{ // bounding in a region
    QVector3D v;
            float xmin, xmax, ymin, ymax, zmin, zmax;
            float theta = 6.0f;
            xmin = destination_point.x() - theta;
            xmax = destination_point.x() + theta;
            ymin = destination_point.y() - theta;
            ymax = destination_point.y() + theta;
            zmin = destination_point.z() - theta;
            zmax = destination_point.z() + theta;

            if (thisBoid->position().x() < xmin) {v.setX(v.x()+5.0f/1000);}
            else if (thisBoid->position().x() > xmax) {v.setX(v.x()-5.0f/1000);}
            if (thisBoid->position().y() < ymin) {v.setY(v.y()+5.0f/1000);}
            else if (thisBoid->position().y() > ymax) {v.setY(v.y()-5.0f/1000);}
            if (thisBoid->position().z() < zmin) {v.setZ(v.z()+5.0f/1000);}
            else if(thisBoid->position().z() > zmax) {v.setZ(v.z()-5.0f/1000);}
            return v;
}

QVector3D BoidAlgo::centre_of_mass()
{
    QVector3D centre;
    for (int i = 0; i < boidList.size(); i++)
    {
        centre += boidList.at(i)->position();
    }
    centre = centre/boidList.size();
    return centre;
}


bool BoidAlgo::close_to_destination()
{ // the distance is hardcoded atm
    return (qAbs(centre_of_mass().distanceToPoint(destination_point)) <= 5.0f);

}

void BoidAlgo::limit_velocity(Boid * thisBoid)
{   // DEFINE LIMIT
    float limit = 3;
    QVector3D velo = thisBoid->getVelocity();
    float x = velo.x(), y = velo.y(), z = velo.z();
    float magnitude = qAbs(qSqrt(qPow(x, 2) + qPow(y,2) + qPow(z,2)));
    if (magnitude > limit) {
        velo = (velo / magnitude) * limit;
        thisBoid->setVelocity(velo);
    }

}

void BoidAlgo::reset_destination()
{
}
