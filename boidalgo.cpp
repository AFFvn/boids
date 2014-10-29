#include "boidalgo.h"

#include "boid.h"

#include <QVector3D>

BoidAlgo::BoidAlgo(QList<Boid*> birds)
{
    boidList = birds;
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
    QVector3D v1, v2, v3;
    for (int i = 0; i < boidList.size(); i++)
    {
        Boid * boid = boidList.at(i);
        v1 = rule1(boid);
        v2 = rule2(boid);
        v3 = rule3(boid);
        QVector3D velo = boid->getVelocity() + v1 + v2 + v3;
        boid->setVelocity(velo);
        QVector3D pos = boid->position() + velo;
  //      boid->setPosition(pos);
        newPos.push_back(pos);
   //     emit got_new_boid_pos(pos, i);
    }
    emit finished_one_frame(newPos);
}


QVector3D BoidAlgo::rule1(Boid * thisBoid)
{//move toward centre of mass
    QVector3D vec, sum;
    for (int i = 0; i < boidList.size(); i++)
    {
        Boid * boid = boidList.at(i);
        if (boid == thisBoid){}
        else
        {
            sum += boid->position();
        }
    }
    vec = sum/(boidList.size()-1);
    return (vec - thisBoid->position())/100;
}

QVector3D BoidAlgo::rule2(Boid * thisBoid)
{//stay away from near birds avoid collision
    QVector3D c(0, 0 ,0);
    for (int i = 0 ; i < boidList.size(); i++)
    {
        Boid * boid = boidList.at(i);
        if (boid == thisBoid){}
        else
        {//checking distance
            if (qAbs(boid->position().distanceToPoint(thisBoid->position())) < 5)
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
